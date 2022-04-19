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
        Method(const std::string name, Formals *formals, const std::string retType, Block *block, const int line, const int column);
        std::string getName() {return name;}
        Formals* getFormalsPointer() {return formals;}
        std::vector<Formal*> getFormals();
        Formal *getFormals(unsigned int i);
        std::string getRetType() {return retType;}

        /**
         * @brief Dump the AST corresponding to the method inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the method is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the method.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the method.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
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
        Call(Expr *objExpr, const std::string methodName, Args *listExpr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the dispatch inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the dispatch is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the dispatch.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the dispatch.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the instantiation of an object.
 */
class New : public Expr
{
    private:
        std::string typeName;
    
    public:
        New(const std::string typeName, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the instantiation inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the instantiation is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the instantiation.
         * 
         * @return const std::string Always empty string because error is not possible.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override {return "";};
};

/**
 * @brief Represent an object identifier.
 */
class ObjectIdentifier : public Expr
{
    private:
        std::string identifier;
    
    public:
        ObjectIdentifier(const std::string identifier, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the identifier inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the identifier is using non defined types.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return "";};

        /**
         * @brief Perform type checking on the object identifier.
         * 
         * @param scope Scope of identifiers usable by the identifier.
         * 
         * @return const std::string Always empty string because no possible error.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>> scope) override;
};

/**
 * @brief Represent the keyword self.
 */
class Self : public Expr
{
    public:
        Self(const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the keyword inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the keyword is using non defined types.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return "";};

        /**
         * @brief Perform type checking on the self.
         * 
         * @param currentClass Class in which we are running type checking.
         * 
         * @return const std::string Always empty string because no possible error.
         */
        const std::string typeChecking(const Program*, std::string currentClass, bool, std::vector<std::pair<std::string, Expr*>>) override;
};

#endif
