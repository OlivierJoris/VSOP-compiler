/**
 * Implementation of the operator types for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <map>
#include <vector>

#include "Operators.hpp"
#include "Expr.hpp"
#include "Class.hpp"

using namespace std;

Assign::Assign(const string name, Expr *expr): name(name), expr(expr){}

string Assign::eval() const 
{
    return "Assign(" + Assign::name + ", " + Assign::expr->eval() + ")";
}

UnOp::UnOp(const string symbol, Expr *expr): expr(expr), symbol(symbol){}

string UnOp::eval() const 
{
    return "UnOp(" + UnOp::symbol + ", " + UnOp::expr->eval() + ")";
}

Not::Not(Expr *expr): UnOp("not", expr){}

UnaryMinus::UnaryMinus(Expr *expr): UnOp("-", expr){}

IsNull::IsNull(Expr *expr): UnOp("isnull", expr){}

BinOp::BinOp(const string symbol, Expr *leftExpr, Expr *rightExpr): leftExpr(leftExpr), rightExpr(rightExpr), symbol(symbol){}

string BinOp::eval() const 
{
    return "BinOp(" + BinOp::symbol + ", " + BinOp::leftExpr->eval() + ", " + BinOp::rightExpr->eval() + ")";
}

Plus::Plus(Expr *leftExpr, Expr *rightExpr): BinOp("+", leftExpr, rightExpr){}

Minus::Minus(Expr *leftExpr, Expr *rightExpr): BinOp("-", leftExpr, rightExpr){}

Times::Times(Expr *leftExpr, Expr *rightExpr): BinOp("*", leftExpr, rightExpr){}

Div::Div(Expr *leftExpr, Expr *rightExpr): BinOp("/", leftExpr, rightExpr){}

And::And(Expr *leftExpr, Expr *rightExpr): BinOp("and", leftExpr, rightExpr){}

LowerEqual::LowerEqual(Expr *leftExpr, Expr *rightExpr): BinOp("<=", leftExpr, rightExpr){}

Lower::Lower(Expr *leftExpr, Expr *rightExpr): BinOp("<", leftExpr, rightExpr){}

Equal::Equal(Expr *leftExpr, Expr *rightExpr): BinOp("=", leftExpr, rightExpr){}

Pow::Pow(Expr *leftExpr, Expr *rightExpr): BinOp("^", leftExpr, rightExpr){}
