//
// Created by 游添予 on 2021/6/2.
//

#ifndef POSFOL_CODEGEN_H
#define POSFOL_CODEGEN_H

#include "../tree/node.h"
#include "../tree/type.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/Pass.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>
#include <string>
#include <fstream>
#include "../semantic/symbol.h"

class CodeGen {
    llvm::LLVMContext llvmContext;
    llvm::Module module;
    llvm::IRBuilder<> irBuilder;
    SymbolTable symbolTable;
    bool hasVisitedMainFunction = false;
    std::stack<llvm::BasicBlock *> blockStack;
    std::unordered_map<const Declaration*, llvm::Value *> llvmSymbolTable;
    const Block* rootBlock = nullptr;
//    std::unordered_map<const Declaration*, llvm::Function *> llvmFunctionTable;

    llvm::Value *visit(const Statement *);
    llvm::BasicBlock *visit(const Block *);
    llvm::Value *visit(const Expression *);
    llvm::Value *visit(const Identifier *);
    llvm::Value *visit(const ArithmeticExpression *);
    llvm::Value *visit(const BinaryOperator *);
    llvm::Value *visit(const UnaryOperator *);
    llvm::Value *visit(const TypeConvertOperator *);
    llvm::Value *visit(const ClassNewExpression *);
    llvm::Value *visit(const Entity *);
    llvm::Value *visit(const AssignExpression *);
//    llvm::Value *visit(const Declaration *);
    llvm::Value *visit(const VariableDeclaration *);
    llvm::Value *visit(const LambdaExpression *);
    llvm::Value *visit(const FunctionDeclaration *);
    llvm::Value *visit(const ClassDeclaration *);
    llvm::Value *visit(const InterfaceDeclaration *);
//    llvm::Value *visit(const LogicStatement *);
    llvm::Value *visit(const IfStatement *);
    llvm::Value *visit(const ForStatement *);
    llvm::Value *visit(const WhileStatement *);
    llvm::Value *visit(const ReturnStatement *);
    llvm::Value *visit(const IOStatement *);

    void dump(const std::string& outputFileName);
    void init(const std::string& inputFileName);

    void genMainFunctionContext();
    llvm::Function *genCFunction(const std::string &name,
                             llvm::Type *returnType, const std::vector<llvm::Type *> &args, bool varLen);
    void genFunctionContext(const std::string &name, llvm::Function *function);
    void endFunctionOrBlock();

    llvm::Type *getType(Type);
    std::string getFmtStr(llvm::Type *);
public:
    CodeGen();

    void genCode(const Block *root, const std::string& inputFileName, const std::string& outputFileName);
};


#endif //POSFOL_CODEGEN_H
