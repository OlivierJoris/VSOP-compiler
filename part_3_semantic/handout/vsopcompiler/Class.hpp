/**
 * Class type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef VSOP_CLASS_HH
#define VSOP_CLASS_HH

#include <string>
#include <vector>
#include <map>

class Field;
class Method;
class Formal;
class Formals;

#include "Expr.hpp"
#include "Field.hpp"
#include "Method.hpp"

/**
 * @brief Represent a class.
 */
class Class : public Expr 
{
    private:
        std::string name; 
        std::string parent;
        std::vector<Field*> fields;
        std::vector<Method*> methods;

    public:
        std::map<std::string, Field*> fieldsMap;
        std::map<std::string, Method*> methodsMap;

        Class(const std::string name, const std::string parent, std::vector<Field*>& fields, std::vector<Method*>& methods, const int line, const int column);
        std::string getName() {return name;}
        std::string getParent() {return parent;}
        std::vector<Field*> getFields() {return fields;}
        std::vector<Method*> getMethods() {return methods;}

        /**
         * @brief Dump the AST corresponding to the class inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the class is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the class.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param scope Scope of identifiers usable by the class.
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(const Program* prog, std::string currentClas, std::vector<std::pair<std::string, Expr*>> scope) override;
};

/**
 * @brief Represent the body of a class.
 */
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

#endif
