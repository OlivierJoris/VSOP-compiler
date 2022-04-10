/**
 * Implementation of the class type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Expr.hpp"
#include "Class.hpp"
#include "Field.hpp"

using namespace std;

Class::Class(const string name, const string parent, vector<Field*>& fields, vector<Method*>& methods, const int line, const int column): name(name), parent(parent), fields(fields), methods(methods){
    this->line = line;
    this->column = column;
}

string Class::eval() const
{
    string fields = "";    

    if(Class::fields.size() != 0)
    {
        auto firstField = Class::fields.rbegin();
        fields = (*firstField)->eval();

        for(auto it = Class::fields.rbegin() + 1; it != Class::fields.rend(); ++it)
            fields += ", " + (*it)->eval();
    }

    string methods = "";

    if(Class::methods.size() != 0)
    {
        auto firstMethod = Class::methods.rbegin();
        methods = (*firstMethod)->eval();

        for(auto it = Class::methods.rbegin() + 1; it != Class::methods.rend(); ++it)
            methods += ", " + (*it)->eval();
    }
    
    return "Class(" + Class::name + ", " + Class::parent + ", " + "[" + fields + "]" + ", " + "[" + methods + "]" + ")";
}

const Expr* Class::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check fields
    for(Field *field: fields){
        const Expr* check = field->checkUsageUndefinedType(classesMap);
        if(check) {
            cout << "Usage of not defined type for field " << field->getName() << endl;
            return check;
        }
    }

    // Check methods
    for(Method *method: methods){
        const Expr* check = method->checkUsageUndefinedType(classesMap);
        if (check) {
            cout << "Usage of not defined type for method " << method->getName() << endl;
            return check;
        }
    }

    return NULL;
}

const string Class::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    // Type checking on each field
    for(Field *field: fields){
        if(field){
            cout << "Performing type checking on field " << field->getName() << endl;
            // Scope must not be modified because, per the docs, init of field should not have access to any other fields or methods of object
            const string err = field->typeChecking(prog, scope);
            if(err.compare("")){
                cout << "type checking error in field" << endl;
                return err;
            }
        }
    }

    // Type checking on each methods
    for(Method *method: methods){
        if(method){
            cout << "Performing type checking on method " << method->getName() << endl;
            const string err = method->typeChecking(prog, scope);
            if(err.compare("")){
                cout << "type checking error in method" << endl;
                return err;
            }
        }
    }

    return "";
}

ClassBody::ClassBody(){}
