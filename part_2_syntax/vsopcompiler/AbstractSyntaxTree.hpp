#ifndef ABSTRACTSYNTAXTREE_HH
#define ABSTRACTSYNTAXTREE_HH

#include <string>
#include <memory>

class Expr 
{
    public: 
        virtual std::string eval() const = 0;
};

class BinOp : public Expr
{
    protected:
        Expr *leftExpr;
        Expr *rightExpr;
        std::string symbol;
    
    public:
        virtual std::string eval() const = 0;
};

class Add: public BinOp
{
    public:
        Add(Expr *leftExpr, Expr *rightExpr);
};

class Sub: public BinOp
{
    public:
        Sub(Expr *leftExpr, Expr *rightExpr);
};

class Mul: public BinOp
{
    public:
        Mul(Expr *leftExpr, Expr *rightExpr);
};

class Div: public BinOp
{
    public:
        Div(Expr *leftExpr, Expr *rightExpr);
};



#endif