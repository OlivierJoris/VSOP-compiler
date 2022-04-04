/**
 * While type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef WHILE_HH
#define WHILE_HH

#include <map>
#include <string>

#include "Expr.hpp"
#include "Class.hpp"

class While : public Expr
{
    private:
        Expr *condExpr;
        Expr *bodyExpr;

    public:
        While(Expr *condExpr, Expr *bodyExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
