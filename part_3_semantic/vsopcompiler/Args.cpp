/**
 * Implementation of the args type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Args.hpp"
#include "Expr.hpp"
#include "Class.hpp"

using namespace std;

Args::Args(const int line, const int column)
{
    this->line = line;
    this->column = column;
}

string Args::eval() const
{
    string exprList = "";

    if(Args::exprList.size() != 0)
    {
        auto firstFormal = Args::exprList.rbegin();
        exprList = (*firstFormal)->eval();

        for(auto it = Args::exprList.rbegin() + 1; it != Args::exprList.rend(); ++it)
            exprList += ", " + (*it)->eval();
    }

    return "[" + exprList + "]";
}

const Expr* Args::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    if(exprList.size() == 0)
        return NULL;
    
    // Check for each expression
    for(Expr *expr: exprList){
        const Expr* check = expr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

const string Args::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    // First, check each expression
    for(Expr* expr: exprList){
        if(expr){
            const string err = expr->typeChecking(prog, scope);
            if(err.compare("")){
                cout << "Error while checking expr" << endl;
                return err;
            }
        }
    }

    /* Then, set type of list as type of last expr in list.
    ! last expr is at front of vector due to how bison works */
    if(exprList.size() > 0){
        Expr* last = exprList.front();
        if(last){
            type = last->type;
        }
    }

    return "";
}
