/**
 * Implementation of the block type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>

#include "Block.hpp"
#include "Args.hpp"

using namespace std;

Block::Block(Args *exprList): exprList(exprList){}

string Block::eval() const
{
    string listExpr = "[]";

    if(Block::exprList)
        listExpr = Block::exprList->eval();
    
    return listExpr;
}
