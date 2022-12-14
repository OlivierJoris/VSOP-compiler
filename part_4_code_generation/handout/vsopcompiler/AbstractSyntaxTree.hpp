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

#include "Expr.hpp"
#include "Class.hpp"
#include "LLVM.hpp"

/**
 * @brief Represent the program.
 */
class Program : public Expr
{
    private:
        std::vector<Class*> classes;

    public:
        std::map<std::string, llvm::Value*> variables;
        std::map<std::string, std::map<std::string, int>> methodsMap; // Map between class name, method name and index
        std::map<std::string, std::map<std::string, int>> fieldsMap; // Map between class name, field name and index
        std::map<std::string, Class*> classesMap;
        std::vector<std::string> errors;

        Program();
        std::vector<Class*> getClasses() const {return classes;}
        void addClass(Class* cls) {classes.push_back(cls);}

        /**
         * @brief Dump the AST inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check for redefinitions.
         * Redefinitions of classes, redefinitions of fields and methods inside a class, and
         * redefinitions of formal arguments inside a method.
         */
        void checkRedefinition();

        /**
         * @brief Check for cycles in inheritance and not defined parent class.
         */
        void checkInheritance();

        /**
         * @brief Check for overridden fields or methods.
         */
        void checkOverrides();

        /**
         * @brief Check if program is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Check if the program contains a Main class with a main method.
         * If the program contains such a method, check if its signature matches the specifications.
         * 
         * @return std::string Empty string if no error. Otherwise, error message.
         */
        std::string checkMain() const;

        /**
         * @brief Perform type checking on the program.
         *
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override;

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

class Unit : public Expr
{
    public:
        Unit(const int line, const int column);

        /**
         * @brief Dump the AST corresponding to Unit inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if unit is using non defined types.
         * 
         * @return const std::string Always empty string because no possible error.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return "";};
        
        /**
         * @brief Perform type checking on the unit.
         * 
         * @return const std::string Always empty string because no possible error.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override {return "";};

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
