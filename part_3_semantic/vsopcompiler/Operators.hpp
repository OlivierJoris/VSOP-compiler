/**
 * Operator types for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef OPERATORS_HH
#define OPERATORS_HH

#include <string>
#include <map>
#include <vector>

#include "Expr.hpp"
#include "Class.hpp"

class Assign : public Expr 
{
    private:
        std::string name;
        Expr *expr;

    public:
        Assign(const std::string name, Expr* expr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class UnOp : public Expr 
{
    protected:
        Expr* expr;
        std::string symbol;

    public:
        UnOp(const std::string symbol, Expr *expr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Not : public UnOp
{
    public:
        Not(Expr *expr);
};

class UnaryMinus : public UnOp
{
    public:
        UnaryMinus(Expr *expr);
};

class IsNull : public UnOp
{
    public:
        IsNull(Expr *expr);
};

class BinOp : public Expr
{
    protected:
        Expr *leftExpr;
        Expr *rightExpr;
        std::string symbol;
    
    public:
        BinOp(const std::string symbol, Expr *leftExpr, Expr *rightExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Plus : public BinOp
{
    public:
        Plus(Expr *leftExpr, Expr *rightExpr);
};

class Minus : public BinOp
{
    public:
        Minus(Expr *leftExpr, Expr *rightExpr);
};

class Times : public BinOp
{
    public:
        Times(Expr *leftExpr, Expr *rightExpr);
};

class Div : public BinOp
{
    public :
        Div(Expr *leftExpr, Expr *rightExpr);
};

class And : public BinOp
{
    public:
        And(Expr *leftExpr, Expr *rightExpr);
};

class LowerEqual : public BinOp
{
    public:
        LowerEqual(Expr *leftExpr, Expr *rightExpr);
};

class Lower : public BinOp
{
    public:
        Lower(Expr *leftExpr, Expr *rightExpr);
};

class Equal : public BinOp
{
    public:
        Equal(Expr *leftExpr, Expr *rightExpr);
};

class Pow : public BinOp
{
    public:
        Pow(Expr *leftExpr, Expr *rightExpr);
};

#endif
