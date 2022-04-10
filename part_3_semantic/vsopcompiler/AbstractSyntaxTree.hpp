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

/**
 * @brief Represent the program.
 */
class Program : public Expr
{
    private:
        std::vector<Class*> classes;

    public:
        std::map<std::string, Class*> classesMap;
        std::vector<std::string> errors;

        Program();
        std::vector<Class*> getClasses() {return classes;}
        void addClass(Class* cls) {classes.push_back(cls);}

        /**
         * @brief Dump the AST inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

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
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Check if the program contains a Main class with a main method.
         * If the program contains such a method, check if its signautre matches the specifications.
         * 
         * @return std::string Empty string if no error. Otherwise, error message.
         */
        std::string checkMain() const;

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
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
        std::string eval() const override;

        /**
         * @brief Check if unit is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Always NULL because Unit does not use any type.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};
        
        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

#endif
