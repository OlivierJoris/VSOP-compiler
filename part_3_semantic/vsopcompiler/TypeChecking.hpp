/**
 * Type checking for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef TYPE_CHECKING_HH
#define TYPE_CHECKING_HH

#include "AbstractSyntaxTree.hpp"

/**
 * @brief Check if code is using undefined types.
 * 
 * @param prog AST of code.
 * 
 * @return const std::string Empty string if no error. Otherwise, error message.
 */
const std::string checkUseUndefinedType(Program *prog);

/**
 * @brief Check if a given type is known.
 * 
 * @param types Map of known types.
 * @param toCheck Type to check.
 * @return true if type is known.
 * @return false if type is unknown.
 */
bool checkKnownType(const std::map<std::string, Class*>& types, const std::string& toCheck);

/**
 * @brief Check if given type is primitive type.
 * 
 * @param toCheck Type to check.
 * @return true If given type is primitive.
 * @return false If given type is not primitive.
 */
bool checkPrimitiveType(const std::string& toCheck);

#endif
