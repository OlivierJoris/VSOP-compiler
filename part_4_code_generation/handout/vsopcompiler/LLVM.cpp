/**
 * Implementation of the CodeGeneration class for VSOP compiler.
 *
 * @authors Goffart Maxime & Joris Olivier
*/

#include "LLVM.hpp"

#include <stack>
#include <iostream>
#include <fstream>

LLVM::LLVM(Program* program, const std::string &fileName): fileName(fileName)
{
    context = new llvm::LLVMContext();
    mdl = new llvm::Module(fileName, *context);
    builder = new llvm::IRBuilder<>(*context);

    for(auto cls: program->classesMap)
    {
        // Declare structure
        llvm::StructType::create(*context, cls.first);
        // Declare VTable
        llvm::StructType::create(*context, cls.first + "VTable");
    }

    /****************** Declare 'malloc' function ******************/
    // void *malloc(size_t size);
    
    // Signature
    auto mallocType = llvm::FunctionType::get(
        llvm::Type::getInt8Ty(*context)->getPointerTo(), // The return type
        {llvm::Type::getInt64Ty(*context)},              // The arguments
        false);                                    // No variable number of arguments
    // Declare the function
    llvm::Function::Create(
        mallocType,                  // The signature
        llvm::GlobalValue::ExternalLinkage, // The linkage: external, malloc is implemented elsewhere
        "malloc",                     // The name
        mdl);                      // The LLVM module

    // Declare power method
    auto powerType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context), // The return type
        {llvm::Type::getInt32Ty(*context), llvm::Type::getInt32Ty(*context)}, // The arguments
        false);                                    // No variable number of arguments
    llvm::Function::Create(
        powerType,                  // The signature
        llvm::Function::ExternalLinkage, // The linkage: external, malloc is implemented elsewhere
        "power",                     // The name
        mdl);                      // The LLVM module

    // Declare new method of Object class
    auto newMethodType = llvm::FunctionType::get(
        getType(std::string("Object")),    // The return type
        {},                   // The arguments
        false);               // No variable number of arguments 

    llvm::Function::Create(
        newMethodType,                         // The signature
        llvm::GlobalValue::ExternalLinkage, // The linkage
        std::string("Object___new"),                  // The name
        mdl);    

    // Declare init method of Object class
    auto initMethodType = llvm::FunctionType::get(
        getType("Object"),    // The return type
        {getType("Object")},  // The arguments
        false);               // No variable number of arguments
    
    llvm::Function::Create(
        initMethodType,                         // The signature
        llvm::GlobalValue::ExternalLinkage, // The linkage
        std::string("Object___init"),                  // The name
        mdl);

    // Declare methods of the Object class
    for(auto method: program->classesMap["Object"]->methodsMap)
    {
        auto formals = std::vector<llvm::Type*>();
        formals.push_back(getType("Object"));

        for(auto formal: method.second->getFormals())
            formals.push_back(getType(formal->getType()));

        auto methodType = llvm::FunctionType::get(getType(method.second->getRetType()), formals, false);
        llvm::Function::Create(methodType, llvm::GlobalValue::ExternalLinkage, "Object__" + std::string(method.second->getName()), mdl);
    }
    
    // Declare class methods
    for(auto cls: program->classesMap)
    {
        if(cls.first == "Object")
            continue;

        // Declare new method of Object class
        auto newMethodType = llvm::FunctionType::get(
        getType(cls.first),    // The return type
        {},                   // The arguments
        false);   

        mdl->getOrInsertFunction(cls.first + std::string("___new"), newMethodType);

        // Declare init method of Object class
        auto initMethodType = llvm::FunctionType::get(
        getType(cls.first),    // The return type
        {getType(cls.first)},  // The arguments
        false);

        mdl->getOrInsertFunction(cls.first + std::string("___init"), initMethodType);

        for(auto method: cls.second->getMethods())
        {
            auto formals = std::vector<llvm::Type*>();
            formals.push_back(getType(cls.first));

            for(auto formal: method->getFormals())
                formals.push_back(getType(formal->getType()));
            
            auto methodType = llvm::FunctionType::get(getType(method->getRetType()), formals, false);
            mdl->getOrInsertFunction(cls.first + "__" + method->getName(), methodType);
        }
    }

    // Declare inherited methods
    for(auto cls: program->classesMap)
    {
        llvm::StructType *structType = mdl->getTypeByName(cls.first + "VTable");
        auto types = std::vector<llvm::Type*>();
        auto methods = std::vector<llvm::Constant*>();

        std::map<std::string, bool> isOverriding;
        std::map<std::string, int> indexes;
        std::stack<std::string> parentClasses = std::stack<std::string>();
        
        std::string currentClass = cls.first;
        parentClasses.push(currentClass);
        while(currentClass != "Object")
        {
            currentClass = program->classesMap[currentClass]->getParent();
            parentClasses.push(currentClass);
        }
        
        int i = 0;
        while(!parentClasses.empty())
        {
            std::string parentClass = parentClasses.top();
            parentClasses.pop();

            for(auto method: program->classesMap[parentClass]->methodsMap)
            {
                if(!isOverriding[method.first])
                {
                    auto tmpType = mdl->getFunction(parentClass + "__" + method.first)->getFunctionType();
                    methods.push_back(mdl->getFunction(parentClass + "__" + method.first));
                    types.push_back(llvm::PointerType::get(tmpType, 0));
                    isOverriding[method.first] = true;
                    indexes[method.first] = i;
                    program->methodsMap[cls.first][method.first] = i;
                }
                else
                {
                    methods[indexes[method.first]] = mdl->getFunction(parentClass + "__" + method.first);
                    auto tmpType = ((llvm::Function*) methods[indexes[method.first]])->getFunctionType();
                    types[indexes[method.first]] = llvm::PointerType::get(tmpType, 0);
                }
                ++i;
            }
        }
        structType->setBody(types);
        if(cls.first != "Object")
        {
            auto cstStruct = llvm::ConstantStruct::get(structType, methods);
            llvm::GlobalVariable *globalVTable = (llvm::GlobalVariable *) mdl->getOrInsertGlobal(cls.first + "___vtable", structType);
            globalVTable->setInitializer(cstStruct);
            globalVTable->setConstant(true);
        }
    }

    // Declare inherited fields 
    for(auto cls: program->classesMap)
    {
        llvm::StructType *structType = (llvm::StructType *) mdl->getTypeByName(cls.first);
        auto types = std::vector<llvm::Type*>();
        types.push_back(llvm::PointerType::get(mdl->getTypeByName(cls.first + "VTable"), 0));

        std::stack<std::string> parentClasses = std::stack<std::string>();
        std::string currentClass = cls.first;
        parentClasses.push(currentClass);
        while(currentClass != "Object")
        {
            currentClass = program->classesMap[currentClass]->getParent();
            parentClasses.push(currentClass);
        }

        while(!parentClasses.empty())
        {
            std::string parentClass = parentClasses.top();
            parentClasses.pop();

            for(auto field: program->classesMap[parentClass]->fieldsMap)
                types.push_back(getType(field.second->getType()));
        }

        structType->setBody(types);
    }

    mdl->getOrInsertFunction("main", llvm::FunctionType::get(getType("int32"), false));
    auto entryBlock = llvm::BasicBlock::Create(*context, "entry", mdl->getFunction("main"));
    builder->SetInsertPoint(entryBlock);
    auto main = mdl->getFunction(std::string("Main___new"));
    auto mainValue = builder->CreateCall(main);
    auto mainMethod = mdl->getFunction(std::string("Main__main"));
    auto mainReturn = builder->CreateCall(mainMethod, {mainValue});
    builder->CreateRet(mainReturn);
}

// Singleton design pattern
LLVM *LLVM::instance = NULL;

LLVM *LLVM::getInstance(Program *program, const std::string &fileName)
{
    if(instance == NULL)
        instance = new LLVM(program, fileName);
    
    return instance;
}

llvm::Type *LLVM::getType(const std::string type)
{
    if (type == "int32")
        return llvm::Type::getInt32Ty(*context);
    else if (type == "bool")
        return llvm::Type::getInt1Ty(*context);
    else if (type == "unit")
        return llvm::Type::getVoidTy(*context);    
    else if (type == "string")
        return llvm::PointerType::getInt8PtrTy(*context);
    else
        return llvm::PointerType::get(mdl->getTypeByName(type), 0);
}

void LLVM::displayIROnStdout(){
    std::string outStr;
    llvm::raw_string_ostream oss(outStr);
    mdl->print(oss, nullptr);
    std::cout << outStr << std::endl;
}

void LLVM::optimizeCode()
{
//     llvm::legacy::FunctionPassManager functionPassManager(mdl);

//     // Promote allocas to registers.
//     functionPassManager.add(llvm::createPromoteMemoryToRegisterPass());
//     // Do simple "peephole" optimizations
//     functionPassManager.add(llvm::createInstructionCombiningPass());
//     // Reassociate expressions.
//     functionPassManager.add(llvm::createReassociatePass());
//     // Eliminate Common SubExpressions.
//     functionPassManager.add(llvm::createGVNPass());
//     // Simplify the control flow graph (deleting unreachable blocks etc).
//     functionPassManager.add(llvm::createCFGSimplificationPass());

//     functionPassManager.doInitialization();

//     for(auto it = mdl->begin(); it != mdl->end(); ++it) 
//         functionPassManager.run(*it);
}

void LLVM::generateExecutable(const std::string &fileName)
{
    std::string execName = fileName.substr(0, fileName.find_last_of("."));
    std::ofstream exec(execName + ".ll");
    std::string outStr;
    llvm::raw_string_ostream oss(outStr);
    mdl->print(oss, nullptr);
	exec << outStr;
	exec.close();
    std::string cmd = "clang -Wno-override-module -o " + execName + " " + execName + ".ll" + " runtime/*.c";
    char c[cmd.size() + 1];
    strcpy(c, cmd.c_str());
    system(c);
}
