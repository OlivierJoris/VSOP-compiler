/**
 * Implementation of the operator types for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "Operators.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "TypeChecking.hpp"

using namespace std;

/*********************
        ASSIGN
*********************/

Assign::Assign(const string name, Expr *expr, const int line, const int column): name(name), expr(expr){
    this->line = line;
    this->column = column;
}

string Assign::dumpAST(bool annotated) const 
{
    if(annotated)
        return "Assign(" + Assign::name + ", " + Assign::expr->dumpAST(annotated) + ") : " + type;
    else
        return "Assign(" + Assign::name + ", " + Assign::expr->dumpAST(annotated) + ")";
}

const string Assign::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check expression if any
    if(expr){
        const string check = expr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string Assign::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    if(expr){
        // Type checking on expr (right-hand side of assign)
        const string err = expr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Check that name is in scope
        Expr *obj = NULL;
        for(auto it = scope.crbegin(); it != scope.crend(); it++){
            if((*it).first.compare(name) == 0){
                obj = (*it).second;
                break;
            }
        }

        if(!obj){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: " + name + " is not in scope.";
            return err;
        }

        vector<string> ancestors = vector<string>();
        auto classes = prog->getClasses();

        string tmpExpr = expr->type;
        ancestors.push_back(tmpExpr);
        while(tmpExpr.compare("Object")){
            auto tmpClass = prog->classesMap.find(tmpExpr);
            if(tmpClass != prog->classesMap.end()){
                Class *cls = (*tmpClass).second;
                if(cls){
                    tmpExpr = cls->getParent();
                    ancestors.push_back(tmpExpr);
                }else
                    break;
            }else
                break;
        }
        
        // Check that type of expr matches type of id (name)
        if(std::find(ancestors.begin(), ancestors.end(), obj->type) == ancestors.end()){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) +
                ": semantic error: <expr> does not have the same type as " + name +
                " or one of its ancestors.";
            return err;
        }

        // Type of assign is type of expr
        type = obj->type;
    }

    return "";
}

llvm::Value *Assign::generateCode(Program *program, Class* cls, const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);

    auto assignCode = expr->generateCode(program, cls, fileName);
    assignCode = llvm->builder->CreatePointerCast(assignCode, llvm->getType(type));
    if(program->variables[name] == NULL){
        auto function = llvm->builder->GetInsertBlock()->getParent();
        auto clas = function->arg_begin();   
        auto address = llvm->builder->CreateStructGEP(llvm->mdl->getTypeByName(cls->getName()), clas, program->fieldsMap[cls->getName()][name]);
        llvm->builder->CreateStore(assignCode, address);
    }
    else{
        llvm->builder->CreateStore(assignCode, program->variables[name]);
    }

    return assignCode;
}   

/*********************
        UN OP
*********************/

UnOp::UnOp(const string symbol, Expr *expr, const int line, const int column): expr(expr), symbol(symbol){
    this->line = line;
    this->column = column;
}

string UnOp::dumpAST(bool annotated) const 
{
    if(annotated)
        return "UnOp(" + UnOp::symbol + ", " + UnOp::expr->dumpAST(annotated) + ") : " + type;
    else
        return "UnOp(" + UnOp::symbol + ", " + UnOp::expr->dumpAST(annotated) + ")";
}

const string UnOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check expr if any
    if(expr){
        const string check = expr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

llvm::Value *UnOp::generateCode(Program *Program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(Program, fileName);

    auto exprCode = expr->generateCode(Program, cls, fileName);
    llvm::Value *ret;
    
    if (symbol == "-")
        ret = llvm->builder->CreateNeg(exprCode);
    else if (symbol == "isnull")
        ret = llvm->builder->CreateIsNull(exprCode);
    else if (symbol == "not")
        ret = llvm->builder->CreateNot(exprCode);
    else
        ret = NULL;

    return ret;
}

Not::Not(Expr *expr, const int line, const int column): UnOp("not", expr, line, column){}

const string Not::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

const string Not::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Right-hand side must be bool
    if(expr->type.compare("bool")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: operand must be of type bool" +
            " (is " + expr->type + ").";
        return err;
    }

    // Set type as bool
    type = "bool";

    return "";
}

UnaryMinus::UnaryMinus(Expr *expr, const int line, const int column): UnOp("-", expr, line, column){}

const string UnaryMinus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

const string UnaryMinus::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Right-hand side must be int32
    if(expr->type.compare("int32")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: operand must be of type int32" +
            " (is " + expr->type + ").";
        return err;
    }

    // Set type as int32
    type = "int32";

    return "";
}

IsNull::IsNull(Expr *expr, const int line, const int column): UnOp("isnull", expr, line, column){}

const string IsNull::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

const string IsNull::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // isnull is only applicable to type defined by classes
    if(checkPrimitiveType(expr->type)){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: isnull not applicable on primitive types.";
        return err;
    }

    // Set type as bool
    type = "bool";

    return "";
}

/*********************
        BIN OP
*********************/

BinOp::BinOp(const string symbol, Expr *leftExpr, Expr *rightExpr, const int line, const int column): leftExpr(leftExpr), rightExpr(rightExpr), symbol(symbol){
    this->line = line;
    this->column = column;
}

string BinOp::dumpAST(bool annotated) const 
{
    if(annotated)
        return "BinOp(" + BinOp::symbol + ", " + BinOp::leftExpr->dumpAST(annotated) + ", " + BinOp::rightExpr->dumpAST(annotated) + ") : " + type;
    else
        return "BinOp(" + BinOp::symbol + ", " + BinOp::leftExpr->dumpAST(annotated) + ", " + BinOp::rightExpr->dumpAST(annotated) + ")";
}

const string BinOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check left-hand side expression if any
    if(leftExpr){
        const string check = leftExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check right-hand side expression if any
    if(rightExpr){
        const string check = rightExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

llvm::Value *BinOp::generateCode(Program *program, Class* cls, const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);

    auto leftExprCode = leftExpr->generateCode(program, cls, fileName);
    llvm::Value *ret;
    if (symbol == "and"){
        llvm::BasicBlock *trueLeft = llvm::BasicBlock::Create(*(llvm->context), "and_true");
        llvm::BasicBlock *falseLeft = llvm::BasicBlock::Create(*(llvm->context), "and_false");
        llvm::BasicBlock *end = llvm::BasicBlock::Create(*(llvm->context), "and_end");

        llvm->builder->CreateCondBr(leftExprCode, trueLeft, falseLeft);
        llvm->builder->GetInsertBlock()->getParent()->getBasicBlockList().push_back(trueLeft);
        llvm->builder->SetInsertPoint(trueLeft);
        auto trueLeftCode = rightExpr->generateCode(program, cls, fileName);
        llvm->builder->CreateBr(end);
        trueLeft = llvm->builder->GetInsertBlock();

        llvm->builder->GetInsertBlock()->getParent()->getBasicBlockList().push_back(falseLeft);
        llvm->builder->SetInsertPoint(falseLeft);
        auto falseLeftCode = llvm->builder->getFalse();
        llvm->builder->CreateBr(end);
        falseLeft = llvm->builder->GetInsertBlock();
        llvm->builder->GetInsertBlock()->getParent()->getBasicBlockList().push_back(end);
        llvm->builder->SetInsertPoint(end);

        auto phi = llvm->builder->CreatePHI(llvm::Type::getInt1Ty(*(llvm->context)), 0);
        phi->addIncoming(trueLeftCode, trueLeft);
        phi->addIncoming(falseLeftCode, falseLeft);

        ret = phi;
    }
    else {
        auto rightExprCode = rightExpr->generateCode(program, cls, fileName);

        if (symbol == "+")
            ret = llvm->builder->CreateAdd(leftExprCode, rightExprCode);
        else if (symbol == "-")
            ret = llvm->builder->CreateSub(leftExprCode, rightExprCode);
        else if (symbol == "*")
            ret = llvm->builder->CreateMul(leftExprCode, rightExprCode);
        else if (symbol == "/")
            ret = llvm->builder->CreateUDiv(leftExprCode, rightExprCode);
        else if (symbol == "^"){
            llvm::Value *call = llvm->builder->CreateCall(llvm->mdl->getFunction("power"), {leftExprCode, rightExprCode});
            ret = llvm->builder->CreateIntCast(call, llvm::Type::getInt32Ty(*(llvm->context)), true);
        }
        else if (symbol == "="){
            if(leftExpr->type == "unit" && rightExpr->type == "unit")
                return llvm::ConstantInt::get(llvm->getType("bool"), 1);
            if(leftExpr->type != "bool" && leftExpr->type != "int32" && leftExpr->type != "unit" && leftExpr->type != "string" && rightExpr->type != "bool" && rightExpr->type != "int32" && rightExpr->type != "unit" && rightExpr->type != "string"){
                leftExprCode = llvm->builder->CreatePointerCast(leftExprCode, llvm::IntegerType::getInt64Ty(*(llvm->context)));
                rightExprCode = llvm->builder->CreatePointerCast(rightExprCode, llvm::IntegerType::getInt64Ty(*(llvm->context)));
            }

            ret = llvm->builder->CreateICmpEQ(leftExprCode, rightExprCode);
        }
        else if (symbol == "<")
            ret = llvm->builder->CreateICmpSLT(leftExprCode, rightExprCode);
        else if (symbol == "<=")
            ret = llvm->builder->CreateICmpSLE(leftExprCode, rightExprCode);
        else
            ret = NULL;
    }

    return ret;
}

/*********************
  ARITHMETIC BIN OP
*********************/

ArithmeticBinOp::ArithmeticBinOp(const string symbol, Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp(symbol, leftExpr, rightExpr, line, column){}

string ArithmeticBinOp::dumpAST(bool annotated) const{
    return BinOp::dumpAST(annotated);
}

const string ArithmeticBinOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string ArithmeticBinOp::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    if(leftExpr){
        // Perform type checking in left-hand side operand
        const string err = leftExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(leftExpr->type.compare("int32")){
            string err = to_string(getLine()) + ": semantic error: " + to_string(getColumn()) + ":" +
                "left-hand side of operator must be int32 (is " + leftExpr->type + ").";
            return err;
        }
    }

    if(rightExpr){
        // Perform type checking on the right-hand side operand
        const string err = rightExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(rightExpr->type.compare("int32")){
            string err = to_string(getLine()) + ": semantic error: " + to_string(getColumn()) + ":" +
                "right-hand side of operator must be int32 (is " + rightExpr->type + ").";
            return err;
        }
    }

    // Set type as int32 (per manual)
    type = "int32";

    return "";
}

Plus::Plus(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("+", leftExpr, rightExpr, line, column){}

const string Plus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Plus::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, inFieldInit, scope);
}

Minus::Minus(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("-", leftExpr, rightExpr, line, column){}

const string Minus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Minus::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, inFieldInit, scope);
}

Times::Times(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("*", leftExpr, rightExpr, line, column){}

const string Times::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Times::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, inFieldInit, scope);
}

Div::Div(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("/", leftExpr, rightExpr, line, column){}

const string Div::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Div::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, inFieldInit, scope);
}

Pow::Pow(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("^", leftExpr, rightExpr, line, column){}

const string Pow::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Pow::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, inFieldInit, scope);
}

/*********************
  BINARY COMPARISON
*********************/

BinaryComparison::BinaryComparison(const string symbol, Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp(symbol, leftExpr, rightExpr, line, column){}

string BinaryComparison::dumpAST(bool annotated) const{
    return BinOp::dumpAST(annotated);
}

const string BinaryComparison::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string BinaryComparison::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    if(leftExpr){
        // Perform type checking in left-hand side operand
        const string err = leftExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(leftExpr->type.compare("int32")){
            string err = to_string(getLine()) + ": semantic error: " + to_string(getColumn()) + ":" +
                "left-hand side of operator must be int32 (is " + leftExpr->type + ").";
            return err;
        }
    }

    if(rightExpr){
        // Perform type checking on the right-hand side operand
        const string err = rightExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(rightExpr->type.compare("int32")){
            string err = to_string(getLine()) + ": semantic error: " + to_string(getColumn()) + ":" +
                "right-hand side of operator must be int32 (is " + rightExpr->type + ").";
            return err;
        }
    }

    // Set type as bool (per manual)
    type = "bool";

    return "";
}

LowerEqual::LowerEqual(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinaryComparison("<=", leftExpr, rightExpr, line, column){}

const string LowerEqual::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinaryComparison::checkUsageUndefinedType(classesMap);
}

const string LowerEqual::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    return BinaryComparison::typeChecking(prog, currentClass, inFieldInit, scope);
}

Lower::Lower(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinaryComparison("<", leftExpr, rightExpr, line, column){}

const string Lower::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinaryComparison::checkUsageUndefinedType(classesMap);
}

const string Lower::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    return BinaryComparison::typeChecking(prog, currentClass, inFieldInit, scope);
}

Equal::Equal(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp("=", leftExpr, rightExpr, line, column){}

const string Equal::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string Equal::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // Perform type checking on left-hand side operand
    if(leftExpr){
        const string err = leftExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Perform type checking on the right-hand side operand
    if(rightExpr){
        const string err = rightExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Check if both operands are primitive types.
    if(leftExpr && rightExpr && checkPrimitiveType(leftExpr->type) && checkPrimitiveType(rightExpr->type)){
        // Must be same primitive type or error
        if(leftExpr->type.compare(rightExpr->type)){
            const string err = to_string(getLine()) + ": semantic error: " + to_string(getColumn()) +
                "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
                rightExpr->type + ".";
            return err;
        }
    }else if(leftExpr && rightExpr && checkPrimitiveType(leftExpr->type) && !checkPrimitiveType(rightExpr->type)){
        // LHS primitive & RHS not primitive
        const string err = to_string(getLine()) + ": semantic error: " + to_string(getColumn()) +
            "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
            rightExpr->type + ".";
        return err;
    } else if(leftExpr && rightExpr && !checkPrimitiveType(leftExpr->type) && checkPrimitiveType(rightExpr->type)){
        // LHS not primitive & RHS primitive
        const string err = to_string(getLine()) + ": semantic error: " + to_string(getColumn()) +
            "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
            rightExpr->type + ".";
        return err;
    }

    // Set type as bool (per manual)
    type = "bool";

    return "";
}

And::And(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp("and", leftExpr, rightExpr, line, column){}

const string And::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string And::typeChecking(const Program* prog, string currentClass, bool inFieldInit, vector<pair<string, Expr*>> scope){
    // Perform type checking on the left-hand side
    if(leftExpr){
        const string err = leftExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Perform type checking on right-hand side
    if(rightExpr){
        const string err = rightExpr->typeChecking(prog, currentClass, inFieldInit, scope);
        if(err.compare(""))
            return err;
    }

    // Both LHS and RHS must be bool
    if(leftExpr->type.compare("bool")){
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: left-hand side must be bool (is " +
            leftExpr->type + ").";
        return err;
    }
    if(rightExpr->type.compare("bool")){
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: right-hand side must be bool (is " +
            rightExpr->type + ").";
        return err;
    }

    // Set type as bool (per manual)
    type = "bool";

    return "";
}
