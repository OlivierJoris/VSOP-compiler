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

string Formal::dumpAST(bool) const
{
    return Formal::name + " : " + Formal::type;
}

const string Formal::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    bool known = checkKnownType(classesMap, type);
    if(known)
        return "";
    else
        return to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: formal " + name + " is using an undefined type.";
}

Formals::Formals(){}

string Formals::dumpAST(bool) const
{
    string formals = "";

    if(Formals::formals.size() != 0)
    {
        auto firstFormal = Formals::formals.rbegin();
        formals = (*firstFormal)->dumpAST(false);

        for(auto it = Formals::formals.rbegin() + 1; it != Formals::formals.rend(); ++it)
            formals += ", " + (*it)->dumpAST(false);
    }

    return "[" + formals + "]";
}

const string Formals::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check if there is any formal to check
    if(formals.size() == 0)
        return "";

    // Check all formals
    for(Formal *formal: formals){
        const string check = formal->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
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
