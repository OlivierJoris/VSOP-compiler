/**
 * Implementation of the class type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <stack>
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

llvm::Value *Class::generateCode(Program *program, Class* cls, const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);
    // Malloc
    auto malloc = llvm->mdl->getFunction("malloc");
    auto dataLayout = new llvm::DataLayout(llvm->mdl);
    auto size = dataLayout->getTypeAllocSizeInBits(llvm->mdl->getTypeByName(name));
    std::vector<llvm::Value*> args = {llvm::ConstantInt::get(llvm::Type::getInt64Ty(*(llvm->context)), size)};
    auto mallocCall = llvm->builder->CreateCall(malloc, args);

    // New method
    auto newMethod = llvm->mdl->getFunction(std::string("new_") + name);
    auto newBlock = llvm::BasicBlock::Create(*(llvm->context), "entry", newMethod);
    llvm->builder->SetInsertPoint(newBlock);

    // Parent class
    auto parentRef = llvm->builder->CreatePointerCast(mallocCall, llvm::PointerType::get(llvm->mdl->getTypeByName(parent), 0));
    auto parentInit = llvm->mdl->getFunction(std::string("init_") + parent);
    parentRef = llvm->builder->CreateCall(parentInit, {parentRef});

    // Child class
    auto childRef = llvm->builder->CreatePointerCast(parentRef, llvm::PointerType::get(llvm->mdl->getTypeByName(name), 0));
    auto childInit = llvm->mdl->getFunction(std::string("init_") + name);
    childRef = llvm->builder->CreateCall(childInit, {childRef});

    // Return
    llvm->builder->CreateRet(childRef);

    // Init method
    auto initMethod = llvm->mdl->getFunction(std::string("init_") + name);
    auto initBlock = llvm::BasicBlock::Create(*(llvm->context), "entry", initMethod);
    llvm->builder->SetInsertPoint(initBlock);

    // Vtable
    auto thisRef = initMethod->args().begin();
    auto vtable = llvm->builder->CreateStructGEP(llvm->mdl->getTypeByName(name), thisRef, 0);
    llvm->builder->CreateStore(llvm->mdl->getNamedGlobal(name + "_vtable"), vtable);

    std::stack<std::string> parentClasses = std::stack<std::string>();
        
    std::string parent = getParent();
    while(parent != "Object")
    {
        parentClasses.push(parent);
        parent = program->classesMap[parent]->getParent();
    }
    int i = 1;
    while(!parentClasses.empty())
    {
        std::string parentClass = parentClasses.top();
        parentClasses.pop();

        for(auto field: program->classesMap[parentClass]->getFields())
        {
            auto fieldValue = field->generateCode(program, this, fileName);
            auto fieldStruct = llvm->builder->CreateStructGEP(llvm->mdl->getTypeByName(name), thisRef, i);
            llvm->builder->CreateStore(fieldValue, fieldStruct);
            program->fieldsMap[name][field->getName()] = i;
            ++i;
        }   
    }

    llvm->builder->CreateRet(thisRef);

    for(auto method: methods)
        method->generateCode(program, this, fileName);

    return NULL;
}

ClassBody::ClassBody(){}
