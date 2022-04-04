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

class Block : public Expr
{
    private:
        Args *exprList;

    public:
        Block(Args *exprList);
        std::string eval() const override;
        const Expr* checkUsageUndefinedType(const std::map<std::string, Class*>& classesMap) const override;
};

#endif
