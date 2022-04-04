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

Let::Let(const string name, const string type, Expr *scopeExpr, Expr *initExpr): name(name), type(type), scopeExpr(scopeExpr), initExpr(initExpr){}

string Let::eval() const
{
    string initExpr = "";

    if(Let::initExpr)
        initExpr = ", " + Let::initExpr->eval();

    return "Let(" + Let::name + ", " + Let::type + initExpr + ", " + Let::scopeExpr->eval() + ")";
}
