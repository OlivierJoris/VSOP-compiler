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

using namespace std;

/**
 * @brief Check that the given type is a primitive type (int32, bool, string).
 * 
 * @param toCheck Type to check.
 * @return true If it is a primitive type.
 * @return false If it is not a primitive type.
 */
static bool checkPrimitiveType(const string& toCheck){
    if(toCheck.compare("int32") == 0)
        return true;
    if(toCheck.compare("bool") == 0)
        return true;
    if(toCheck.compare("string") == 0)
        return true;
    return false;
}

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

const string Assign::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    if(expr){
        // Type checking on expr (right-hand side of assign)
        const string err = expr->typeChecking(prog, currentClass, scope);
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
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + name + " is not in scope.";
            return err;
        }
        
        // Check that type of expr matches type of id (name)
        if(obj->type.compare(expr->type)){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) +
                ":<expr> does not have the same type as " + name +
                ". " + name + " has type " + obj->type + " while <expr> has type " + expr->type + ".";
            return err;
        }

        // Type of assign is type of expr
        type = expr->type;
    }

    return "";
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

Not::Not(Expr *expr, const int line, const int column): UnOp("not", expr, line, column){}

const string Not::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

const string Not::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Right-hand side must be bool
    if(expr->type.compare("bool")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "operand must be of type bool" +
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

const string UnaryMinus::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Right-hand side must be int32
    if(expr->type.compare("int32")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "operand must be of type int32" +
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

const std::string IsNull::typeChecking(const Program* prog, string currentClass, std::vector<std::pair<std::string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // isnull is only applicable to type defined by classes
    if(checkPrimitiveType(expr->type)){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":isnull not applicable on primitive types.";
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

const string ArithmeticBinOp::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    if(leftExpr){
        // Perform type checking in left-hand side operand
        const string err = leftExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(leftExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "left-hand side of operator must be int32 (is " + leftExpr->type + ").";
            return err;
        }
    }

    if(rightExpr){
        // Perform type checking on the right-hand side operand
        const string err = rightExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(rightExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
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

const string Plus::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, scope);
}

Minus::Minus(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("-", leftExpr, rightExpr, line, column){}

const string Minus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Minus::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, scope);
}

Times::Times(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("*", leftExpr, rightExpr, line, column){}

const string Times::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Times::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, scope);
}

Div::Div(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("/", leftExpr, rightExpr, line, column){}

const string Div::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Div::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, scope);
}

Pow::Pow(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("^", leftExpr, rightExpr, line, column){}

const string Pow::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Pow::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, currentClass, scope);
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

const string BinaryComparison::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    if(leftExpr){
        // Perform type checking in left-hand side operand
        const string err = leftExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(leftExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "left-hand side of operator must be int32 (is " + leftExpr->type + ").";
            return err;
        }
    }

    if(rightExpr){
        // Perform type checking on the right-hand side operand
        const string err = rightExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;

        // Check that type is int32
        if(rightExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
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

const string LowerEqual::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    return BinaryComparison::typeChecking(prog, currentClass, scope);
}

Lower::Lower(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinaryComparison("<", leftExpr, rightExpr, line, column){}

const string Lower::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinaryComparison::checkUsageUndefinedType(classesMap);
}

const string Lower::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    return BinaryComparison::typeChecking(prog, currentClass, scope);
}

Equal::Equal(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp("=", leftExpr, rightExpr, line, column){}

const string Equal::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string Equal::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Perform type checking on left-hand side operand
    if(leftExpr){
        const string err = leftExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Perform type checking on the right-hand side operand
    if(rightExpr){
        const string err = rightExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Check if both operands are primitive types.
    if(leftExpr && rightExpr && checkPrimitiveType(leftExpr->type) && checkPrimitiveType(rightExpr->type)){
        // Must be same primitive type or error
        if(leftExpr->type.compare(rightExpr->type)){
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) +
                "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
                rightExpr->type + ".";
            return err;
        }
    }else if(leftExpr && rightExpr && checkPrimitiveType(leftExpr->type) && !checkPrimitiveType(rightExpr->type)){
        // LHS primitive & RHS not primitive
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) +
            "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
            rightExpr->type + ".";
        return err;
    } else if(leftExpr && rightExpr && !checkPrimitiveType(leftExpr->type) && checkPrimitiveType(rightExpr->type)){
        // LHS not primitive & RHS primitive
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) +
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

const string And::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Perform type checking on the left-hand side
    if(leftExpr){
        const string err = leftExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Perform type checking on right-hand side
    if(rightExpr){
        const string err = rightExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Both LHS and RHS must be bool
    if(leftExpr->type.compare("bool")){
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "left-hand side must be bool (is " +
            leftExpr->type + ").";
        return err;
    }
    if(rightExpr->type.compare("bool")){
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "right-hand side must be bool (is " +
            rightExpr->type + ").";
        return err;
    }

    // Set type as bool (per manual)
    type = "bool";

    return "";
}
