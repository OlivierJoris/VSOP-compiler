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
#include "LLVM.hpp"

using namespace std;

IntegerLiteral::IntegerLiteral(const int intValue, const int line, const int column): intValue(intValue){
    this->line = line;
    this->column = column;
    this->type = "int32";
}

string IntegerLiteral::dumpAST(bool annotated) const
{
    if(annotated)
        return to_string(IntegerLiteral::intValue) + " : " + type;
    else
        return to_string(IntegerLiteral::intValue);
}

llvm::Value *IntegerLiteral::generateCode(Program *program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(program, fileName);
    return llvm::ConstantInt::get(llvm->getType("int32"), intValue);
}

StringLiteral::StringLiteral(const string stringValue, const int line, const int column): stringValue(stringValue){
    this->line = line;
    this->column = column;
    this->type = "string";
}

string hexConvert(char character)
{
    string ret = "\\xhh";
    string ref = "0123456789abcdef";

    ret[2] = ref[character / 16];
    ret[3] = ref[character % 16];

    return ret;
}

string StringLiteral::dumpAST(bool annotated) const
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

    if(annotated)
        return ret + "\" : string";
    else
        return ret + "\"";
}

llvm::Value *StringLiteral::generateCode(Program *Program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(Program, fileName);

    std::string formatedString = "\"";

    for(char character: StringLiteral::stringValue){

        if(character != '\"' && character != '\\'){
            if(character >= 32 && character <= 126)
                formatedString += character;
            else 
                formatedString += hexConvert(character);
        }
        else
            formatedString += hexConvert(character);
    }

    formatedString += "\"";

    return llvm->builder->CreateGlobalStringPtr(formatedString);
}

BooleanLiteral::BooleanLiteral(const bool booleanValue, const int line, const int column): booleanValue(booleanValue){
    this->line = line;
    this->column = column;
    this->type = "bool";
}

string BooleanLiteral::dumpAST(bool annotated) const
{
    string boolString = "false";

    if(BooleanLiteral::booleanValue)
        boolString = "true";

    if(annotated)
        return boolString + " : bool";
    else
        return boolString;
}

llvm::Value *BooleanLiteral::generateCode(Program *Program, Class* cls,const std::string &fileName){
    LLVM *llvm = LLVM::getInstance(Program, fileName);

    if(booleanValue)
        return llvm::ConstantInt::get(llvm->getType("bool"), 1);
    
    return llvm::ConstantInt::get(llvm->getType("bool"), 0);
}
