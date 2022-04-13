/**
 * Implementation of the if type for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include <iostream>
#include <string>
#include <map>

#include "If.hpp"
#include "Expr.hpp"
#include "Class.hpp"
#include "AbstractSyntaxTree.hpp"
#include "TypeChecking.hpp"

using namespace std;

If::If(Expr *condExpr, Expr *thenExpr, Expr *elseExpr, const int line, const int column): condExpr(condExpr), thenExpr(thenExpr), elseExpr(elseExpr){
    this->line = line;
    this->column = column;
}

string If::dumpAST(bool annotated) const
{
    string elseExpr = "";

    if(If::elseExpr)
        elseExpr = ", " + If::elseExpr->dumpAST(annotated);

    if(annotated)
        return "If(" + If::condExpr->dumpAST(annotated) + ", " + If::thenExpr->dumpAST(annotated) + elseExpr + ") : " + type;
    else
        return "If(" + If::condExpr->dumpAST(annotated) + ", " + If::thenExpr->dumpAST(annotated) + elseExpr + ")";
}

const string If::checkUsageUndefinedType(const map<string, Class*>& classesMap) const {
    // Check cond expression if any
    if(condExpr){
        const string check = condExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check then expression if any
    if(thenExpr){
        const string check = thenExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    // Check els expression if any
    if(elseExpr){
        const string check = elseExpr->checkUsageUndefinedType(classesMap);
        if(check.compare(""))
            return check;
    }

    return "";
}

const string If::typeChecking(const Program* prog, string currentClass, vector<pair<string, Expr*>> scope){
    // Type checking on condition
    if(condExpr){
        const string err = condExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Type checking on then branch
    if(thenExpr){
        const string err = thenExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Type checking on else branch
    if(elseExpr){
        const string err = elseExpr->typeChecking(prog, currentClass, scope);
        if(err.compare(""))
            return err;
    }

    // Check if type of condition is bool
    if(condExpr && condExpr->type.compare("bool")){
        const string err = to_string(condExpr->getLine()) + ": semantic error: " + to_string(condExpr->getColumn())
            + ":" + "condition must have type bool (is type " + condExpr->type + ").";
        return err;
    }

    // Check if types of thenExpr and elseExpr agree
    if(thenExpr && elseExpr){ // Both then and else branches
        if(!checkPrimitiveType(thenExpr->type) && !checkPrimitiveType(elseExpr->type) && thenExpr->type.compare("unit") && elseExpr->type.compare("unit")){
            // Both are not primitive types -> type of if is first ancestor
            vector<string> listAncestorThen = vector<string>();
            vector<string> listAncestorElse = vector<string>();
            listAncestorThen.push_back(thenExpr->type);
            listAncestorElse.push_back(elseExpr->type);
            auto classes = prog->getClasses();

            string tmpThen = thenExpr->type;
            while(tmpThen.compare("Object")){
                auto tmpClass = prog->classesMap.find(tmpThen);
                if(tmpClass != prog->classesMap.end()){
                    Class *cls = (*tmpClass).second;
                    if(cls){
                        tmpThen = cls->getParent();
                        listAncestorThen.push_back(tmpThen);
                    }else
                        break;
                }else
                    break;
            }

            string tmpElse = elseExpr->type;
            while(tmpElse.compare("Object")){
                auto tmpClass = prog->classesMap.find(tmpElse);
                if(tmpClass != prog->classesMap.end()){
                    Class *cls = (*tmpClass).second;
                    if(cls){
                        tmpElse = cls->getParent();
                        listAncestorThen.push_back(tmpElse);
                    }else
                        break;
                }else
                    break;
            }

            string firstCommonAncestor = "";
            for(string ancestorThen: listAncestorThen){
                if(firstCommonAncestor.compare("")) // allow to stop looking for ancestor when first one found
                    break;
                for(string ancestorElse: listAncestorElse){
                    if(firstCommonAncestor.compare("")) // allow to stop looking for ancestor when first one found
                        break;
                    if(!ancestorThen.compare(ancestorElse))
                        firstCommonAncestor = ancestorThen;
                }
            }

            type = firstCommonAncestor;

        }else if(!(thenExpr->type.compare(elseExpr->type)) && checkPrimitiveType(thenExpr->type)){
            // If both have same primitive type -> type of if is the same type
            type = thenExpr->type;
        }else if(!(thenExpr->type.compare("unit")) || !(elseExpr->type.compare("unit"))){
            // If (at least) one branch has type unit -> type of if is unit
            type = "unit";
        }else{
            // Types of branches do not agree
            const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: types of <expr_t> and <expr_e> do not agree.";
            return err;
        }
    }else if(thenExpr && !elseExpr){ // No else branch
        type = "unit";
    }else{
        const string err = to_string(getLine()) + ":" + to_string(getColumn()) + ": semantic error: types of <expr_t> and <expr_e> do not agree.";
        return err;
    }

    return "";
}
