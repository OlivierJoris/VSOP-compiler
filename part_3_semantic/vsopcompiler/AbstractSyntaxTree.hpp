/**
 * Abstract syntax tree for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef ABSTRACTSYNTAXTREE_HH
#define ABSTRACTSYNTAXTREE_HH

#include <string>
#include <vector>
#include <map>

#include "Expr.hpp"
#include "Class.hpp"

class Program : public Expr
{
    private:
        std::vector<Class*> classes;

    public:
        Program();
        void checkRedefinition();
        void checkInheritance();
        void checkOverrides();
        void addClass(Class* cls) {classes.push_back(cls);}
        std::string eval() const override;
        std::vector<Class*> getClasses() {return classes;}
        std::map<std::string, Class*> classesMap;
        std::vector<std::string> errors;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Unit : public Expr
{
    public:
        Unit();
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

#endif
