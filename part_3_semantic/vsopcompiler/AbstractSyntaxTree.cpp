/**
 * Implementation of the AST for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "AbstractSyntaxTree.hpp"
#include "TypeChecking.hpp"

using namespace std;

Program::Program()
{
    Program::classesMap.insert(pair<string, Class *>("Object", NULL));
}

void Program::checkRedefinition()
{
    for(Class *cls: classes)
    {
        std::string className = cls->getName();
        if(classesMap.find(className) != classesMap.end())
            errors.push_back("redefinition of class " + className);
        else 
            classesMap[className] = cls;

        for(Field *field: cls->getFields())
        {
            std::string fieldName = field->getName();
            if(cls->fieldsMap.find(fieldName) != cls->fieldsMap.end())
                errors.push_back("redefinition of field " + fieldName);
            else
                cls->fieldsMap[fieldName] = field;
        }

        for(Method *method: cls->getMethods())
        {
            std::string methodName = method->getName();
            if(cls->methodsMap.find(methodName) != cls->methodsMap.end())
                errors.push_back("redefinition of method " + methodName);
            else
                cls->methodsMap[methodName] = method;
            

            for(Formal *formal: method->getFormals())
            {
                std::string formalName = formal->getName();
                if(method->formalsMap.find(formalName) != method->formalsMap.end())
                    errors.push_back("redefinition of the formal " + formalName);
                else 
                    method->formalsMap[formalName] = formal;
            }
        }
    }
}

void Program::checkInheritance()
{
    std::set<std::string> parentSet;

    for(Class *cls: classes)
    {
        std::string parent = cls->getParent();
        while(parent != "Object")
        {
            /* Cycle in inheritance */
            if(parentSet.find(parent) != parentSet.end())
            {
                errors.push_back("class " + cls->getName() + " cannot extends parent class " + parent);
                break;
            }
            else
            {
                /* Parent class has not been defined */
                if(classesMap.find(parent) == classesMap.end())
                {
                    errors.push_back("class " + parent + " is not defined");
                    break; 
                }

                parentSet.insert(parent);
                parent = classesMap[parent]->getParent();
            }
        }

        if(parentSet.size() > 0)
            parentSet.clear(); 
    }
}

void Program::checkOverrides()
{
    for(Class *cls: classes)
    {
        /* Field */
        for(Field *field: cls->getFields())
        {
            std::string parent = cls->getParent();
            while(parent != "Object")
            {
                /* Parent class has not been defined */
                if(classesMap.find(parent) == classesMap.end())
                    break; 
            
                if(classesMap[parent]->fieldsMap.find(field->getName()) != classesMap[parent]->fieldsMap.end())
                    errors.push_back("field " + field->getName() + " of class " + cls->getName() + " is overriden");
                
                parent = classesMap[parent]->getParent();
            }
        }

        for(Method *method: cls->getMethods())
        {
            std::string parent = cls->getParent();
            while(parent != "Object")
            {
                /* Parent class has not been defined */
                if(classesMap.find(parent) == classesMap.end())
                    break; 

                if(classesMap[parent]->methodsMap.find(method->getName()) != classesMap[parent]->methodsMap.end())
                {
                    Method *m =  classesMap[parent]->methodsMap[method->getName()];
                    if(m->getRetType() != method->getRetType())
                        errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with type " + method->getRetType() + " but parent type was " + m->getRetType());
                    
                    if(m->getFormals().size() != method->getFormals().size())
                    {
                        errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with " + std::to_string(method->getFormals().size()) + " formals but parent class has " + std::to_string(m->getFormals().size()) + " formals");
                        break;
                    }

                    unsigned int i = 0;
                    for(Formal *formal: method->getFormals())
                    {
                        if(m->getFormals(i)->getName() != formal->getName())
                            errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with " + formal->getName() + " as formal name in place " + std::to_string(i) + " but parent class has " + m->getFormals(i)->getName() + " as formal name in this position");
                        
                        if(m->getFormals(i)->getType() != formal->getType())
                            errors.push_back("method " + method->getName() + " of class " + cls->getName() + " overriden with " + formal->getType() + " as formal type in place " + std::to_string(i) + " but parent class has " + m->getFormals(i)->getType() + " as formal type in this position");
                    }
                }

                parent = classesMap[parent]->getParent();
            }
        }
    }
}

std::string Program::eval() const 
{
    auto firstClass = Program::classes.rbegin();
    string program = (*firstClass)->eval();

    for(auto it = Program::classes.rbegin() + 1; it != Program::classes.rend(); ++it)
        program += ", " + (*it)->eval();
    
    return "[" + program + "]";
}

const Expr* Program::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    for(Class *cls: classes){
        const Expr* check = cls->checkUsageUndefinedType(classesMap);
        if(check == NULL) {
            cout << "No usage of not defined type inside class " << cls->getName() << endl;
        } else {
            cout << "Usage of not defined type inside class " << cls->getName() << endl;
            return check;
        }

    }
    return NULL;
}

Class::Class(const string name, const string parent, vector<Field*>& fields, vector<Method*>& methods): name(name), parent(parent), fields(fields), methods(methods){}

string Class::eval() const
{
    string fields = "";    

    if(Class::fields.size() != 0)
    {
        auto firstField = Class::fields.rbegin();
        fields = (*firstField)->eval();

        for(auto it = Class::fields.rbegin() + 1; it != Class::fields.rend(); ++it)
            fields += ", " + (*it)->eval();
    }

    string methods = "";

    if(Class::methods.size() != 0)
    {
        auto firstMethod = Class::methods.rbegin();
        methods = (*firstMethod)->eval();

        for(auto it = Class::methods.rbegin() + 1; it != Class::methods.rend(); ++it)
            methods += ", " + (*it)->eval();
    }
    
    return "Class(" + Class::name + ", " + Class::parent + ", " + "[" + fields + "]" + ", " + "[" + methods + "]" + ")";
}

const Expr* Class::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    // Check fields
    for(Field *field: fields){
        const Expr* check = field->checkUsageUndefinedType(classesMap);
        if(check == NULL) {
            cout << "No usage of not defined type for field " << field->getName() << endl;
        } else {
            cout << "Usage of not defined type for field " << field->getName() << endl;
            return check;
        }
    }

    // Check methods
    for(Method *method: methods){
        const Expr* check = method->checkUsageUndefinedType(classesMap);
        if (check == NULL) {
            cout << "No usage of not defined type for method " << method->getName() << endl;
        } else {
            cout << "Usage of not defined type for method " << method->getName() << endl;
            return check;
        }
    }

    return NULL;
}

ClassBody::ClassBody(){}

Field::Field(const string name, const string type, Expr *initExpr): name(name), type(type), initExpr(initExpr){}

string Field::eval() const
{
    string initExpr = "";

    if(Field::initExpr)
        initExpr = ", " + Field::initExpr->eval();

    return "Field(" + Field::name + ", " + Field::type + initExpr + ")";
}

const Expr* Field::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    bool knwon = checkKnownType(classesMap, type);
    if(knwon)
        return NULL;
    else
        return this;
}

Method::Method(const string name, Formals* formals, const string retType, Block* block): name(name), formals(formals), retType(retType), block(block){}

string Method::eval() const 
{
    string formals = "[]";
    string block = "[]";

    if(Method::formals)
        formals = Method::formals->eval();
    
    if(Method::block)
        block = Method::block->eval();

    return "Method(" + Method::name + ", " + formals + ", " + Method::retType + ", " + block + ")";
}

const Expr* Method::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    // Check return type
    bool known = checkKnownType(classesMap, retType);
    if(known){
        cout << "Return type of " << name << " known" << endl;
    }else{
        cout << "Return type of " << name << " unknown" << endl;
        return this;
    }

    // Check formals if any
    if(formals != NULL){
        cout << "Checking formals" << endl;
        formals->checkUsageUndefinedType(classesMap);
    }else{
        cout << "No formals to check" << endl;
    }

    return NULL;
}

Formal::Formal(const string name, const string type): name(name), type(type){}

string Formal::eval() const
{
    return Formal::name + " : " + Formal::type;
}

const Expr* Formal::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    bool known = checkKnownType(classesMap, type);
    if(known){
        cout << "Type of formal " << name << " known" << endl;
        return NULL;
    }else{
        cout << "Type of formal " << name << " unknown" << endl;
        return this;
    }
}

Formals::Formals(){}

string Formals::eval() const
{
    string formals = "";

    if(Formals::formals.size() != 0)
    {
        auto firstFormal = Formals::formals.rbegin();
        formals = (*firstFormal)->eval();

        for(auto it = Formals::formals.rbegin() + 1; it != Formals::formals.rend(); ++it)
            formals += ", " + (*it)->eval();
    }

    return "[" + formals + "]";
}

const Expr* Formals::checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const {
    if(formals.size() == 0){
        cout << "No formals to check" << endl;
        return NULL;
    }

    // Check all formals
    for(Formal *formal: formals){
        cout << "Checking formal " << formal->getName() << endl;
        const Expr* check = formal->checkUsageUndefinedType(classesMap);
        if(check != NULL)
            return check;
    }

    return NULL;
}

Block::Block(Args *exprList): exprList(exprList){}

string Block::eval() const
{
    string listExpr = "[]";

    if(Block::exprList)
        listExpr = Block::exprList->eval();
    
    return listExpr;
}

If::If(Expr *condExpr, Expr *thenExpr, Expr *elseExpr): condExpr(condExpr), thenExpr(thenExpr), elseExpr(elseExpr){}

string If::eval() const
{
    string elseExpr = "";

    if(If::elseExpr)
        elseExpr = ", " + If::elseExpr->eval();

    return "If(" + If::condExpr->eval() + ", " + If::thenExpr->eval() + elseExpr + ")";
}

While::While(Expr *condExpr, Expr *bodyExpr): condExpr(condExpr), bodyExpr(bodyExpr){}

string While::eval() const 
{
    return "While(" + While::condExpr->eval() + ", " + While::bodyExpr->eval() + ")";
}

Let::Let(const string name, const string type, Expr *scopeExpr, Expr *initExpr): name(name), type(type), scopeExpr(scopeExpr), initExpr(initExpr){}

string Let::eval() const
{
    string initExpr = "";

    if(Let::initExpr)
        initExpr = ", " + Let::initExpr->eval();

    return "Let(" + Let::name + ", " + Let::type + initExpr + ", " + Let::scopeExpr->eval() + ")";
}

Assign::Assign(const string name, Expr *expr): name(name), expr(expr){}

string Assign::eval() const 
{
    return "Assign(" + Assign::name + ", " + Assign::expr->eval() + ")";
}

UnOp::UnOp(const string symbol, Expr *expr): expr(expr), symbol(symbol){}

string UnOp::eval() const 
{
    return "UnOp(" + UnOp::symbol + ", " + UnOp::expr->eval() + ")";
}

Not::Not(Expr *expr): UnOp("not", expr){}

UnaryMinus::UnaryMinus(Expr *expr): UnOp("-", expr){}

IsNull::IsNull(Expr *expr): UnOp("isnull", expr){}

BinOp::BinOp(const string symbol, Expr *leftExpr, Expr *rightExpr): leftExpr(leftExpr), rightExpr(rightExpr), symbol(symbol){}

string BinOp::eval() const 
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

Call::Call(Expr *objExpr, const string methodName, Args *listExpr): objExpr(objExpr), methodName(methodName), listExpr(listExpr){}

string Call::eval() const
{
    string objExpr = "self";
   
    string listExpr = "[]";

    if(Call::listExpr)
        listExpr = Call::listExpr->eval();

    if(Call::objExpr)
        objExpr = Call::objExpr->eval();

    return "Call(" + objExpr + ", " + Call::methodName + ", " + listExpr + ")";
}

New::New(const string typeName): typeName(typeName){}

string New::eval() const
{
    return "New(" + New::typeName + ")";
}

IntegerLiteral::IntegerLiteral(const int intValue): intValue(intValue){}

string IntegerLiteral::eval() const
{
    return to_string(IntegerLiteral::intValue);
}

StringLiteral::StringLiteral(const string stringValue): stringValue(stringValue){}

string hexConvert(char character)
{
    string ret = "\\xhh";
    string ref = "0123456789abcdef";

    ret[2] = ref[character / 16];
    ret[3] = ref[character % 16];

    return ret;
}

string StringLiteral::eval() const
{
    string ret = "\"";

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

string BooleanLiteral::eval() const
{
    string boolString = "false";

    if(BooleanLiteral::booleanValue)
        boolString = "true";

    return boolString;
}

ObjectIdentifier::ObjectIdentifier(const string identifier): identifier(identifier){}

string ObjectIdentifier::eval() const 
{
    return ObjectIdentifier::identifier;
}

Self::Self(){}

string Self::eval() const
{
    return "self";
}

Unit::Unit(){}

string Unit::eval() const
{
    return "unit";
}
