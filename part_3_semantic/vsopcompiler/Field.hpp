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

class Field : public Expr
{
    private:
        std::string name;
        std::string type;
        Expr *initExpr;

    public:
        Field(const std::string name, const std::string type, Expr *initExpr);
        std::string getName() {return name;}
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
