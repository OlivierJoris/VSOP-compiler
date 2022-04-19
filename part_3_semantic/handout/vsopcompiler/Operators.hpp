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
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the assignment.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the assignment.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
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
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the operator.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override {return "";};
};

/**
 * @brief Represent the unary not.
 */
class Not : public UnOp
{
    public:
        Not(Expr *expr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the operator.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the operator.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the unary minus.
 */
class UnaryMinus : public UnOp
{
    public:
        UnaryMinus(Expr *expr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the operator.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the operator.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string curentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the isNull operator.
 */
class IsNull : public UnOp
{
    public:
        IsNull(Expr *expr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the operator.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the operator.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
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
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the operator.
         *
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(const Program*, std::string, bool, std::vector<std::pair<std::string, Expr*>>) override {return "";};
};

/**
 * @brief Represent a generic arithmetic binary operator.
 */
class ArithmeticBinOp : public BinOp
{
    public:
        ArithmeticBinOp(const std::string, Expr *leftExpr, Expr *rightExpr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the operator inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the operator.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the operator.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the plus operator.
 */
class Plus : public ArithmeticBinOp
{
    public:
        Plus(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the minus operator.
 */
class Minus : public ArithmeticBinOp
{
    public:
        Minus(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the multiplication operator.
 */
class Times : public ArithmeticBinOp
{
    public:
        Times(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the division operator.
 */
class Div : public ArithmeticBinOp
{
    public :
        Div(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the power operator.
 */
class Pow : public ArithmeticBinOp
{
    public:
        Pow(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent a generic binary comparison.
 */
class BinaryComparison : public BinOp
{
    public:
        BinaryComparison(const std::string, Expr *leftExpr, Expr *rightExpr, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the operator inside the returned string.
         * 
         * @param annotated True, annotated AST. False, AST.
         * 
         * @return std::string AST.
         */
        std::string dumpAST(bool annotated) const override;

        /**
         * @brief Check if the operator is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the operator.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the operator.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
            ) override;
};

/**
 * @brief Represent the lower equal operator.
 */
class LowerEqual : public BinaryComparison
{
    public:
        LowerEqual(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the lower operator.
 */
class Lower : public BinaryComparison
{
    public:
        Lower(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the comparison operator.
 */
class Equal : public BinOp
{
    public:
        Equal(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the comparison operator.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param scope Scope of identifiers usable by the operator.
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

/**
 * @brief Represent the and operator.
 */
class And : public BinOp
{
    public:
        And(Expr *leftExpr, Expr *rightExpr, const int line, const int column);
        const std::string checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        /**
         * @brief Perform type checking on the and operator.
         * 
         * @param prog Program that we are analyzing.
         * @param currentClass Class in which we are running type checking.
         * @param inFieldInit Whether typeChecking is called inside a field initializer.
         * @param scope Scope of identifiers usable by the operator.
         * 
         * @return const std::string Empty string if no error. Otherwise, error message.
         */
        const std::string typeChecking(
            const Program* prog,
            std::string currentClass,
            bool inFieldInit,
            std::vector<std::pair<std::string, Expr*>> scope
        ) override;
};

#endif
