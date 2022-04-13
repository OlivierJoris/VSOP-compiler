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

using namespace std;

Let::Let(const string name, const string type, Expr *scopeExpr, Expr *initExpr, const int line, const int column): name(name), type(type), scopeExpr(scopeExpr), initExpr(initExpr){
    this->line = line;
    this->column = column;
}

string Let::eval() const
{
    string initExpr = "";

    if(Let::initExpr)
        initExpr = ", " + Let::initExpr->eval();

    return "Let(" + Let::name + ", " + Let::type + initExpr + ", " + Let::scopeExpr->eval() + ")";
}

const string Let::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
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

const string Let::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    if(initExpr){
        // Type checking on initExpr
        cout << "Start type checking on init expr of let" << endl;
        const string err = initExpr->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "Error type checking let initExpr" << endl;
            return err;
        }else
            cout << "Ok type checking on init expr of let" << endl;

        // Check if type of initExpr is the same as the type declared
        if(Let::type.compare(initExpr->type)){
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "type of initializer does not match expected type. Expected " + Let::type +
                " but is " + initExpr->type + ".";
        }
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
        cout << "Start type checking on scope expr of let" << endl;
        // Type checking of body of let
        const string err = scopeExpr->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "Error type checking let scopeExpr" << endl;
            return err;
        }else
            cout << "Ok type checking on scope expr of let" << endl;

        // Type of let is type of body,
       Expr::type = scopeExpr->type;
    }

    return "";
}
