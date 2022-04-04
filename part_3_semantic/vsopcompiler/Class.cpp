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

Class::Class(const string name, const string parent, vector<Field*>& fields, vector<Method*>& methods): name(name), parent(parent), fields(fields), methods(methods){}

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

const Expr* Class::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    // Check fields
    for(Field *field: fields){
        const Expr* check = field->checkUsageUndefinedType(classesMap);
        if(check == NULL) {
            cout << "No usage of not defined type for field " << field->getName() << endl;
        } else {
            cout << "Usage of not defined type for field " << field->getName() << endl;
            return check;
        }
    }

    // Check methods
    for(Method *method: methods){
        const Expr* check = method->checkUsageUndefinedType(classesMap);
        if (check == NULL) {
            cout << "No usage of not defined type for method " << method->getName() << endl;
        } else {
            cout << "Usage of not defined type for method " << method->getName() << endl;
            return check;
        }
    }

    return NULL;
}

ClassBody::ClassBody(){}
