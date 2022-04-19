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

string Class::dumpAST(bool annotated) const
{
    string fields = "";    

    if(Class::fields.size() != 0)
    {
        auto firstField = Class::fields.rbegin();
        fields = (*firstField)->dumpAST(annotated);

        for(auto it = Class::fields.rbegin() + 1; it != Class::fields.rend(); ++it)
            fields += ", " + (*it)->dumpAST(annotated);
    }

    string methods = "";

    if(Class::methods.size() != 0)
    {
        auto firstMethod = Class::methods.rbegin();
        methods = "\n" + (*firstMethod)->dumpAST(annotated);

        for(auto it = Class::methods.rbegin() + 1; it != Class::methods.rend(); ++it){
            methods += "\n";
            methods += ", " + (*it)->dumpAST(annotated);
        }
    }
    
    return "Class(" + Class::name + ", " + Class::parent + ", " + "[" + fields + "]" + ", " + "[" + methods + "]" + ")";
}

const string Class::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check fields
    for(Field *field: fields){
        const string check = field->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check methods
    for(Method *method: methods){
        const string check = method->checkUsageUndefinedType(classesMap);
        if (check.compare(""))
            return check;
    }

    return "";
}

const string Class::typeChecking(const Program* prog, string currentClass, bool, vector<pair<string, Expr*>> scope){
    // Type checking on each field
    for(Field *field: fields){
        if(field){
            // Scope must not be modified because, per the docs, init of field should not have access to any other fields or methods of object
            const string err = field->typeChecking(prog, currentClass, true, scope);
            if(err.compare(""))
                return err;
        }
    }

    // Add each field (including from ancestors) inside the scope
    vector<pair<string, Expr*>> extendedScope;
    string curClass = currentClass;
    while(curClass.compare("")){
        auto clsMap = prog->classesMap.find(curClass);
        if(clsMap != prog->classesMap.end()){
            Class *cls = (*clsMap).second;
            if(cls){
                vector<Field*> fields = cls->getFields();
                for(Field *field: fields){
                    if(field)
                        extendedScope.push_back(pair<string, Expr*>(field->getName(), field->getExpr()));
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
            const string err = method->typeChecking(prog, currentClass, false, scope);
            if(err.compare(""))
                return err;
        }
    }

    return "";
}

ClassBody::ClassBody(){}
