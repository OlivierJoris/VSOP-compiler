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

        /**
         * @brief Dump the AST corresponding to the expressions inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the expressions are using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

#endif
