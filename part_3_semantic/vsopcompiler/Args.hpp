/**
 * Args type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef ARGS_HH
#define ARGS_HH

#include <string>
#include <vector>
#include <map>

#include "Expr.hpp"
#include "Class.hpp"

class Args : public Expr
{
    private:
        std::vector<Expr*> exprList;

    public:
        Args();
        void addExpr(Expr *expr) {exprList.push_back(expr);}
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
