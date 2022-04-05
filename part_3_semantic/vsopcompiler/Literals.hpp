/**
 * Types related to the literals for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef LITERAL_HH
#define LITERAL_HH

#include <string>
#include <map>
#include <vector>

#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent an integer literal.
 */
class IntegerLiteral : public Expr 
{
    private:
        int intValue;

    public:
        IntegerLiteral(const int intValue);

        /**
         * @brief Dump the AST corresponding to the integer inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the literal is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Always NULL because Unit does not use any type.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};
};

/**
 * @brief Represent a string literal.
 */
class StringLiteral : public Expr
{
    private:
        std::string stringValue;
    
    public:
        StringLiteral(const std::string stringValue);

        /**
         * @brief Dump the AST corresponding to the string inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the string is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Always NULL because Unit does not use any type.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};

};

/**
 * @brief Represent a boolean.
 */
class BooleanLiteral : public Expr
{
    private:
        bool booleanValue;
    
    public:
        BooleanLiteral(const bool booleanValue);

        /**
         * @brief Dump the AST corresponding to the boolean inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the boolean is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Always NULL because Unit does not use any type.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return NULL;};
};

#endif
