/**
 * Implementation of the AST for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "AbstractSyntaxTree.hpp"
#include "Args.hpp"
#include "Block.hpp"
#include "Class.hpp"
#include "Expr.hpp"
#include "Field.hpp"
#include "Formal.hpp"
#include "If.hpp"
#include "Let.hpp"
#include "Literals.hpp"
#include "Method.hpp"
#include "Operators.hpp"
#include "While.hpp"
#include "TypeChecking.hpp"

using namespace std;

Program::Program()
{
    Program::classesMap.insert(pair<string, Class *>("Object", NULL));
}

void Program::checkRedefinition()
{
    for(Class *cls: classes)
    {
        std::string className = cls->getName();
        if(classesMap.find(className) != classesMap.end())
            errors.push_back("redefinition of class " + className);
        else 
            classesMap[className] = cls;

        for(Field *field: cls->getFields())
        {
            std::string fieldName = field->getName();
            if(cls->fieldsMap.find(fieldName) != cls->fieldsMap.end())
                errors.push_back("redefinition of field " + fieldName);
            else
                cls->fieldsMap[fieldName] = field;
        }

        for(Method *method: cls->getMethods())
        {
            std::string methodName = method->getName();
            if(cls->methodsMap.find(methodName) != cls->methodsMap.end())
                errors.push_back("redefinition of method " + methodName);
            else
                cls->methodsMap[methodName] = method;
            

            for(Formal *formal: method->getFormals())
            {
                std::string formalName = formal->getName();
                if(method->formalsMap.find(formalName) != method->formalsMap.end())
                    errors.push_back("redefinition of the formal " + formalName);
                else 
                    method->formalsMap[formalName] = formal;
            }
        }
    }
}

void Program::checkInheritance()
{
    std::set<std::string> parentSet;

    for(Class *cls: classes)
    {
        std::string parent = cls->getParent();
        while(parent != "Object")
        {
            /* Cycle in inheritance */
            if(parentSet.find(parent) != parentSet.end())
            {
                errors.push_back("class " + cls->getName() + " cannot extends parent class " + parent);
                break;
            }
            else
            {
                /* Parent class has not been defined */
                if(classesMap.find(parent) == classesMap.end())
                {
                    errors.push_back("class " + parent + " is not defined");
                    break; 
                }

                parentSet.insert(parent);
                parent = classesMap[parent]->getParent();
            }
        }

        if(parentSet.size() > 0)
            parentSet.clear(); 
    }
}

void Program::checkOverrides()
{
    for(Class *cls: classes)
    {
        /* Field */
        for(Field *field: cls->getFields())
        {
            std::string parent = cls->getParent();
            while(parent != "Object")
            {
                /* Parent class has not been defined */
                if(classesMap.find(parent) == classesMap.end())
                    break; 
            
                if(classesMap[parent]->fieldsMap.find(field->getName()) != classesMap[parent]->fieldsMap.end())
                    errors.push_back("field " + field->getName() + " of class " + cls->getName() + " is overriden");
                
                parent = classesMap[parent]->getParent();
            }
        }

        for(Method *method: cls->getMethods())
        {
            std::string parent = cls->getParent();
            while(parent != "Object")
            {
                /* Parent class has not been defined */
                if(classesMap.find(parent) == classesMap.end())
                    break; 

                if(classesMap[parent]->methodsMap.find(method->getName()) != classesMap[parent]->methodsMap.end())
                {
                    Method *m =  classesMap[parent]->methodsMap[method->getName()];
                    if(m->getRetType() != method->getRetType())
                        errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with type " + method->getRetType() + " but parent type was " + m->getRetType());
                    
                    if(m->getFormals().size() != method->getFormals().size())
                    {
                        errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with " + std::to_string(method->getFormals().size()) + " formals but parent class has " + std::to_string(m->getFormals().size()) + " formals");
                        break;
                    }

                    unsigned int i = 0;
                    for(Formal *formal: method->getFormals())
                    {
                        if(m->getFormals(i)->getName() != formal->getName())
                            errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with " + formal->getName() + " as formal name in place " + std::to_string(i) + " but parent class has " + m->getFormals(i)->getName() + " as formal name in this position");
                        
                        if(m->getFormals(i)->getType() != formal->getType())
                            errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with " + formal->getType() + " as formal type in place " + std::to_string(i) + " but parent class has " + m->getFormals(i)->getType() + " as formal type in this position");
                    }
                }

                parent = classesMap[parent]->getParent();
            }
        }
    }
}

std::string Program::eval() const 
{
    auto firstClass = Program::classes.rbegin();
    string program = (*firstClass)->eval();

    for(auto it = Program::classes.rbegin() + 1; it != Program::classes.rend(); ++it)
        program += ", " + (*it)->eval();
    
    return "[" + program + "]";
}

const Expr* Program::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check each class
    for(Class *cls: classes){
        cout << "Starting check for class " << cls->getName() << endl;
        const Expr* check = cls->checkUsageUndefinedType(classesMap);
        if(check) {
            cout << "Usage of not defined type inside class " << cls->getName() << endl;
            return check;
        }
    }
    return NULL;
}

Unit::Unit(){}

string Unit::eval() const
{
    return "unit";
}
