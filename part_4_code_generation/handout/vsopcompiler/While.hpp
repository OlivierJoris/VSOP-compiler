/**
 * While type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef WHILE_HH
#define WHILE_HH

#include <map>
#include <string>

#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent a while in the source code.
 */
class While : public Expr
{
    private:
        Expr *condExpr;
        Expr *bodyExpr;

    public:
        While(Expr *condExpr, Expr *bodyExpr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the while inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the while is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the while.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the while.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;

        /**
         * @brief Perform code generation on the expression.
         * 
         * @param Program Program for which we are generating code.
         * @param cls current Class in which we are generating code.
         * @param fileName Name of the file for which we are generating code.
         * 
         * @return llvm::Value* Value of the expression.
         */
        llvm::Value *generateCode(Program *Program, Class* cls, const std::string &fileName) override;
};

#endif
