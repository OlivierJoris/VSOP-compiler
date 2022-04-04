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
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class UnOp : public Expr 
{
    protected:
        Expr* expr;
        std::string symbol;

    public:
        UnOp(const std::string symbol, Expr *expr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Not : public UnOp
{
    public:
        Not(Expr *expr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class UnaryMinus : public UnOp
{
    public:
        UnaryMinus(Expr *expr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class IsNull : public UnOp
{
    public:
        IsNull(Expr *expr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
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
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Plus : public BinOp
{
    public:
        Plus(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Minus : public BinOp
{
    public:
        Minus(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Times : public BinOp
{
    public:
        Times(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Div : public BinOp
{
    public :
        Div(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class And : public BinOp
{
    public:
        And(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class LowerEqual : public BinOp
{
    public:
        LowerEqual(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Lower : public BinOp
{
    public:
        Lower(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Equal : public BinOp
{
    public:
        Equal(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Pow : public BinOp
{
    public:
        Pow(Expr *leftExpr, Expr *rightExpr);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
