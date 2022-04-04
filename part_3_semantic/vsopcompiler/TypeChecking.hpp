/**
 * Type checking for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef TYPE_CHECKING_HH
#define TYPE_CHECKING_HH

#include "AbstractSyntaxTree.hpp"

/**
 * Check if code is using undefined types.
 *
 * @param prog AST of code.
 * 
 * @return 0 if no error. -1, otherwise.
 */
int checkUseUndefinedType(Program *prog);

/**
 * @brief Check if a given type is known.
 * 
 * @param types Map of known types.
 * @param toCheck Type to check.
 * @return true if type is known.
 * @return false if type is unknown.
 */
bool checkKnownType(const std::map<std::string, Class*>& types, const std::string& toCheck);


#endif
