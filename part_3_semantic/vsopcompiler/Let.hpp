/**
 * Let type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef LET_HH
#define LET_HH

#include <string>
#include <map>
#include <string>

#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent a let in the source code.
 */
class Let : public Expr 
{
    private:
        std::string name;
        std::string type;
        Expr *scopeExpr;
        Expr *initExpr;
    
    public:
        Let(const std::string name, const std::string type, Expr *scopeExpr, Expr *initExpr);

        /**
         * @brief Dump the AST corresponding to the let inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the let is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
