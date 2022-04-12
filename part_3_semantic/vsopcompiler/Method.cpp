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

const string Method::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // First, we need to perform type checking on the formals (should never return error)
    if(formals){
        /* The scope does not really matter because should not have type errors in formals since
        declared types of formals are checked in checkUsageUndefinedType */
        const string err = formals->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "Error in formal" << endl;
            return err;
        }
    }

    if(block){
        // Then, we can perform type checking on the body (block) of the method
        const string err = block->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "type checking error in method body" << endl;
            return err;
        }
        // Finally, we need to check that the type of the body (block) matches the type of the return
        if(retType.compare(block->type)){
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":"
                + "body type does not match return type of method. Expected "
                + retType + " but is " + block->type + ".";
            cout << "Error in ret type" << endl;
            return err;
        }
    }else{
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "method is missing body.";
        return err;
    }

    return "";
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

const string Call::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Type checking on the expr representing the left-hand side
    if(objExpr){
        const string err = objExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Type checking on each argument
    if(listExpr){
        const string err = listExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // TODO check that type of objExpr has a method methodName with the same number of args

    // TODO check that the types of the args match types of args of method

    // TODO set type of call as type of return of method

    return "";
}

New::New(const string typeName, const int line, const int column): typeName(typeName){
    this->line = line;
    this->column = column;
    this->type = typeName;
}

string New::eval() const
{
    return "New(" + New::typeName + ")";
}

const Expr* New::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check type name
    bool known = checkKnownType(classesMap, typeName);
    if(known){
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

const string ObjectIdentifier::typeChecking(const Program*, string, vector<pair<string, Expr*>> scope){
    // Check if object identifier is in scope
    Expr *obj = NULL;
    for(auto it = scope.crbegin(); it != scope.crend(); it++){
        if((*it).first.compare(identifier) == 0){
            obj = (*it).second;
            break;
        }
    }

    if(!obj){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + identifier + " is not in scope.";
        return err;
    }

    // Set type of object identifier as type of same object in scope
    type = obj->type;

    return "";
}

Self::Self(const int line, const int column){
    this->line = line;
    this->column = column;
}

string Self::eval() const
{
    return "self";
}

const string Self::typeChecking(const Program*, string currentClass, vector<pair<string, Expr*>>){
    // Set type as current class.
    type = currentClass;

    return "";
}
