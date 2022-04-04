/**
 * Let type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef LET_HH
#define LET_HH

#include <string>
#include <map>
#include <string>

#include "Expr.hpp"
#include "Class.hpp"

class Let : public Expr 
{
    private:
        std::string name;
        std::string type;
        Expr *scopeExpr;
        Expr *initExpr;
    
    public:
        Let(const std::string name, const std::string type, Expr *scopeExpr, Expr *initExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

#endif
