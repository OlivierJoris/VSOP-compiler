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
#include "TypeChecking.hpp"

using namespace std;

Method::Method(const string name, Formals* formals, const string retType, Block* block, const int line, const int column): name(name), formals(formals), retType(retType), block(block){
    this->line = line;
    this->column = column;
}

vector<Formal*> Method::getFormals() {return formals->getFormals();}
Formal* Method::getFormals(unsigned int i) {return formals->getFormals(i);}

string Method::eval() const 
{
    string formals = "[]";
    string block = "[]";

    if(Method::formals)
        formals = Method::formals->eval();
    
    if(Method::block)
        block = Method::block->eval();

    return "Method(" + Method::name + ", " + formals + ", " + Method::retType + ", " + block + ")";
}

const Expr* Method::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check return type
    bool known = checkKnownType(classesMap, retType);
    if(!known){
         cout << "Return type of " << name << " unknown" << endl;
        return this;
    }

    // Check formals if any
    if(formals){
        const Expr* check = formals->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check block if any
    if(block){
        const Expr* check = block->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

Call::Call(Expr *objExpr, const string methodName, Args *listExpr, const int line, const int column): objExpr(objExpr), methodName(methodName), listExpr(listExpr){
    this->line = line;
    this->column = column;
}

string Call::eval() const
{
    string objExpr = "self";
   
    string listExpr = "[]";

    if(Call::listExpr)
        listExpr = Call::listExpr->eval();

    if(Call::objExpr)
        objExpr = Call::objExpr->eval();

    return "Call(" + objExpr + ", " + Call::methodName + ", " + listExpr + ")";
}

const Expr* Call::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check object expr if any
    if(objExpr){
        const Expr* check = objExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check the list of expressions if any
    if(listExpr){
        const Expr* check = listExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

New::New(const string typeName, const int line, const int column): typeName(typeName){
    this->line = line;
    this->column = column;
}

string New::eval() const
{
    return "New(" + New::typeName + ")";
}

const Expr* New::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check type name
    bool known = checkKnownType(classesMap, typeName);
    if(known){
        cout << "Type of new " << typeName << " known" << endl;
        return NULL;
    }else{
        cout << "Return type of " << typeName << " unknown" << endl;
        return this;
    }
}

ObjectIdentifier::ObjectIdentifier(const string identifier, const int line, const int column): identifier(identifier){
    this->line = line;
    this->column = column;
}

string ObjectIdentifier::eval() const 
{
    return ObjectIdentifier::identifier;
}

Self::Self(const int line, const int column){
    this->line = line;
    this->column = column;
}

string Self::eval() const
{
    return "self";
}
