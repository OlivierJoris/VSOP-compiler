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

        Class(const std::string name, const std::string parent, std::vector<Field*>& fields, std::vector<Method*>& methods);
        std::string getName() {return name;}
        std::string getParent() {return parent;}
        std::vector<Field*> getFields() {return fields;}
        std::vector<Method*> getMethods() {return methods;}

        /**
         * @brief Dump the AST corresponding to the class inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the class is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
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
