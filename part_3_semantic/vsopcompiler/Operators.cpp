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

const Expr* Assign::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check expression if any
    if(expr){
        const Expr* check = expr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

UnOp::UnOp(const string symbol, Expr *expr): expr(expr), symbol(symbol){}

string UnOp::eval() const 
{
    return "UnOp(" + UnOp::symbol + ", " + UnOp::expr->eval() + ")";
}

const Expr* UnOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check expr if any
    if(expr){
        const Expr* check = expr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

Not::Not(Expr *expr): UnOp("not", expr){}

const Expr* Not::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

UnaryMinus::UnaryMinus(Expr *expr): UnOp("-", expr){}

const Expr* UnaryMinus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

IsNull::IsNull(Expr *expr): UnOp("isnull", expr){}

const Expr* IsNull::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

BinOp::BinOp(const string symbol, Expr *leftExpr, Expr *rightExpr): leftExpr(leftExpr), rightExpr(rightExpr), symbol(symbol){}

string BinOp::eval() const 
{
    return "BinOp(" + BinOp::symbol + ", " + BinOp::leftExpr->eval() + ", " + BinOp::rightExpr->eval() + ")";
}

const Expr* BinOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check left-hand side expression if any
    if(leftExpr){
        const Expr* check = leftExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check right-hand side expression if any
    if(rightExpr){
        const Expr* check = rightExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

Plus::Plus(Expr *leftExpr, Expr *rightExpr): BinOp("+", leftExpr, rightExpr){}

const Expr* Plus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

Minus::Minus(Expr *leftExpr, Expr *rightExpr): BinOp("-", leftExpr, rightExpr){}

const Expr* Minus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

Times::Times(Expr *leftExpr, Expr *rightExpr): BinOp("*", leftExpr, rightExpr){}

const Expr* Times::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

Div::Div(Expr *leftExpr, Expr *rightExpr): BinOp("/", leftExpr, rightExpr){}

const Expr* Div::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

And::And(Expr *leftExpr, Expr *rightExpr): BinOp("and", leftExpr, rightExpr){}

const Expr* And::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

LowerEqual::LowerEqual(Expr *leftExpr, Expr *rightExpr): BinOp("<=", leftExpr, rightExpr){}

const Expr* LowerEqual::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

Lower::Lower(Expr *leftExpr, Expr *rightExpr): BinOp("<", leftExpr, rightExpr){}

const Expr* Lower::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

Equal::Equal(Expr *leftExpr, Expr *rightExpr): BinOp("=", leftExpr, rightExpr){}

const Expr* Equal::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

Pow::Pow(Expr *leftExpr, Expr *rightExpr): BinOp("^", leftExpr, rightExpr){}

const Expr* Pow::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}
