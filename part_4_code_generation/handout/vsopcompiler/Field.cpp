/**
 * Implementation of the class type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <iostream>
#include <string>
#include <map>

#include "Field.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "Literals.hpp"
#include "TypeChecking.hpp"

using namespace std;

Field::Field(const string name, const string type, Expr *initExpr, const int line, const int column): name(name), type(type), initExpr(initExpr){
    this->line = line;
    this->column = column;

    if(!initExpr){
        Field::defaultInitialized = true;
        // Need to add new identifier inside scope
        if(!type.compare("int32")){
            Field::initExpr = new IntegerLiteral(0, getLine(), getColumn());
        }else if(!type.compare("string")){
            Field::initExpr = new StringLiteral("", getLine(), getColumn());
        }else if(!type.compare("bool")){
            Field::initExpr = new BooleanLiteral(false, getLine(), getColumn());
        }else{
            Field::initExpr = new New(type, getLine(), getColumn());
        }
    }else
        Field::defaultInitialized = false;
}

string Field::dumpAST(bool annotated) const
{
    string initExpr = "";

    if(Field::initExpr && !defaultInitialized)
        initExpr = ", " + Field::initExpr->dumpAST(annotated);

    return "Field(" + Field::name + ", " + Field::type + initExpr + ")";
}

const string Field::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check type of field
    bool known = checkKnownType(classesMap, type);
    if(!known)
        return to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: field " + name + " is using an undefined type.";

    // Check init expr if any
    if(initExpr){
        const string check = initExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string Field::typeChecking(const Program* prog, string currentClass, bool inFieldInit,vector<pair<string, Expr*>> scope){
    if(initExpr){
        // First, perform type checking on the field initializer if any
        const string err = initExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Then, check if type of field initializer matches static type of field
        // Field initializer can be a child of static type
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
            if(!type.compare(ancestor)){
                validType = true;
                break;
            }
        }
        if(!validType){
            string lineNumber = to_string(initExpr->getLine());
            string columnNumber = to_string(initExpr->getColumn());
            const string err = lineNumber + ":" + columnNumber + ": semantic error: initializer of field has not expected type. Expected " + type + " but is " + initExpr->type +".";
            return err;
        }
    }

    Expr::type = Field::type;

    return "";
}

llvm::Value *Field::generateCode(Program *program, Class* cls, const std::string &fileName){
    llvm::Value *val;
    llvm::Type *llvmType;
    LLVM *llvm = LLVM::getInstance(program, fileName);

    if(initExpr)
        val = initExpr->generateCode(program, cls, fileName);
    else
    {
        llvmType = llvm->getType(type);

        if(type == "bool" || type == "int32")
            val = llvm::ConstantInt::get(llvmType, 0);
        if (type == "string")
            val = llvm->builder->CreateGlobalStringPtr("");
        else
            val = llvm::ConstantPointerNull::get(llvmType->getPointerTo()); 
    }

    return val;
}
