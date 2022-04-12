/**
 * Implementation of the block type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <iostream>
#include <string>

#include "Block.hpp"
#include "Args.hpp"

using namespace std;

Block::Block(Args *exprList, const int line, const int column): exprList(exprList){
    this->line = line;
    this->column = column;
}

string Block::eval() const
{
    string listExpr = "[]";

    if(Block::exprList)
        listExpr = Block::exprList->eval();
    
    return listExpr;
}

const Expr* Block::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    if(exprList == NULL)
        return NULL;
    
    return exprList->checkUsageUndefinedType(classesMap);
}

const string Block::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    if(exprList){
        // First, need to check the expressions inside the block if any
        const string err = exprList->typeChecking(prog, currentClass, scope);
        if(err.compare("")){
            cout << "Error in exprlist check" << endl;
            return err;
        }
        
        // Then, set type of block as type of list of expressions (itself is type of last expr)
        type = exprList->type;
    }

    return "";
}
