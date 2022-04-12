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
        }else
            cout << "Ok type checking formals" << endl;
    }

    if(block){
        cout << "Starting type checking on block" << endl;
        // Then, we can perform type checking on the body (block) of the method
        const string err = block->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "type checking error in method body" << endl;
            return err;
        }else
            cout << "Ok type checking on block" << endl;
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

static bool checkPrimitiveType(const string& toCheck){
    if(toCheck.compare("int32") == 0)
        return true;
    if(toCheck.compare("bool") == 0)
        return true;
    if(toCheck.compare("string") == 0)
        return true;
    if(toCheck.compare("unit") == 0)
        return true;
    return false;
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

    // Check that type of objExpr has a method named methodName
    string typeOfLHS = "";
    if(objExpr)
        typeOfLHS = objExpr->type;
    else // if no objExpr, dispatch with self (thus, currentClass)
        typeOfLHS = currentClass;
    
    if(!typeOfLHS.compare("")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":<id> has no type.";
        return err;
    }

    // Find class
    auto clsMap = prog->classesMap.find(typeOfLHS);
    if(clsMap == prog->classesMap.end()){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":type " + typeOfLHS + " not found.";
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
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":<id> has no method " + methodName;
        return err;
    }

    // Check if same number of args
    size_t nbFormals = method->getFormals().size();
    size_t nbArgs = listExpr->getNumberExpr();
    if(nbFormals != nbArgs){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + methodName + "has " +
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
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":formal " +
                to_string(it) + " must be of type " + formalType + ". Given argument is of type " + argType + ".";
            return err;
        }
    }

    // Set type of call as type of return of method
    type = method->getRetType();

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
