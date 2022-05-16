/**
 * Expr type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef VSOP_EXPR_HH
#define VSOP_EXPR_HH

#include <vector>
#include <string>
#include <map>
#include <utility>

#include "llvm/IR/Value.h"

class Program;
class Class;

/**
 * @brief Represent an expression.
 */
class Expr
{
    protected:
        int line;
        int column;

    public:
        /**
         * @brief Type of the expression.
         */
        std::string type;

        /**
         * @brief Dump the AST corresponding to the expressions inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST
         */
        virtual std::string dumpAST(bool annotated) const = 0;

        /**
         * @brief Check if expr is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        virtual const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const = 0;

        /**
         * @brief Perform type checking on the expression.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the expression.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        virtual const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) = 0;

        /**
         * @brief Perform code generation on the expression.
         * 
         * @param Program Program for which we are generating code.
         * @param cls current Class in which we are generating code.
         * @param fileName Name of the file for which we are generating code.
         * 
         * @return llvm::Value* Value of the expression.
         */
        virtual llvm::Value *generateCode(Program *Program, Class* cls, const std::string &fileName) = 0;

        /**
         * @brief Get the line of the expression.
         * 
         * @return int Line.
         */
        int getLine() const { return line; }

        /**
         * @brief Get the column of the expression.
         * 
         * @return int Column.
         */     
        int getColumn() const { return column; }
};

#endif
