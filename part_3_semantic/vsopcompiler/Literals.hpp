/**
 * Types related to the literals for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef LITERAL_HH
#define LITERAL_HH

#include <string>
#include <map>
#include <vector>

#include "Expr.hpp"
#include "Class.hpp"

class IntegerLiteral : public Expr 
{
    private:
        int intValue;

    public:
        IntegerLiteral(const int intValue);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class StringLiteral : public Expr
{
    private:
        std::string stringValue;
    
    public:
        StringLiteral(const std::string stringValue);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};

};

class BooleanLiteral : public Expr
{
    private:
        bool booleanValue;
    
    public:
        BooleanLiteral(const bool booleanValue);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

#endif
