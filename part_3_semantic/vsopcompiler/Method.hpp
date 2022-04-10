/**
 * Types related to methods for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef METHOD_HH
#define METHOD_HH

#include <string>
#include <map>
#include <vector>

class Block;
class Args;
class Formal;
class Formals;

#include "Block.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "Formal.hpp"
#include "Args.hpp"

/**
 * @brief Represent a method.
 */
class Method : public Expr 
{
    private:
        std::string name;
        Formals* formals;
        std::string retType;
        Block* block;

    public:
        std::map<std::string, Formal*> formalsMap;
        Method(const std::string name, Formals *formals, const std::string retType, Block *block);
        std::string getName() {return name;}
        std::vector<Formal*> getFormals();
        Formal *getFormals(unsigned int i);
        std::string getRetType() {return retType;}

        /**
         * @brief Dump the AST corresponding to the method inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the method is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

/**
 * @brief Represent a call (dispatch) to a method of an object.
 */
class Call : public Expr 
{
    private:
        Expr *objExpr;
        std::string methodName;
        Args *listExpr;

    public:
        Call(Expr *objExpr, const std::string methodName, Args *listExpr);

        /**
         * @brief Dump the AST corresponding to the dispatch inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the dispatch is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

/**
 * @brief Represent the instantiation of an object.
 */
class New : public Expr
{
    private:
        std::string typeName;
    
    public:
        New(const std::string typeName);

        /**
         * @brief Dump the AST corresponding to the instantiation inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the instantiation is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

/**
 * @brief Represent an object identifier.
 */
class ObjectIdentifier : public Expr
{
    private:
        std::string identifier;
    
    public:
        ObjectIdentifier(const std::string identifier);

        /**
         * @brief Dump the AST corresponding to the identifier inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the identifier is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Always NULL because the object identifier does not use any type.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

/**
 * @brief Represent the keyword self.
 */
class Self : public Expr
{
    public:
        Self();

        /**
         * @brief Dump the AST corresponding to the keyword inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the keyword is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Always NULL because the keyword does not use any type.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

#endif
