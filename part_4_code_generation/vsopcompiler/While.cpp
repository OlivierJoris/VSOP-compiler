/**
 * Implementation of the while type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <map>
#include <string>

#include "While.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "LLVM.hpp"

using namespace std;

While::While(Expr *condExpr, Expr *bodyExpr, const int line, const int column): condExpr(condExpr), bodyExpr(bodyExpr){
    this->line = line;
    this->column = column;
}

string While::dumpAST(bool annotated) const
{
    if(annotated)
        return "While(" + While::condExpr->dumpAST(annotated) + ", " + While::bodyExpr->dumpAST(annotated) + ") : " + type;
    else
        return "While(" + While::condExpr->dumpAST(annotated) + ", " + While::bodyExpr->dumpAST(annotated) + ")";
}

const string While::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check condition expression if any
    if(condExpr){
        const string check = condExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check body expression if any
    if(bodyExpr){
        const string check = bodyExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string While::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // Type checking on condition
    if(condExpr){
        const string err = condExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Type checking on body
    if(bodyExpr){
        const string err = bodyExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Type of condition must be bool
    if(condExpr && condExpr->type.compare("bool")){
        const string err = to_string(condExpr->getLine()) + ": semantic error: " + to_string(condExpr->getColumn())
            + ":" + "condition must have type bool (is type " + condExpr->type + ").";
        return err;
    }

    // No restriction on type of body -> no check

    // Set type of while as unit (from manual of VSOP)
    type = "unit";

    return "";
}

llvm::Value *While::generateCode(Program *program, Class* cls, const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);

    auto block = llvm->builder->GetInsertBlock()->getParent();
    auto condBlock = llvm::BasicBlock::Create(*(llvm->context), "while_cond", block);
    auto bodyBlock = llvm::BasicBlock::Create(*(llvm->context), "while_body", block);
    auto endBlock = llvm::BasicBlock::Create(*(llvm->context), "while_end", block);

    llvm->builder->CreateBr(condBlock);
    llvm->builder->SetInsertPoint(condBlock);
    auto cond = condExpr->generateCode(program, cls, fileName);
    llvm->builder->CreateCondBr(cond, bodyBlock, endBlock);

    llvm->builder->SetInsertPoint(bodyBlock);
    bodyExpr->generateCode(program, cls, fileName);
    llvm->builder->CreateBr(condBlock);

    llvm->builder->SetInsertPoint(endBlock);
    return NULL;
}