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
