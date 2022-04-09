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
        std::string eval() const override;

        /**
         * @brief Check if the formal is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
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
        void addFormal(Formal *formal){formals.push_back(formal);};
        std::vector<Formal*> getFormals() {return formals;}
        Formal *getFormals(unsigned int i) {return formals[i];}

        /**
         * @brief Dump the AST corresponding to the formals inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the formals are using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
