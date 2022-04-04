/**
 * Implementation of types related to literals for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <string>
#include <map>
#include <vector>

#include "Literals.hpp"
#include "Expr.hpp"
#include "Class.hpp"

using namespace std;

IntegerLiteral::IntegerLiteral(const int intValue): intValue(intValue){}

string IntegerLiteral::eval() const
{
    return to_string(IntegerLiteral::intValue);
}

StringLiteral::StringLiteral(const string stringValue): stringValue(stringValue){}

string hexConvert(char character)
{
    string ret = "\\xhh";
    string ref = "0123456789abcdef";

    ret[2] = ref[character / 16];
    ret[3] = ref[character % 16];

    return ret;
}

string StringLiteral::eval() const
{
    string ret = "\"";

    for(char character: StringLiteral::stringValue){

        if(character != '\"' && character != '\\'){
            if(character >= 32 && character <= 126)
                ret += character;
            else 
                ret += hexConvert(character);
        }
        else
            ret += hexConvert(character);
    }

    return ret + "\"";
}

BooleanLiteral::BooleanLiteral(const bool booleanValue): booleanValue(booleanValue){}

string BooleanLiteral::eval() const
{
    string boolString = "false";

    if(BooleanLiteral::booleanValue)
        boolString = "true";

    return boolString;
}
