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

string Args::dumpAST(bool annotated) const
{
    string exprList = "";

    if(Args::exprList.size() != 0)
    {
        auto firstFormal = Args::exprList.rbegin();
        exprList = (*firstFormal)->dumpAST(annotated);

        for(auto it = Args::exprList.rbegin() + 1; it != Args::exprList.rend(); ++it)
            exprList += ", " + (*it)->dumpAST(annotated);
    }

    return "[" + exprList + "]";
}

const string Args::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    if(exprList.size() == 0)
        return "";
    
    // Check for each expression
    for(Expr *expr: exprList){
        const string check = expr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string Args::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // First, check each expression
    for(Expr* expr: exprList){
        if(expr){
            const string err = expr->typeChecking(prog, currentClass, inFieldInit, scope);
            if(err.compare(""))
                return err;
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

llvm::Value *Args::generateCode(Program *Program, Class* cls,const std::string &fileName){
    return NULL;
}
