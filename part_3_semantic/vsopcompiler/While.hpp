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
        While(Expr *condExpr, Expr *bodyExpr);

        /**
         * @brief Dump the AST corresponding to the while inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the while is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
