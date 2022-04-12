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

const Expr* Let::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check expr used in initialize if any
    if(initExpr){
        const Expr* check = initExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check expr used in scope if any
    if(scopeExpr){
        const Expr* check = scopeExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

const string Let::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    if(initExpr){
        // Type checking on initExpr
        const string err = initExpr->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "Error type checking let initExpr" << endl;
            return err;
        }

        // Check if type of initExpr is the same as the type declared
        if(Let::type.compare(initExpr->type)){
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "type of initializer does not match expected type. Expected " + Let::type +
                " but is " + initExpr->type + ".";
        }
    }

    if(scopeExpr){
        // Type checking of body of let
        const string err = scopeExpr->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "Error type checking let scopeExpr" << endl;
            return err;
        }

        // Type of let is type of body,
       Expr::type = scopeExpr->type;
    }

    return "";
}
