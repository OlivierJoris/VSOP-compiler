/**
 * Formal type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef FORMAL_HH
#define FORMAL_HH

#include <string>
#include <map>
#include <vector>

#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent a formal argument of a method. 
 */
class Formal : public Expr 
{
    private:
        std::string name;
        std::string type;
    
    public:
        Formal(const std::string name, const std::string type, const int line, const int column);
        std::string getName() {return name;}
        std::string getType() {return type;}

        /**
         * @brief Dump the AST corresponding to the formal inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool) const override;

        /**
         * @brief Check if the formal is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the formal.
         * 
         * @return const std::string Always empty string because error is not possible.
         */
        const std::string typeChecking(
            const Program*,
            std::string,
            bool,
            std::vector<std::pair<std::string, Expr*>>
        ) override {return "";};

        llvm::Value *generateCode(Program *Program, Class* cls,const std::string &fileName) override;
};

/**
 * @brief Represent all the formals of a method.
 */
class Formals : public Expr
{
    private:
        std::vector<Formal*> formals;
    
    public:
        Formals();
        void addFormal(Formal *formal) {formals.push_back(formal);};
        std::vector<Formal*> getFormals() {return formals;}
        Formal *getFormals(unsigned int i) {return formals[i];}

        /**
         * @brief Dump the AST corresponding to the formals inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool) const override;

        /**
         * @brief Check if the formals are using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the formals.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the formals.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;

        /**
         * @brief Perform code generation on the expression.
         * 
         * @param Program Program for which we are generating code.
         * @param cls current Class in which we are generating code.
         * @param fileName Name of the file for which we are generating code.
         * 
         * @return llvm::Value* Value of the expression.
         */
        llvm::Value *generateCode(Program *Program, Class* cls, const std::string &fileName) override;
};

#endif
