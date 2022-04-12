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

string Assign::eval() const 
{
    return "Assign(" + Assign::name + ", " + Assign::expr->eval() + ")";
}

const Expr* Assign::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check expression if any
    if(expr){
        const Expr* check = expr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

const string Assign::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    if(expr){
        // Type checking on expr (right-hand side of assign)
        const string err = expr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Type checking error in expr of assign" << endl;
            return err;
        }

        // TODO check that name is in scope
        
        // TODO check that type of expr matches type of id

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

string UnOp::eval() const 
{
    return "UnOp(" + UnOp::symbol + ", " + UnOp::expr->eval() + ")";
}

const Expr* UnOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check expr if any
    if(expr){
        const Expr* check = expr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

Not::Not(Expr *expr, const int line, const int column): UnOp("not", expr, line, column){}

const Expr* Not::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

const string Not::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Err rhs not" << endl;
            return err;
        }
    }

    // Right-hand side must be bool
    if(expr->type.compare("bool")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "operand must be of type bool" +
            " (is " + expr->type + ").";
        cout << "Err rhs wrong type" << endl;
        return err;
    }

    // Set type as bool
    type = "bool";

    return "";
}

UnaryMinus::UnaryMinus(Expr *expr, const int line, const int column): UnOp("-", expr, line, column){}

const Expr* UnaryMinus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

const string UnaryMinus::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Err rhs unary minus" << endl;
            return err;
        }
    }

    // Right-hand side must be int32
    if(expr->type.compare("int32")){
        string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "operand must be of type int32" +
            " (is " + expr->type + ").";
        cout << "Err rhs wrong type" << endl;
        return err;
    }

    // Set type as int32
    type = "int32";

    return "";
}

IsNull::IsNull(Expr *expr, const int line, const int column): UnOp("isnull", expr, line, column){}

const Expr* IsNull::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return UnOp::checkUsageUndefinedType(classesMap);
}

const std::string IsNull::typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope){
    // Perform type checking on right-hand side
    if(expr){
        const string err = expr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Err rhs unary minus" << endl;
            return err;
        }
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

string BinOp::eval() const 
{
    return "BinOp(" + BinOp::symbol + ", " + BinOp::leftExpr->eval() + ", " + BinOp::rightExpr->eval() + ")";
}

const Expr* BinOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    // Check left-hand side expression if any
    if(leftExpr){
        const Expr* check = leftExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    // Check right-hand side expression if any
    if(rightExpr){
        const Expr* check = rightExpr->checkUsageUndefinedType(classesMap);
        if(check)
            return check;
    }

    return NULL;
}

/*********************
  ARITHMETIC BIN OP
*********************/

ArithmeticBinOp::ArithmeticBinOp(const string symbol, Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp(symbol, leftExpr, rightExpr, line, column){}

string ArithmeticBinOp::eval() const{
    return BinOp::eval();
}

const Expr* ArithmeticBinOp::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string ArithmeticBinOp::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    if(leftExpr){
        // Perform type checking in left-hand side operand
        const string err = leftExpr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Error in LHS" << endl;
            return err;
        }

        // Check that type is int32
        if(leftExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "left-hand side of operator must be int32 (is " + leftExpr->type + ").";
            cout << "Wrong type lhs" << endl;
            return err;
        }
    }

    if(rightExpr){
        // Perform type checking on the right-hand side operand
        const string err = rightExpr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Error in rhs" << endl;
            return err;
        }

        // Check that type is int32
        if(rightExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "right-hand side of operator must be int32 (is " + rightExpr->type + ").";
            cout << "Wrong type rhs" << endl;
            return err;
        }
    }

    // Set type as int32 (per manual)
    type = "int32";

    return "";
}

Plus::Plus(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("+", leftExpr, rightExpr, line, column){}

const Expr* Plus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Plus::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, scope);
}

Minus::Minus(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("-", leftExpr, rightExpr, line, column){}

const Expr* Minus::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Minus::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, scope);
}

Times::Times(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("*", leftExpr, rightExpr, line, column){}

const Expr* Times::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Times::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, scope);
}

Div::Div(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("/", leftExpr, rightExpr, line, column){}

const Expr* Div::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Div::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, scope);
}

Pow::Pow(Expr *leftExpr, Expr *rightExpr, const int line, const int column): ArithmeticBinOp("^", leftExpr, rightExpr, line, column){}

const Expr* Pow::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return ArithmeticBinOp::checkUsageUndefinedType(classesMap);
}

const string Pow::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    return ArithmeticBinOp::typeChecking(prog, scope);
}

/*********************
  BINARY COMPARISON
*********************/

BinaryComparison::BinaryComparison(const string symbol, Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp(symbol, leftExpr, rightExpr, line, column){}

string BinaryComparison::eval() const{
    return BinOp::eval();
}

const Expr* BinaryComparison::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string BinaryComparison::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    if(leftExpr){
        // Perform type checking in left-hand side operand
        const string err = leftExpr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Error in LHS" << endl;
            return err;
        }

        // Check that type is int32
        if(leftExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "left-hand side of operator must be int32 (is " + leftExpr->type + ").";
            cout << "Wrong type lhs" << endl;
            return err;
        }
    }

    if(rightExpr){
        // Perform type checking on the right-hand side operand
        const string err = rightExpr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Error in rhs" << endl;
            return err;
        }

        // Check that type is int32
        if(rightExpr->type.compare("int32")){
            string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" +
                "right-hand side of operator must be int32 (is " + rightExpr->type + ").";
            cout << "Wrong type rhs" << endl;
            return err;
        }
    }

    // Set type as bool (per manual)
    type = "bool";

    return "";
}

LowerEqual::LowerEqual(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinaryComparison("<=", leftExpr, rightExpr, line, column){}

const Expr* LowerEqual::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinaryComparison::checkUsageUndefinedType(classesMap);
}

const string LowerEqual::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    return BinaryComparison::typeChecking(prog, scope);
}

Lower::Lower(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinaryComparison("<", leftExpr, rightExpr, line, column){}

const Expr* Lower::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinaryComparison::checkUsageUndefinedType(classesMap);
}

const string Lower::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    return BinaryComparison::typeChecking(prog, scope);
}

Equal::Equal(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp("=", leftExpr, rightExpr, line, column){}

const Expr* Equal::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string Equal::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    // Perform type checking on left-hand side operand
    if(leftExpr){
        const string err = leftExpr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Error lhs" << endl;
            return err;
        }
    }

    // Perform type checking on the right-hand side operand
    if(rightExpr){
        const string err = rightExpr->typeChecking(prog, scope);
        if(err.compare("")){
            cout << "Error rhs" << endl;
            return err;
        }
    }

    // Check if both operands are primitive types.
    if(leftExpr && rightExpr && checkPrimitiveType(leftExpr->type) && checkPrimitiveType(rightExpr->type)){
        // Must be same primitive type or error
        if(leftExpr->type.compare(rightExpr->type)){
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) +
                "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
                rightExpr->type + ".";
            cout << "Comparison err not same type" << endl;
            return err;
        }
    }else if(leftExpr && rightExpr && checkPrimitiveType(leftExpr->type) && !checkPrimitiveType(rightExpr->type)){
        // LHS primitive & RHS not primitive
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) +
            "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
            rightExpr->type + ".";
        cout << "Comparison err not same type" << endl;
        return err;
    } else if(leftExpr && rightExpr && !checkPrimitiveType(leftExpr->type) && checkPrimitiveType(rightExpr->type)){
        // LHS not primitive & RHS primitive
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) +
            "both operands do not have the same type. Left-hand side is " + leftExpr->type + " while right-hand side is " +
            rightExpr->type + ".";
        cout << "Comparison err not same type" << endl;
        return err;
    }

    // Set type as bool (per manual)
    type = "bool";

    return "";
}

And::And(Expr *leftExpr, Expr *rightExpr, const int line, const int column): BinOp("and", leftExpr, rightExpr, line, column){}

const Expr* And::checkUsageUndefinedType(const map<string, Class*>& classesMap) const{
    return BinOp::checkUsageUndefinedType(classesMap);
}

const string And::typeChecking(const Program* prog, vector<pair<string, Expr*>> scope){
    // Perform type checking on the left-hand side
    if(leftExpr){
        const string err = leftExpr->typeChecking(prog, scope);
        cout << "Error lhs" << endl;
        return err;
    }

    // Perform type checking on right-hand side
    if(rightExpr){
        const string err = rightExpr->typeChecking(prog, scope);
        cout << "Error rhs" << endl;
        return err;
    }

    // Both LHS and RHS must be bool
    if(leftExpr->type.compare("bool")){
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "left-hand side must be bool (is " +
            leftExpr->type + ").";
        cout << "Wrong type lhs" << endl;
        return err;
    }
    if(rightExpr->type.compare("bool")){
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ":" + "right-hand side must be bool (is " +
            rightExpr->type + ").";
        cout << "Wrong type rhs" << endl;
        return err;
    }

    // Set type as bool (per manual)
    type = "bool";

    return "";
}
