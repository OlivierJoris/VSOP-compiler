/**
 * Operator types for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef OPERATORS_HH
#define OPERATORS_HH

#include <string>
#include <map>
#include <vector>

#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent the assign operator.
 */
class Assign : public Expr 
{
    private:
        std::string name;
        Expr *expr;

    public:
        Assign(const std::string name, Expr* expr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the assign operator inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent a generic unary operator.
 */
class UnOp : public Expr 
{
    protected:
        Expr* expr;
        std::string symbol;

    public:
        UnOp(const std::string symbol, Expr *expr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the operator inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the unary not.
 */
class Not : public UnOp
{
    public:
        Not(Expr *expr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the unary minus.
 */
class UnaryMinus : public UnOp
{
    public:
        UnaryMinus(Expr *expr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the isNull operator.
 */
class IsNull : public UnOp
{
    public:
        IsNull(Expr *expr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent a generic binary operator.
 */
class BinOp : public Expr
{
    protected:
        Expr *leftExpr;
        Expr *rightExpr;
        std::string symbol;
    
    public:
        BinOp(const std::string symbol, Expr *leftExpr, Expr *rightExpr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the operator inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the plus operator.
 */
class Plus : public BinOp
{
    public:
        Plus(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the minus operator.
 */
class Minus : public BinOp
{
    public:
        Minus(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the multiplication operator.
 */
class Times : public BinOp
{
    public:
        Times(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the division operator.
 */
class Div : public BinOp
{
    public :
        Div(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the and operator.
 */
class And : public BinOp
{
    public:
        And(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the lower equal operator.
 */
class LowerEqual : public BinOp
{
    public:
        LowerEqual(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the lower operator.
 */
class Lower : public BinOp
{
    public:
        Lower(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the comparison operator.
 */
class Equal : public BinOp
{
    public:
        Equal(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

/**
 * @brief Represent the power operator.
 */
class Pow : public BinOp
{
    public:
        Pow(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
