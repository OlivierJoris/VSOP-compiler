/**
 * Implementation of the if type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <map>

#include "If.hpp"
#include "Expr.hpp"
#include "Class.hpp"

using namespace std;

If::If(Expr *condExpr, Expr *thenExpr, Expr *elseExpr): condExpr(condExpr), thenExpr(thenExpr), elseExpr(elseExpr){}

string If::eval() const
{
    string elseExpr = "";

    if(If::elseExpr)
        elseExpr = ", " + If::elseExpr->eval();

    return "If(" + If::condExpr->eval() + ", " + If::thenExpr->eval() + elseExpr + ")";
}

const Expr* If::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check cond expression if any
    if(condExpr){
        const Expr* check = condExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check then expression if any
    if(thenExpr){
        const Expr* check = thenExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check els expression if any
    if(elseExpr){
        const Expr* check = elseExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}
