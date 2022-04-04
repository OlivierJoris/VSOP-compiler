/**
 * Expr type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef VSOP_EXPR_HH
#define VSOP_EXPR_HH

#include <string>
#include <map>

class Class;

class Expr
{
    public:
        virtual std::string eval() const = 0;

        /**
         * @brief Check if expr is using non defined type.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        virtual const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const = 0;
};

#endif
