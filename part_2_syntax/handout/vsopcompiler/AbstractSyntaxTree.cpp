#include "AbstractSyntaxTree.hpp"
#include <iostream>

Program::Program(){}

std::string Program::eval() const 
{
    auto firstClass = Program::classes.rbegin();
    std::string program = (*firstClass)->eval();

    for(auto it = Program::classes.rbegin() + 1; it != Program::classes.rend(); ++it)
        program += ", " + (*it)->eval();
    
    return "[" + program + "]";
}

Class::Class(const std::string name, const std::string parent, std::vector<Field*>& fields, std::vector<Method*>& methods): name(name), parent(parent), fields(fields), methods(methods){}

std::string Class::eval() const
{
    std::string fields = "";    

    if(Class::fields.size() != 0)
    {
        auto firstField = Class::fields.rbegin();
        fields = (*firstField)->eval();

        for(auto it = Class::fields.rbegin() + 1; it != Class::fields.rend(); ++it)
            fields += ", " + (*it)->eval();
    }

    std::string methods = "";

    if(Class::methods.size() != 0)
    {
        auto firstMethod = Class::methods.rbegin();
        methods = (*firstMethod)->eval();

        for(auto it = Class::methods.rbegin() + 1; it != Class::methods.rend(); ++it)
            methods += ", " + (*it)->eval();
    }
    
    return "Class(" + Class::name + ", " + Class::parent + ", " + "[" + fields + "]" + ", " + "[" + methods + "]" + ")";
}   

ClassBody::ClassBody(){}

Field::Field(const std::string name, const std::string type, Expr *initExpr): name(name), type(type), initExpr(initExpr){}

std::string Field::eval() const
{
    std::string initExpr = "";

    if(Field::initExpr)
        initExpr = ", " + Field::initExpr->eval();

    return "Field(" + Field::name + ", " + Field::type + initExpr + ")";
}

Method::Method(const std::string name, Formals* formals, const std::string retType, Block* block): name(name), formals(formals), retType(retType), block(block){}

std::string Method::eval() const 
{
    std::string formals = "[]";
    std::string block = "[]";

    if(Method::formals)
        formals = Method::formals->eval();
    
    if(Method::block)
        block = Method::block->eval();

    return "Method(" + Method::name + ", " + formals + ", " + Method::retType + ", " + block + ")";
}

Formal::Formal(const std::string name, const std::string type): name(name), type(type){}

std::string Formal::eval() const
{
    return Formal::name + " : " + Formal::type;
}

Formals::Formals(){}

std::string Formals::eval() const
{
    std::string formals = "";

    if(Formals::formals.size() != 0)
    {
        auto firstFormal = Formals::formals.rbegin();
        formals = (*firstFormal)->eval();

        for(auto it = Formals::formals.rbegin() + 1; it != Formals::formals.rend(); ++it)
            formals += ", " + (*it)->eval();
    }

    return "[" + formals + "]";
}

Block::Block(Args *exprList): exprList(exprList){}

std::string Block::eval() const
{
    std::string listExpr = "[]";

    if(Block::exprList)
        listExpr = Block::exprList->eval();
    
    return listExpr;
}

If::If(Expr *condExpr, Expr *thenExpr, Expr *elseExpr): condExpr(condExpr), thenExpr(thenExpr), elseExpr(elseExpr){}

std::string If::eval() const
{
    std::string elseExpr = "";

    if(If::elseExpr)
        elseExpr = ", " + If::elseExpr->eval();

    return "If(" + If::condExpr->eval() + ", " + If::thenExpr->eval() + elseExpr + ")";
}

While::While(Expr *condExpr, Expr *bodyExpr): condExpr(condExpr), bodyExpr(bodyExpr){}

std::string While::eval() const 
{
    return "While(" + While::condExpr->eval() + ", " + While::bodyExpr->eval() + ")";
}

Let::Let(const std::string name, const std::string type, Expr *scopeExpr, Expr *initExpr): name(name), type(type), scopeExpr(scopeExpr), initExpr(initExpr){}

std::string Let::eval() const
{
    std::string initExpr = "";

    if(Let::initExpr)
        initExpr = ", " + Let::initExpr->eval();

    return "Let(" + Let::name + ", " + Let::type + initExpr + ", " + Let::scopeExpr->eval() + ")";
}

Assign::Assign(const std::string name, Expr *expr): name(name), expr(expr){}

std::string Assign::eval() const 
{
    return "Assign(" + Assign::name + ", " + Assign::expr->eval() + ")";
}

UnOp::UnOp(const std::string symbol, Expr *expr): expr(expr), symbol(symbol){}

std::string UnOp::eval() const 
{
    return "UnOp(" + UnOp::symbol + ", " + UnOp::expr->eval() + ")";
}

Not::Not(Expr *expr): UnOp("not", expr){}

UnaryMinus::UnaryMinus(Expr *expr): UnOp("-", expr){}

IsNull::IsNull(Expr *expr): UnOp("isnull", expr){}

BinOp::BinOp(const std::string symbol, Expr *leftExpr, Expr *rightExpr): leftExpr(leftExpr), rightExpr(rightExpr), symbol(symbol){}

std::string BinOp::eval() const 
{
    return "BinOp(" + BinOp::symbol + ", " + BinOp::leftExpr->eval() + ", " + BinOp::rightExpr->eval() + ")";
}

Plus::Plus(Expr *leftExpr, Expr *rightExpr): BinOp("+", leftExpr, rightExpr){}

Minus::Minus(Expr *leftExpr, Expr *rightExpr): BinOp("-", leftExpr, rightExpr){}

Times::Times(Expr *leftExpr, Expr *rightExpr): BinOp("*", leftExpr, rightExpr){}

Div::Div(Expr *leftExpr, Expr *rightExpr): BinOp("/", leftExpr, rightExpr){}

And::And(Expr *leftExpr, Expr *rightExpr): BinOp("and", leftExpr, rightExpr){}

LowerEqual::LowerEqual(Expr *leftExpr, Expr *rightExpr): BinOp("<=", leftExpr, rightExpr){}

Lower::Lower(Expr *leftExpr, Expr *rightExpr): BinOp("<", leftExpr, rightExpr){}

Equal::Equal(Expr *leftExpr, Expr *rightExpr): BinOp("=", leftExpr, rightExpr){}

Pow::Pow(Expr *leftExpr, Expr *rightExpr): BinOp("^", leftExpr, rightExpr){}

Args::Args(){}

std::string Args::eval() const
{
    std::string exprList = "";

    if(Args::exprList.size() != 0)
    {
        auto firstFormal = Args::exprList.rbegin();
        exprList = (*firstFormal)->eval();

        for(auto it = Args::exprList.rbegin() + 1; it != Args::exprList.rend(); ++it)
            exprList += ", " + (*it)->eval();
    }

    return "[" + exprList + "]";
}

Call::Call(Expr *objExpr, const std::string methodName, Args *listExpr): objExpr(objExpr), methodName(methodName), listExpr(listExpr){}

std::string Call::eval() const
{
    std::string objExpr = "self";
   
    std::string listExpr = "[]";

    if(Call::listExpr)
        listExpr = Call::listExpr->eval();

    if(Call::objExpr)
        objExpr = Call::objExpr->eval();

    return "Call(" + objExpr + ", " + Call::methodName + ", " + listExpr + ")";
}

New::New(const std::string typeName): typeName(typeName){}

std::string New::eval() const
{
    return "New(" + New::typeName + ")";
}

IntegerLiteral::IntegerLiteral(const int intValue): intValue(intValue){}

std::string IntegerLiteral::eval() const
{
    return std::to_string(IntegerLiteral::intValue);
}

StringLiteral::StringLiteral(const std::string stringValue): stringValue(stringValue){}

std::string hexConvert(char character)
{
    std::string ret = "\\xhh";
    std::string ref = "0123456789abcdef";

    ret[2] = ref[character / 16];
    ret[3] = ref[character % 16];

    return ret;
}

std::string StringLiteral::eval() const
{
    std::string ret = "\"";

    for(char character: StringLiteral::stringValue){

        if(character != '\"' && character != '\\'){
            if(character >= 32 && character <= 126)
                ret += character;
            else 
                ret += hexConvert(character);
        }
        else
            ret += hexConvert(character);
    }

    return ret + "\"";
}

BooleanLiteral::BooleanLiteral(const bool booleanValue): booleanValue(booleanValue){}

std::string BooleanLiteral::eval() const
{
    std::string boolString = "false";

    if(BooleanLiteral::booleanValue)
        boolString = "true";

    return boolString;
}

ObjectIdentifier::ObjectIdentifier(const std::string identifier): identifier(identifier){}

std::string ObjectIdentifier::eval() const 
{
    return ObjectIdentifier::identifier;
}

Self::Self(){}

std::string Self::eval() const
{
    return "self";
}

Unit::Unit(){}

std::string Unit::eval() const
{
    return "unit";
}
