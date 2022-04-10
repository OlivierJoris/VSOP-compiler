/**
 * Implementation of the let type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <map>
#include <string>

#include "Let.hpp"
#include "Expr.hpp"
#include "Class.hpp"

using namespace std;

Let::Let(const string name, const string type, Expr *scopeExpr, Expr *initExpr, const int line, const int column): name(name), type(type), scopeExpr(scopeExpr), initExpr(initExpr){
    this->line = line;
    this->column = column;
}

string Let::eval() const
{
    string initExpr = "";

    if(Let::initExpr)
        initExpr = ", " + Let::initExpr->eval();

    return "Let(" + Let::name + ", " + Let::type + initExpr + ", " + Let::scopeExpr->eval() + ")";
}

const Expr* Let::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check expr used in initialize if any
    if(initExpr){
        const Expr* check = initExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check expr used in scope if any
    if(scopeExpr){
        const Expr* check = scopeExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}
