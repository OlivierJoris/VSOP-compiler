/**
 * Implementation of the while type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <map>
#include <string>

#include "While.hpp"
#include "Expr.hpp"
#include "Class.hpp"

using namespace std;

While::While(Expr *condExpr, Expr *bodyExpr): condExpr(condExpr), bodyExpr(bodyExpr){}

string While::eval() const 
{
    return "While(" + While::condExpr->eval() + ", " + While::bodyExpr->eval() + ")";
}

const Expr* While::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check condition expression if any
    if(condExpr){
        const Expr* check = condExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check body expression if any
    if(bodyExpr){
        const Expr* check = bodyExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}
