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

        /**
         * @brief Perform type checking on the formal.
         * 
         * @return const std::string Always empty string because error is not possible.
         */
        const std::string typeChecking(const Program*, std::string, std::vector<std::pair<std::string, Expr*>>) override {return "";};
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
        std::string eval() const override;

        /**
         * @brief Check if the formals are using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the formals.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param scope Scope of identifiers usable by the formals.
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(const Program* prog, std::string currentClass, std::vector<std::pair<std::string, Expr*>> scope) override;
};

#endif
