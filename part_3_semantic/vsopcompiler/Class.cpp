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
#include "Method.hpp"
#include "AbstractSyntaxTree.hpp"

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

const string Class::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check fields
    for(Field *field: fields){
        const string check = field->checkUsageUndefinedType(classesMap);
        if(check.compare("")) {
            cout << "Usage of not defined type for field " << field->getName() << endl;
            return check;
        }
    }

    // Check methods
    for(Method *method: methods){
        const string check = method->checkUsageUndefinedType(classesMap);
        if (check.compare("")) {
            cout << "Usage of not defined type for method " << method->getName() << endl;
            return check;
        }
    }

    return "";
}

const string Class::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Type checking on each field
    for(Field *field: fields){
        if(field){
            cout << "Performing type checking on field " << field->getName() << endl;
            // Scope must not be modified because, per the docs, init of field should not have access to any other fields or methods of object
            const string err = field->typeChecking(prog, currentClass, scope);
            if(err.compare("")){
                cout << "type checking error in field" << endl;
                return err;
            }else
                cout << "End type checking on field " << field->getName() << endl;
        }
    }

    // Add each field (including from ancestors) inside the scope
    cout << "** Updating scope" << endl;
    vector<pair<string, Expr*>> extendedScope;
    string curClass = currentClass;
    while(curClass.compare("")){
        cout << "Working on class " << curClass << endl;
        auto clsMap = prog->classesMap.find(curClass);
        if(clsMap != prog->classesMap.end()){
            Class *cls = (*clsMap).second;
            if(cls){
                vector<Field*> fields = cls->getFields();
                for(Field *field: fields){
                    if(field){
                        cout << "Adding field " << field->getName() << endl;
                        extendedScope.push_back(pair<string, Expr*>(field->getName(), field->getExpr()));
                    }
                }
                curClass = cls->getParent();
            }else
                break;
        }else
            break;
    }

    // Add in reverse order to respect precedence between fields with the same name
    for(auto it = extendedScope.crbegin(); it < extendedScope.crend(); it++)
        scope.push_back((*it));


    // Type checking on each methods
    for(Method *method: methods){
        if(method){
            cout << "Performing type checking on method " << method->getName() << endl;
            const string err = method->typeChecking(prog, currentClass, scope);
            if(err.compare("")){
                cout << "type checking error in method" << endl;
                return err;
            }else
                cout << "End type checking on method " << method->getName() << endl;
        }
    }

    return "";
}

ClassBody::ClassBody(){}
