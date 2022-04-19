/**
 * Args type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef ARGS_HH
#define ARGS_HH

#include <string>
#include <vector>
#include <map>

#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent a list of expressions.
 */
class Args : public Expr
{
    private:
        std::vector<Expr*> exprList;

    public:
        Args(const int line, const int column);
        void addExpr(Expr *expr) {exprList.push_back(expr);}
        std::vector<Expr*> getExpr() {return exprList;}
        size_t getNumberExpr() const {return exprList.size();}

        /**
         * @brief Dump the AST corresponding to the expressions inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the expressions are using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the list of expressions.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the expressions.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

#endif
