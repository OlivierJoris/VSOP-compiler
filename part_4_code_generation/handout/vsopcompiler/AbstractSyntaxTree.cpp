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
    // Add Object class
    vector<Field*> fields;
    vector<Method*> methods;

    Formals *printFormals = new Formals();
    Formals *printBoolFormals = new Formals();
    Formals *printIntFormals = new Formals();
    Formals *inputFormals = new Formals();
    Formals *inputBoolFormals = new Formals();
    Formals *inputIntFormals = new Formals();
    printFormals->addFormal(new Formal("s", "string", 0, 0));
    printBoolFormals->addFormal(new Formal("b", "bool", 0, 0));
    printIntFormals->addFormal(new Formal("i", "int32", 0, 0));
    Method *print = new Method("print", printFormals, "Object", NULL, 0, 0);
    Method *printBool = new Method("printBool", printBoolFormals, "Object", NULL, 0, 0);
    Method *printInt32 = new Method("printInt32", printIntFormals, "Object", NULL, 0, 0);
    Method *inputLine = new Method("inputLine", inputFormals, "string", NULL, 0, 0);
    Method *inputBool = new Method("inputBool", inputBoolFormals, "bool", NULL, 0, 0);
    Method *inputInt = new Method("inputInt32", inputIntFormals, "int32", NULL, 0, 0);
    Class *object = new Class("Object", "", fields, methods, 0, 0);
    
    object->addMethod(inputInt);
    object->addMethod(inputBool);
    object->addMethod(inputLine);
    object->addMethod(printInt32);
    object->addMethod(printBool);
    object->addMethod(print);

    object->methodsMap.insert(pair<string, Method*>("print", print));
    object->methodsMap.insert(pair<string, Method*>("printBool", printBool));
    object->methodsMap.insert(pair<string, Method*>("printInt32", printInt32));
    object->methodsMap.insert(pair<string, Method*>("inputLine", inputLine));
    object->methodsMap.insert(pair<string, Method*>("inputBool", inputBool));
    object->methodsMap.insert(pair<string, Method*>("inputInt32", inputInt));
    Program::classesMap.insert(pair<string, Class*>("Object", object));
}

void Program::checkRedefinition()
{
    for(auto it = classes.rbegin(); it != classes.rend(); ++it)
    {
        Class *cls = *it;
        // Check class redefinition
        string className = cls->getName();
        if(classesMap.find(className) != classesMap.end())
            errors.push_back(to_string(cls->getLine()) + ":" + to_string(cls->getColumn()) + ": " + "semantic error: " + " redefinition of class " + className);
        
        else 
            classesMap[className] = cls;

        // Check field redefinition in current class
        vector<Field*> fields = cls->getFields();
        for(auto it = fields.rbegin(); it != fields.rend(); ++it)
        {
            Field *field = *it;
            string fieldName = field->getName();
            if(cls->fieldsMap.find(fieldName) != cls->fieldsMap.end())
                errors.push_back(to_string(field->getLine()) + ":" + to_string(field->getColumn()) + ": " + "semantic error: " + "redefinition of field " + fieldName);
            else
                cls->fieldsMap[fieldName] = field;
        }

        // Check method redefinition in current class
        vector<Method*> methods = cls->getMethods();
        for(auto it = methods.rbegin(); it != methods.rend(); ++it)
        {
            Method *method = *it;
            string methodName = method->getName();
            if(cls->methodsMap.find(methodName) != cls->methodsMap.end())
                errors.push_back(to_string(method->getLine()) + ":" + to_string(method->getColumn()) + ": " + "semantic error: " + "redefinition of method " + methodName);
            else
                cls->methodsMap[methodName] = method;
            
            // Check formal redefinition in current method
            if(!method->getFormalsPointer())
                continue;

            vector<Formal*> formals = method->getFormals();
            for(auto it = formals.rbegin(); it != formals.rend(); ++it)
            {
                Formal *formal = *it;
                string formalName = formal->getName();
                if(method->formalsMap.find(formalName) != method->formalsMap.end())
                    errors.push_back(to_string(formal->getLine()) + ":" + to_string(formal->getColumn()) + ": " + "semantic error: " + "redefinition of the formal " + formalName);
                else 
                    method->formalsMap[formalName] = formal;
            }
        }
    }
}

void Program::checkInheritance()
{
    set<string> parentSet;

    for(Class *cls: classes)
    {
        string parent = cls->getParent();
        while(parent != "Object")
        {
            // Cycle in inheritance
            if(parentSet.find(parent) != parentSet.end())
            {
                errors.push_back(to_string(cls->getLine()) + ":" + to_string(cls->getColumn()) + ": " + "semantic error: " + "class " + cls->getName() + " cannot extends parent class " + parent);
                break;
            }
            else
            {
                // Parent class has not been defined
                if(classesMap.find(parent) == classesMap.end())
                {
                    errors.push_back(to_string(cls->getLine()) + ":" + to_string(cls->getColumn()) + ": " + "semantic error: " + "class " + parent + " is not defined");
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
    // Check for each class
    for(Class *cls: classes)
    {
        // Check overridden fields in current class
        for(Field *field: cls->getFields())
        {
            string parent = cls->getParent();
            while(parent != "Object")
            {
                // Parent class has not been defined
                if(classesMap.find(parent) == classesMap.end())
                    break; 
            
                if(classesMap[parent]->fieldsMap.find(field->getName()) != classesMap[parent]->fieldsMap.end())
                    errors.push_back(to_string(field->getLine()) + ":" + to_string(field->getColumn()) + ": " + "semantic error: " + "field " + field->getName() + " of class " + cls->getParent() + " is overriden");
                
                parent = classesMap[parent]->getParent();
            }
        }

        // Check for overridden methods with different args and/or return type in current class
        for(Method *method: cls->getMethods())
        {
            string parent = cls->getParent();
            while(parent != "Object")
            {
                // Parent class has not been defined
                if(classesMap.find(parent) == classesMap.end())
                    break; 

                if(classesMap[parent]->methodsMap.find(method->getName()) != classesMap[parent]->methodsMap.end())
                {
                    Method *m =  classesMap[parent]->methodsMap[method->getName()];
                    // Check if matching return type
                    if(m->getRetType() != method->getRetType())
                        errors.push_back(to_string(method->getLine()) + ":" + to_string(method->getColumn()) + ": " + "semantic error: " + "method " + method->getName() + " of class " + cls->getParent() + " overriden with type " + method->getRetType() + " but parent type was " + m->getRetType());
                    
                    // Check if matching number of formal arguments
                    if(m->getFormalsPointer()){
                        if(m->getFormals().size() != method->getFormals().size())
                        {
                        errors.push_back(to_string(method->getLine()) + ":" + to_string(method->getColumn()) + ": " + "semantic error: " + "method " + method->getName() + " of class " + cls->getParent() + " overriden with " + to_string(method->getFormals().size()) + " formals but parent class has " + to_string(m->getFormals().size()) + " formals");
                        break;
                        }

                        // Check if matching formal arguments
                        unsigned int i = 0;
                        unsigned int nbFormals = (unsigned int)method->getFormals().size();
                        for(Formal *formal: method->getFormals())
                        {
                            if(m->getFormals(i)->getName() != formal->getName())
                                errors.push_back(to_string(formal->getLine()) + ":" + to_string(formal->getColumn()) + ": " + "semantic error: " + "method " + method->getName() + " of class " + cls->getParent() + " overriden with " + formal->getName() + " as formal name in place " + to_string(nbFormals-i) + " but parent class has " + m->getFormals(i)->getName() + " as formal name in this position");
                            
                            if(m->getFormals(i)->getType() != formal->getType())
                                errors.push_back(to_string(formal->getLine()) + ":" + to_string(formal->getColumn()) + ": " + "semantic error: " + "method " + method->getName() + " of class " + cls->getParent() + " overriden with " + formal->getType() + " as formal type in place " + to_string(nbFormals-i) + " but parent class has " + m->getFormals(i)->getType() + " as formal type in this position");

                            i+=1;
                        }
                    }
                }

                parent = classesMap[parent]->getParent();
            }
        }
    }
}

string Program::dumpAST(bool annotated) const 
{
    auto firstClass = Program::classes.rbegin();
    string program = (*firstClass)->dumpAST(annotated);

    for(auto it = Program::classes.rbegin() + 1; it != Program::classes.rend(); ++it)
        program += "\n, " + (*it)->dumpAST(annotated);
    
    return "[" + program + "]";
}

const string Program::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check each class
    for(Class *cls: classes){
        const string check = cls->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }
    return "";
}

string Program::checkMain() const {
    // Check if Main class
    auto mainClass = classesMap.find("Main");
    if(mainClass != classesMap.end()){
        // Check if main method
        Class *main = (*mainClass).second;
        Method *mainMethod = NULL;
        vector<Method*> methods = main->getMethods();
        for(Method *method: methods){
            if(method && !(method->getName().compare("main")))
                mainMethod = method;
        }

        if(!mainMethod)
            return to_string(main->getLine()) + ":" + to_string(main->getColumn()) + ": semantic error: missing main method.";

        // Check return type
        if(mainMethod->getRetType().compare("int32"))
            return to_string(mainMethod->getLine()) + ":" + to_string(mainMethod->getColumn()) + ": semantic error: main method return type must be int32.";

        // Check formal arguments
        if(mainMethod->getFormals().size() > 0)
            return to_string(mainMethod->getLine()) + ":" + to_string(mainMethod->getColumn()) + ": semantic error: main method must not have arguments.";

    }else{
        return  "1:1: semantic error: missing Main class.";
    }

    return "";
}

const string Program::typeChecking(const Program*, string, bool, vector<pair<string, Expr*>>) {
    // Type checking on each class
    for(auto cls = classes.begin(); cls != classes.end(); cls++){
        if(*cls){
            const string err = (*cls)->typeChecking(this, (*cls)->getName(), false, vector<pair<string, Expr*>>());
            if(err.compare(""))
                return err;
        }
    }

    return "";
}

llvm::Value *Program::generateCode(Program *program, Class* cls,const std::string &fileName){
    // Generate code on each class
    for(auto clas = classes.rbegin(); clas != classes.rend(); clas++){
        if(*clas){
            (*clas)->generateCode(program, *clas, fileName);
        }
    }

    return NULL;
}

Unit::Unit(const int line, const int column){
    this->line = line;
    this->column = column;
    this->type = "unit";
}

string Unit::dumpAST(bool annotated) const
{
    if(annotated)
        return "() : unit";
    else
        return "unit";
}

llvm::Value *Unit::generateCode(Program *program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);

    return llvm::ConstantPointerNull::get((llvm::PointerType*) llvm->getType("unit"));;
}
