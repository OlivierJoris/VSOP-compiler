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

Method::Method(const string name, Formals* formals, const string retType, Block* block): name(name), formals(formals), retType(retType), block(block){}

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

const Expr* Method::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    // Check return type
    bool known = checkKnownType(classesMap, retType);
    if(known){
        cout << "Return type of " << name << " known" << endl;
    }else{
        cout << "Return type of " << name << " unknown" << endl;
        return this;
    }

    // Check formals if any
    if(formals != NULL){
        cout << "Checking formals" << endl;
        formals->checkUsageUndefinedType(classesMap);
    }else{
        cout << "No formals to check" << endl;
    }

    return NULL;
}

Call::Call(Expr *objExpr, const string methodName, Args *listExpr): objExpr(objExpr), methodName(methodName), listExpr(listExpr){}

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

New::New(const string typeName): typeName(typeName){}

string New::eval() const
{
    return "New(" + New::typeName + ")";
}

ObjectIdentifier::ObjectIdentifier(const string identifier): identifier(identifier){}

string ObjectIdentifier::eval() const 
{
    return ObjectIdentifier::identifier;
}

Self::Self(){}

string Self::eval() const
{
    return "self";
}

