/**
 * Formal type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef FORMAL_HH
#define FORMAL_HH

#include <string>
#include <map>
#include <vector>

#include "Expr.hpp"
#include "Class.hpp"

class Formal : public Expr 
{
    private:
        std::string name;
        std::string type;
    
    public:
        Formal(const std::string name, const std::string type);
        std::string eval() const override;
        std::string getName() {return name;}
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        std::string getType() {return type;}
};

class Formals : public Expr
{
    private:
        std::vector<Formal*> formals;
    
    public:
        Formals();
        void addFormal(Formal *formal){formals.push_back(formal);};
        std::string eval() const override;
        std::vector<Formal*> getFormals() {return formals;}
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        Formal *getFormals(unsigned int i) {return formals[i];}
};

#endif
