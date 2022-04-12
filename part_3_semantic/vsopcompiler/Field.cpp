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
    }
}

string Field::eval() const
{
    string initExpr = "";

    if(Field::initExpr)
        initExpr = ", " + Field::initExpr->eval();

    return "Field(" + Field::name + ", " + Field::type + initExpr + ")";
}

const Expr* Field::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check type of field
    bool known = checkKnownType(classesMap, type);
    if(!known)
        return this;

    // Check init expr if any
    if(initExpr){
        const Expr* check = initExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

const string Field::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    if(initExpr){
        // First, perform type checking on the field initializer if any
        const string err = initExpr->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "type checking error in field initializer" << endl;
            return err;
        }

        // Then, check if type of field initializer matches static type of field
        if(type.compare(initExpr->type)){
            string lineNumber = to_string(initExpr->getLine());
            string columnNumber = to_string(initExpr->getColumn());
            const string err = lineNumber + ":" + columnNumber + ":" + "initializer of field has not expected type. Expected " + type + " but is " + initExpr->type +".";
            cout << err << endl;
            return err;
        }
    }

    return "";
}
