/**
 * Implementation of the formal type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "Formal.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "TypeChecking.hpp"

using namespace std;

Formal::Formal(const string name, const string type, const int line, const int column): name(name), type(type){
    this->line = line;
    this->column = column;
}

string Formal::eval() const
{
    return Formal::name + " : " + Formal::type;
}

const Expr* Formal::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    bool known = checkKnownType(classesMap, type);
    if(known){
        return NULL;
    }else{
        cout << "Type of formal " << name << " unknown" << endl;
        return this;
    }
}

Formals::Formals(){}

string Formals::eval() const
{
    string formals = "";

    if(Formals::formals.size() != 0)
    {
        auto firstFormal = Formals::formals.rbegin();
        formals = (*firstFormal)->eval();

        for(auto it = Formals::formals.rbegin() + 1; it != Formals::formals.rend(); ++it)
            formals += ", " + (*it)->eval();
    }

    return "[" + formals + "]";
}

const Expr* Formals::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check if there is any formal to check
    if(formals.size() == 0)
        return NULL;

    // Check all formals
    for(Formal *formal: formals){
        const Expr* check = formal->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

const string Formals::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Check each formal
    for(Formal *formal: formals){
        if(formal){
            // Scope does not matter since there should never be any errors
            const string err = formal->typeChecking(prog, currentClass, scope);
            if(err.compare(""))
                return err;
        }
    }

    return "";
}
