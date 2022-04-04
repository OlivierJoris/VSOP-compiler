/**
 * Abstract syntax tree for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef ABSTRACTSYNTAXTREE_HH
#define ABSTRACTSYNTAXTREE_HH

#include <string>
#include <vector>
#include <map>

class Class;
       
class Expr 
{
    public:
        virtual std::string eval() const = 0;

        /**
         * @brief Check if expr is using non defined type.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        virtual const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const = 0;
};

class Field : public Expr
{
    private:
        std::string name;
        std::string type;
        Expr *initExpr;

    public:
        Field(const std::string name, const std::string type, Expr *initExpr);
        std::string getName() {return name;}
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Args : public Expr
{
    private:
        std::vector<Expr*> exprList;

    public:
        Args();
        void addExpr(Expr *expr) {exprList.push_back(expr);}
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Block : public Expr
{
    private:
        Args *exprList;

    public:
        Block(Args *exprList);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Formal : public Expr 
{
    private:
        std::string name;
        std::string type;
    
    public:
        Formal(const std::string name, const std::string type);
        std::string eval() const override;
        std::string getName() {return name;}
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        std::string getType() {return type;}
};

class Formals : public Expr
{
    private:
        std::vector<Formal*> formals;
    
    public:
        Formals();
        void addFormal(Formal *formal){formals.push_back(formal);};
        std::string eval() const override;
        std::vector<Formal*> getFormals() {return formals;}
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        Formal *getFormals(unsigned int i) {return formals[i];}
};

class Method : public Expr 
{
    private:
        std::string name;
        Formals* formals;
        std::string retType;
        Block* block;

    public:
        Method(const std::string name, Formals *formals, const std::string retType, Block *block);
        std::string eval() const override;
        std::string getName() {return name;}
        std::vector<Formal*> getFormals() {return formals->getFormals();}
        Formal *getFormals(unsigned int i) {return formals->getFormals(i);}
        std::string getRetType() {return retType;}
        std::map<std::string, Formal*> formalsMap;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class Class : public Expr 
{
    private:
        std::string name; 
        std::string parent;
        std::vector<Field*> fields;
        std::vector<Method*> methods;

    public:
        Class(const std::string name, const std::string parent, std::vector<Field*>& fields, std::vector<Method*>& methods);
        std::string eval() const override;
        std::string getName() {return name;}
        std::vector<Field*> getFields() {return fields;}
        std::vector<Method*> getMethods() {return methods;}
        std::string getParent() {return parent;}
        std::map<std::string, Field*> fieldsMap;
        std::map<std::string, Method*> methodsMap;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class ClassBody
{
    private:
        std::vector<Field*> fields;
        std::vector<Method*> methods;

    public:
        ClassBody();
        std::vector<Field*> getFields() {return fields;}
        std::vector<Method*> getMethods() {return methods;}
        void addField(Field *field) {fields.push_back(field);}
        void addMethod(Method *method) {methods.push_back(method);}
};

class Program : public Expr
{
    private:
        std::vector<Class*> classes;

    public:
        Program();
        void checkRedefinition();
        void checkInheritance();
        void checkOverrides();
        void addClass(Class* cls) {classes.push_back(cls);}
        std::string eval() const override;
        std::vector<Class*> getClasses() {return classes;}
        std::map<std::string, Class*> classesMap;
        std::vector<std::string> errors;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

class If : public Expr 
{
    private:
        Expr *condExpr;
        Expr *thenExpr;
        Expr *elseExpr;
    
    public:
        If(Expr *condExpr, Expr *thenExpr, Expr *elseExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class While : public Expr
{
    private:
        Expr *condExpr;
        Expr *bodyExpr;

    public:
        While(Expr *condExpr, Expr *bodyExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Let : public Expr 
{
    private:
        std::string name;
        std::string type;
        Expr *scopeExpr;
        Expr *initExpr;
    
    public:
        Let(const std::string name, const std::string type, Expr *scopeExpr, Expr *initExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Assign : public Expr 
{
    private:
        std::string name;
        Expr *expr;

    public:
        Assign(const std::string name, Expr* expr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class UnOp : public Expr 
{
    protected:
        Expr* expr;
        std::string symbol;

    public:
        UnOp(const std::string symbol, Expr *expr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Not : public UnOp
{
    public:
        Not(Expr *expr);
};

class UnaryMinus : public UnOp
{
    public:
        UnaryMinus(Expr *expr);
};

class IsNull : public UnOp
{
    public:
        IsNull(Expr *expr);
};

class BinOp : public Expr
{
    protected:
        Expr *leftExpr;
        Expr *rightExpr;
        std::string symbol;
    
    public:
        BinOp(const std::string symbol, Expr *leftExpr, Expr *rightExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Plus : public BinOp
{
    public:
        Plus(Expr *leftExpr, Expr *rightExpr);
};

class Minus : public BinOp
{
    public:
        Minus(Expr *leftExpr, Expr *rightExpr);
};

class Times : public BinOp
{
    public:
        Times(Expr *leftExpr, Expr *rightExpr);
};

class Div : public BinOp
{
    public :
        Div(Expr *leftExpr, Expr *rightExpr);
};

class And : public BinOp
{
    public:
        And(Expr *leftExpr, Expr *rightExpr);
};

class LowerEqual : public BinOp
{
    public:
        LowerEqual(Expr *leftExpr, Expr *rightExpr);
};

class Lower : public BinOp
{
    public:
        Lower(Expr *leftExpr, Expr *rightExpr);
};

class Equal : public BinOp
{
    public:
        Equal(Expr *leftExpr, Expr *rightExpr);
};

class Pow : public BinOp
{
    public:
        Pow(Expr *leftExpr, Expr *rightExpr);
};

class Call : public Expr 
{
    private:
        Expr *objExpr;
        std::string methodName;
        Args *listExpr;

    public:
        Call(Expr *objExpr, const std::string methodName, Args *listExpr);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};  

class New : public Expr
{
    private:
        std::string typeName;
    
    public:
        New(const std::string typeName);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class IntegerLiteral : public Expr 
{
    private:
        int intValue;

    public:
        IntegerLiteral(const int intValue);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class StringLiteral : public Expr
{
    private:
        std::string stringValue;
    
    public:
        StringLiteral(const std::string stringValue);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};

};

class BooleanLiteral : public Expr
{
    private:
        bool booleanValue;
    
    public:
        BooleanLiteral(const bool booleanValue);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class ObjectIdentifier : public Expr
{
    private:
        std::string identifier;
    
    public:
        ObjectIdentifier(const std::string identifier);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Self : public Expr
{
    public:
        Self();
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

class Unit : public Expr
{
    public:
        Unit();
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override {return NULL;};
};

#endif
