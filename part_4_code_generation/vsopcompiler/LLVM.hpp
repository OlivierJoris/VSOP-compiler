/**
 * LLVM class for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#ifndef LLVM_HH
#define LLVM_HH

#include <string>
#include <map>

#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

#include "AbstractSyntaxTree.hpp"

/**
 * @brief Represent LLVM code generation (singleton design pattern).
 */
class LLVM
{
    private:
        static LLVM *instance;
        std::string fileName;

    public:
        llvm::LLVMContext *context;
        llvm::Module *mdl;
        llvm::IRBuilder<> *builder;

        /**
         * @brief Return the singleton instance.
         * 
         * @param program Program for which we are generating code.
         * @param fileName Name of the file for which we are generating code.
         * 
         * @return LLVM * instance of LLVM singleton.
         */
        static LLVM *getInstance(Program *program, const std::string &fileName);

        /**
         * @brief Constructor.
         * 
         * @param program Program for which we are generating code.
         * @param fileName Name of the file for which we are generating code.
         */
        LLVM(Program *program, const std::string &fileName);

        /**
         * @brief Return the associated LLVM type.
         * 
         * @param type string corresponding type.
         * 
         * @return llvm::Type * LLVM Type.
         */
        llvm::Type *getType(const std::string type);

        /**
         * @brief Return the associated LLVM type.
         * 
         * @return llvm::Type * LLVM Type.
         */
        void displayIROnStdout();
};

#endif 