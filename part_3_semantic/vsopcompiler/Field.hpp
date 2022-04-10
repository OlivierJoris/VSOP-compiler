/**
 * Field type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef FIELD_HH
#define FIELD_HH

#include <string>
#include <map>

#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent a field of a class.
 */
class Field : public Expr
{
    private:
        std::string name;
        std::string type;
        Expr *initExpr;

    public:
        Field(const std::string name, const std::string type, Expr *initExpr, const int line, const int column);
        std::string getName() {return name;}

        /**
         * @brief Dump the AST corresponding to the field inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the field is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
