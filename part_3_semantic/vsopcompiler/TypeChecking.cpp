/**
 * Implementation of type checking for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "AbstractSyntaxTree.hpp"
#include "TypeChecking.hpp"

using namespace std;

int checkUseUndefinedType(Program *prog){
    if(prog == NULL)
        return -1;

    const Expr* check = prog->checkUsageUndefinedType(prog->classesMap);
    if(check == NULL)
        return 0;
    else
        return -1;
}

bool checkKnownType(const map<string, Class*>& types, const string& toCheck){
    if(types.find(toCheck) != types.end()){
        return true;
    }else{
        if(toCheck.compare("int32") == 0)
            return true;
        if(toCheck.compare("bool") == 0)
            return true;
        if(toCheck.compare("string") == 0)
            return true;
        if(toCheck.compare("unit") == 0)
            return true;
        return false;
    }
}
