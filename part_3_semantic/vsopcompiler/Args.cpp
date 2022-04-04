/**
 * Implementation of the args type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>

#include "Args.hpp"

using namespace std;

Args::Args(){}

string Args::eval() const
{
    string exprList = "";

    if(Args::exprList.size() != 0)
    {
        auto firstFormal = Args::exprList.rbegin();
        exprList = (*firstFormal)->eval();

        for(auto it = Args::exprList.rbegin() + 1; it != Args::exprList.rend(); ++it)
            exprList += ", " + (*it)->eval();
    }

    return "[" + exprList + "]";
}