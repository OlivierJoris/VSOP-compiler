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

string Block::dumpAST(bool annotated) const
{
    string listExpr = "[]";

    if(Block::exprList){
        listExpr = Block::exprList->dumpAST(annotated);
        if(annotated)
            listExpr += (" : " + type);
    }
    
    return listExpr;
}

const string Block::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    if(exprList == NULL)
        return "";
    
    return exprList->checkUsageUndefinedType(classesMap);
}

const string Block::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    if(exprList){
        // First, need to check the expressions inside the block if any
        const string err = exprList->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
        
        // Then, set type of block as type of list of expressions (itself is type of last expr)
        type = exprList->type;
    }

    return "";
}

llvm::Value *Block::generateCode(Program *program, Class* cls, const std::string &fileName){
    llvm::Value *code;
    std::vector<Expr*> exprs = exprList->getExpr();
    for(auto it = exprs.rbegin(); it != exprs.rend(); ++it){
        Expr *arg = *it;
        code = arg->generateCode(program, cls, fileName);
    }

    return code;
}