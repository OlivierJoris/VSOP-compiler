/**
 * If type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef IF_HH
#define IF_HH

#include <string>
#include <map>

#include "Expr.hpp"
#include "Class.hpp"
#include "AbstractSyntaxTree.hpp"

/**
 * @brief Represent an if in the source code.
 */
class If : public Expr 
{
    private:
        Expr *condExpr;
        Expr *thenExpr;
        Expr *elseExpr;
    
    public:
        If(Expr *condExpr, Expr *thenExpr, Expr *elseExpr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the if inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the if is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the if.
         * 
         * @param prog Program that we are analyzing.
         * @param scope Scope of identifiers usable by the if.
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override;
};

#endif
