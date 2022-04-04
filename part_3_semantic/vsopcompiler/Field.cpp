/**
 * Implementation of the class type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <map>

#include "Field.hpp"
#include "Expr.hpp"
#include "Class.hpp"

#include "TypeChecking.hpp"

using namespace std;

Field::Field(const string name, const string type, Expr *initExpr): name(name), type(type), initExpr(initExpr){}

string Field::eval() const
{
    string initExpr = "";

    if(Field::initExpr)
        initExpr = ", " + Field::initExpr->eval();

    return "Field(" + Field::name + ", " + Field::type + initExpr + ")";
}

const Expr* Field::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check type of field
    bool known = checkKnownType(classesMap, type);
    if(!known)
        return this;

    // Check init expr if any
    if(initExpr){
        const Expr* check = initExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}
