/**
 * Implementation of types related to methods for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "Method.hpp"
#include "Block.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "Formal.hpp"
#include "Args.hpp"
#include "Literals.hpp"
#include "TypeChecking.hpp"

using namespace std;

Method::Method(const string name, Formals* formals, const string retType, Block* block, const int line, const int column): name(name), formals(formals), retType(retType), block(block){
    this->line = line;
    this->column = column;
}

vector<Formal*> Method::getFormals() {return formals->getFormals();}
Formal* Method::getFormals(unsigned int i) {return formals->getFormals(i);}

string Method::dumpAST(bool annotated) const 
{
    string formals = "[]";
    string block = "[]";

    if(Method::formals)
        formals = Method::formals->dumpAST(annotated);
    
    if(Method::block)
        block = Method::block->dumpAST(annotated);

    return "Method(" + Method::name + ", " + formals + ", " + Method::retType + ", " + block + ")";
}

const string Method::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check return type
    bool known = checkKnownType(classesMap, retType);
    if(!known)
        return to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: return type of method is not defined.";

    // Check formals if any
    if(formals){
        const string check = formals->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check block if any
    if(block){
        const string check = block->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string Method::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // First, we need to perform type checking on the formals (should never return error)
    if(formals){
        /* The scope does not really matter because should not have type errors in formals since
        declared types of formals are checked in checkUsageUndefinedType */
        const string err = formals->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
        
        // Add formals in scope
        for(Formal *formal: getFormals()){
            if(!formal->getType().compare("int32")){
                scope.push_back(pair<string, Expr*>(formal->getName(), new IntegerLiteral(0, getLine(), getColumn())));
            }else if(!formal->getType().compare("string")){
                scope.push_back(pair<string, Expr*>(formal->getName(), new StringLiteral("", getLine(), getColumn())));
            }else if(!formal->getType().compare("bool")){
                scope.push_back(pair<string, Expr*>(formal->getName(), new BooleanLiteral(false, getLine(), getColumn())));
            }else{
               scope.push_back(pair<string, Expr*>(formal->getName(), new New(formal->getType(), getLine(), getColumn())));
            }
        }
    }

    if(block){
        // Then, we can perform type checking on the body (block) of the method
        const string err = block->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Finally, we need to check that the type of the body (block) matches the type of the return
        // Get ancestors because body can be of type of child of expected type
        vector<string> ancestors;
        ancestors.push_back(block->type);
        if(!checkPrimitiveType(block->type)){ // Ancestor only if not primitive type
            string ancestor = block->type;
            while(ancestor.compare("")){
                auto clsMap = prog->classesMap.find(ancestor);
                if(clsMap != prog->classesMap.end()){
                    Class *cls = (*clsMap).second;
                    if(cls){
                        ancestor = cls->getParent();
                        ancestors.push_back(ancestor);
                    }else
                        break;
                }else
                    break;
            }
        }
        bool validType = false;
        for(string type: ancestors){
            if(!type.compare(retType)){
                validType = true;
                break;
            }
        }
        if(!validType){
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":"
                + " semantic error: body type does not match return type of method. Expected "
                + retType + " but is " + block->type + ".";
            return err;
        }
    }else{
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: method is missing body.";
        return err;
    }

    return "";
}

llvm::Value *Method::generateCode(Program *program, Class* cls, const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);
    llvm::Function *method = llvm->mdl->getFunction(cls->getName() + "__" + name);
    auto bloc = llvm::BasicBlock::Create(*(llvm->context), "entry", method);
    llvm->builder->SetInsertPoint(bloc);

    auto args = method->arg_begin() + 1;
    for(auto formal: formalsMap)
    {
        llvm::Value *arg = llvm->builder->CreateAlloca(llvm->getType(formal.second->getType()));
        llvm->builder->CreateStore(args, arg);
        program->variables[formal.first] = arg;
        args++;
    }

    auto ret = block->generateCode(program, cls, fileName);
    llvm->builder->CreateRet(ret);

    return NULL;
}

Call::Call(Expr *objExpr, const string methodName, Args *listExpr, const int line, const int column): objExpr(objExpr), methodName(methodName), listExpr(listExpr){
    this->line = line;
    this->column = column;
    if(!Call::objExpr)
        Call::objExpr = new Self(line, column);
}

string Call::dumpAST(bool annotated) const
{
    string objExpr = "self";
   
    string listExpr = "[]";

    if(Call::listExpr)
        listExpr = Call::listExpr->dumpAST(annotated);

    if(Call::objExpr)
        objExpr = Call::objExpr->dumpAST(annotated);

    auto newType = Call::methodType.find(methodName);

    if(annotated)
        return "Call(" + objExpr + ", " + Call::methodName + ", " + listExpr + ") : " + newType->second;
    else
        return "Call(" + objExpr + ", " + Call::methodName + ", " + listExpr + ")";
}

const string Call::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check object expr if any
    if(objExpr){
        const string check = objExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check the list of expressions if any
    if(listExpr){
        const string check = listExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string Call::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // Type checking on the expr representing the left-hand side
    if(objExpr){
        const string err = objExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Type checking on each argument
    if(listExpr){
        const string err = listExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Check that type of objExpr has a method named methodName
    string typeOfLHS = "";
    if(objExpr)
        typeOfLHS = objExpr->type;
    else // if no objExpr, dispatch with self (thus, currentClass)
        typeOfLHS = currentClass;
    
    if(!typeOfLHS.compare("")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: <id> has no type.";
        return err;
    }

    if(!typeOfLHS.compare(currentClass) && inFieldInit){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) +
            ": semantic error: cannot use method of object inside field initializer.";
        return err;
    }

    // Find class
    auto clsMap = prog->classesMap.find(typeOfLHS);
    if(clsMap == prog->classesMap.end()){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: type " + typeOfLHS + " not found.";
        return err;
    }

    // Check if class (or parent of class) has a method named methodName
    Class *cls = (*clsMap).second;
    Method *method = NULL;
    while(cls != NULL){
        auto methodMap = cls->methodsMap.find(methodName);
        if(methodMap != cls->methodsMap.end()){
            method = (*methodMap).second;
            break;
        }else{
            string parent = cls->getParent();
            auto parentMap = prog->classesMap.find(parent);
            if(parentMap != prog->classesMap.end()){
                cls = (*parentMap).second;
            }else
                cls = NULL;
        }
    }

    if(!method){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error <id> has no method " + methodName;
        return err;
    }

    // Check if same number of args
    size_t nbFormals = method->getFormals().size();
    size_t nbArgs = listExpr->getNumberExpr();
    if(nbFormals != nbArgs){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: " + methodName + "has " +
            to_string(nbFormals) + " formal arguments but " + to_string(nbArgs) + " were given.";
        return err;
    }

    // Check that the types of the args match the types of the formals
    vector<Formal*> formals = method->getFormals();
    vector<Expr*> args = listExpr->getExpr();
    for(size_t it = 0; it < formals.size(); ++it){
        string formalType = formals[it]->getType();
        string argType = args[it]->type;

        // Get ancestors of arg because can use child (oop)
        vector<string> ancestors;
        ancestors.push_back(argType);
        if(!checkPrimitiveType(argType)){ // Ancestor only if not primitive type
            string ancestor = argType;
            while(ancestor.compare("")){
                auto clsMap = prog->classesMap.find(ancestor);
                if(clsMap != prog->classesMap.end()){
                    Class *cls = (*clsMap).second;
                    if(cls){
                        ancestor = cls->getParent();
                        ancestors.push_back(ancestor);
                    }else
                        break;
                }else
                    break;
            }
        }

        // Check if formalType is equal to argType or one of its ancestor
        bool typeOk = false;
        for(string ancestor: ancestors){
            if(!ancestor.compare(formalType))
                typeOk = true;
        }
        if(!typeOk){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: formal " +
                to_string(it) + " must be of type " + formalType + ". Given argument is of type " + argType + ".";
            return err;
        }
    }

    // Set type of call as type of return of method
    type = method->getRetType();
    methodType[methodName] = method->getRetType();

    return "";
}

llvm::Value *Call::generateCode(Program *program, Class* cls, const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);

    auto arg = objExpr->generateCode(program, cls, fileName);

    auto table = llvm->builder->CreateStructGEP(llvm->mdl->getTypeByName(objExpr->type), arg, 0);
    table = llvm->builder->CreateLoad(table);

    int iMethod = program->methodsMap[objExpr->type][methodName];
    auto type = llvm->mdl->getTypeByName(objExpr->type + "VTable");
    auto method = llvm->builder->CreateStructGEP(type, table, iMethod);
    method = llvm->builder->CreateLoad(method);
    auto methodType = (llvm::FunctionType*) ((llvm::PointerType*) type->getStructElementType(iMethod))->getElementType();
    auto argType = methodType->getParamType(0);
    arg = (llvm::Argument*) llvm->builder->CreatePointerCast(arg, argType);

    std::vector<llvm::Value*> args;
    args.push_back(arg);
    int i = 1;
    for(auto arg : listExpr->getExpr()){
        if(arg->type == "unit")
            continue;

        auto argCode = arg->generateCode(program, cls, fileName);
        argCode = llvm->builder->CreatePointerCast(argCode, methodType->getParamType(i));
        args.push_back(argCode);
        i++;
    }

    auto methodCall = llvm->builder->CreateCall(methodType, method, args);

    return methodCall;
}

New::New(const string typeName, const int line, const int column): typeName(typeName){
    this->line = line;
    this->column = column;
    this->type = typeName;
}

string New::dumpAST(bool annotated) const
{
    if(annotated)
        return "New(" + New::typeName + ") : " + type;
    else
        return "New(" + New::typeName + ")";
}

const string New::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check type name
    bool known = checkKnownType(classesMap, typeName);
    if(known)
        return "";
    else
        return to_string(getLine()) + to_string(getColumn()) + ": semantic error: type " + typeName + " is not defined.";
}

llvm::Value *New::generateCode(Program *Program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(Program, fileName);
    return llvm->builder->CreateCall(llvm->mdl->getFunction(typeName + std::string("___new")));
}

ObjectIdentifier::ObjectIdentifier(const string identifier, const int line, const int column): identifier(identifier){
    this->line = line;
    this->column = column;
}

string ObjectIdentifier::dumpAST(bool annotated) const 
{
    if(annotated)
        return ObjectIdentifier::identifier + " : " + type;
    else
        return ObjectIdentifier::identifier;
}

const string ObjectIdentifier::typeChecking(const Program*, string, bool, vector<pair<string, Expr*>> scope){
    // Check if object identifier is in scope
    Expr *obj = NULL;
    for(auto it = scope.crbegin(); it != scope.crend(); it++){
        if((*it).first.compare(identifier) == 0){
            obj = (*it).second;
            break;
        }
    }

    if(!obj){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: " + identifier + " is not in scope.";
        return err;
    }

    // Set type of object identifier as type of same object in scope
    type = obj->type;

    return "";
}

llvm::Value *ObjectIdentifier::generateCode(Program *program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);
    llvm::Value *retObj;
    if(program->variables[identifier] != NULL){
        retObj = program->variables[identifier];
    }
    else{
        auto linkedClass = llvm->builder->GetInsertBlock()->getParent()->args().begin();
        if(identifier == "self"){
            return linkedClass;
        }
        else{
            retObj = llvm->builder->CreateStructGEP(llvm->mdl->getTypeByName(cls->getName()), linkedClass, program->fieldsMap[cls->getName()][identifier]);
        }
    }
    return llvm->builder->CreateLoad(retObj);
}

Self::Self(const int line, const int column){
    this->line = line;
    this->column = column;
}

string Self::dumpAST(bool annotated) const
{
    if(annotated)
        return "self : " + type;
    else
        return "self";
}

const string Self::typeChecking(const Program*, string currentClass, bool, vector<pair<string, Expr*>>){
    // Set type as current class.
    type = currentClass;

    return "";
}

llvm::Value *Self::generateCode(Program *program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);
    return llvm->builder->GetInsertBlock()->getParent()->args().begin();
}
