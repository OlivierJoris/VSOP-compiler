/**
 * Types related to methods for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef METHOD_HH
#define METHOD_HH

#include <string>
#include <map>
#include <vector>

class Block;
class Args;
class Formal;
class Formals;

#include "Block.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "Formal.hpp"
#include "Args.hpp"

class Method : public Expr 
{
    private:
        std::string name;
        Formals* formals;
        std::string retType;
        Block* block;

    public:
        Method(const std::string name, Formals *formals, const std::string retType, Block *block);
        std::string eval() const override;
        std::string getName() {return name;}
        std::vector<Formal*> getFormals();
        Formal *getFormals(unsigned int i);
        std::string getRetType() {return retType;}
        std::map<std::string, Formal*> formalsMap;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Call : public Expr 
{
    private:
        Expr *objExpr;
        std::string methodName;
        Args *listExpr;

    public:
        Call(Expr *objExpr, const std::string methodName, Args *listExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class New : public Expr
{
    private:
        std::string typeName;
    
    public:
        New(const std::string typeName);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class ObjectIdentifier : public Expr
{
    private:
        std::string identifier;
    
    public:
        ObjectIdentifier(const std::string identifier);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};
};

class Self : public Expr
{
    public:
        Self();
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};
};

#endif
