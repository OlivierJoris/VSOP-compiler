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
        IntegerLiteral(const int intValue, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the integer inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the literal is using non defined types.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return "";};

        /**
         * @brief Perform type checking on the literal.
         *
         * @return const std::string Always empty string because no possible error.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override {return "";};
};

/**
 * @brief Represent a string literal.
 */
class StringLiteral : public Expr
{
    private:
        std::string stringValue;
    
    public:
        StringLiteral(const std::string stringValue, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the string inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the string is using non defined types.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return "";};

        /**
         * @brief Perform type checking on the literal.
         * 
         * @return const std::string Always empty string because no possible error.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override {return "";};

};

/**
 * @brief Represent a boolean.
 */
class BooleanLiteral : public Expr
{
    private:
        bool booleanValue;
    
    public:
        BooleanLiteral(const bool booleanValue, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the boolean inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the boolean is using non defined types.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>&) const override {return "";};

        /**
         * @brief Perform type checking on the literal.
         * 
         * @return const std::string Always empty string because no possible error.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override {return "";};
};

#endif
