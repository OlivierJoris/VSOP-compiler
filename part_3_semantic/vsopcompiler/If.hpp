/**
 * If type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef IF_HH
#define IF_HH

#include <string>
#include <map>

#include "Expr.hpp"
#include "Class.hpp"

class If : public Expr 
{
    private:
        Expr *condExpr;
        Expr *thenExpr;
        Expr *elseExpr;
    
    public:
        If(Expr *condExpr, Expr *thenExpr, Expr *elseExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

#endif
