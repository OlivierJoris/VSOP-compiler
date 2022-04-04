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

#endif
