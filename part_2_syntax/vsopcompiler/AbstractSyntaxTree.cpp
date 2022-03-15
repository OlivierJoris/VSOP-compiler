#include "AbstractSyntaxTree.hpp"

Add::Add(Expr *leftExpr, Expr *rightExpr){
    Add::leftExpr = leftExpr;
    Add::rightExpr = rightExpr;

    symbol = '+';
}

Sub::Sub(Expr *leftExpr, Expr *rightExpr){
    Sub::leftExpr = leftExpr;
    Sub::rightExpr = rightExpr;

    symbol = '-';
}

Mul::Mul(Expr *leftExpr, Expr *rightExpr){
    Mul::leftExpr = leftExpr;
    Mul::rightExpr = rightExpr;

    symbol = '*';
}

Div::Div(Expr *leftExpr, Expr *rightExpr){
    Div::leftExpr = leftExpr;
    Div::rightExpr = rightExpr;

    symbol = '/';
}

std::string BinOp::eval() const {
    return "BinOp(" + symbol + "," + BinOp::leftExpr->eval() + "," + BinOp::rightExpr->eval() + ")";
}