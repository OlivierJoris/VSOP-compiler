/**
 * Block type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef BLOCK_HH
#define BLOCK_HH

#include <string>
#include <map>

class Args;

#include "Args.hpp"
#include "Expr.hpp"
#include "Class.hpp"

/**
 * @brief Represent a block in the source code.
 */
class Block : public Expr
{
    private:
        Args *exprList;

    public:
        Block(Args *exprList, const int line, const int column);

        /**
         * @brief Dump the AST corresponding to the block inside the returned string.
         * 
         * @return std::string AST.
         */
        std::string eval() const override;

        /**
         * @brief Check if the code inside the block is using non defined types.
         * 
         * @param classesMap Map of classes defined throughout the source code.
         * @return Expr*, if using non defined type. Otherwise, null.
         */
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;

        const std::string typeChecking(const Program* prog, std::vector<std::pair<std::string, Expr*>> scope) override {return "";};
};

#endif
