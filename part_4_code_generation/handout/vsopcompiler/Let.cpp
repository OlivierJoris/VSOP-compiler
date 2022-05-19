/**
 * Implementation of the let type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <iostream>
#include <string>
#include <map>
#include <string>

#include "Let.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "Literals.hpp"
#include "TypeChecking.hpp"

using namespace std;

Let::Let(const string name, const string type, Expr *scopeExpr, Expr *initExpr, const int line, const int column): name(name), type(type), scopeExpr(scopeExpr), initExpr(initExpr){
    this->line = line;
    this->column = column;
}

string Let::dumpAST(bool annotated) const
{
    string initExpr = "";

    if(Let::initExpr)
        initExpr = ", " + Let::initExpr->dumpAST(annotated);

    if(annotated)
        return "Let(" + Let::name + ", " + Let::type + initExpr + ", " + Let::scopeExpr->dumpAST(annotated) + ") : " + Expr::type;
    else
        return "Let(" + Let::name + ", " + Let::type + initExpr + ", " + Let::scopeExpr->dumpAST(annotated) + ")";
}

const string Let::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    bool known = checkKnownType(classesMap, type);
    if(!known)
        return to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: type " + type + " is an undefined type.";

    // Check expr used in initialize if any
    if(initExpr){
        const string check = initExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check expr used in scope if any
    if(scopeExpr){
        const string check = scopeExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string Let::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    if(initExpr){
        // Type checking on initExpr
        const string err = initExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Check if type of initExpr is the same as the type declared
        // initExpr can also be a child of the type declared
        vector<string> ancestors;
        ancestors.push_back(initExpr->type);
        if(!checkPrimitiveType(initExpr->type)){ // Ancestor only if not primitive type
            string ancestor = initExpr->type;
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
        for(string ancestor: ancestors){
            if(!Let::type.compare(ancestor)){
                validType = true;
                break;
            }
        }
        if(!validType){
            cout << "Let type = " << Let::type << endl;
            cout << "Init expr type = " << initExpr->type << endl;
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                " semantic error: type of initializer does not match expected type. Expected " + Let::type +
                " but is " + initExpr->type + ".";
            return err;
        }

        initExpr->type = Let::type;
    }

    // Need to add new identifier inside scope
    if(initExpr){
        scope.push_back(pair<string, Expr*>(name, initExpr));
    }else if (!type.compare("int32")){
        IntegerLiteral *intLit = new IntegerLiteral(0, getLine(), getColumn());
        scope.push_back(pair<string, Expr*>(name, intLit));
    }else if (!type.compare("string")){
        StringLiteral *stringLit = new StringLiteral("", getLine(), getColumn());
        scope.push_back(pair<string, Expr*>(name, stringLit));
    }else if (!type.compare("bool")){
        BooleanLiteral *boolLit = new BooleanLiteral(false, getLine(), getColumn());
        scope.push_back(pair<string, Expr*>(name, boolLit));
    }else{
        Expr* expr = new New(type, getLine(), getColumn());
        scope.push_back(pair<string, Expr*>(name, expr));
    }

    if(scopeExpr){
        // Type checking of body of let
        const string err = scopeExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Type of let is type of body,
       Expr::type = scopeExpr->type;
    }

    return "";
}

llvm::Value *Let::generateCode(Program *program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);

    auto let = llvm->builder->CreateAlloca(llvm->getType(initExpr->type));
    llvm::Value *llvmInit;
    if(!initExpr){
        auto llvmType = llvm->getType(type);
        if(type == "bool" || type == "int32"){
            llvmInit = llvm::ConstantInt::get(llvmType, 0);
        }
        else if(type == "string"){
            llvmInit = llvm->builder->CreateGlobalStringPtr("");
        }
        else{
            llvmInit = llvm::ConstantPointerNull::get((llvm::PointerType *) llvmType);
        }
    } else {
        llvmInit = initExpr->generateCode(program, cls, fileName);
        llvmInit = llvm->builder->CreatePointerCast(llvmInit, llvm->getType(initExpr->type));
    }

    llvm->builder->CreateStore(llvmInit, let);

    program->variables[name] = let;

    auto llvmScope = scopeExpr->generateCode(program, cls, fileName);

    return llvmScope;
}
