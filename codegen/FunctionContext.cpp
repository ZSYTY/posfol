//
// Created by 游添予 on 2021/6/5.
//

#include "CodeGen.h"

void CodeGen::genMainFunctionContext() {
    std::vector<llvm::Type*> params;
    llvm::FunctionType *ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), params, false);
    llvm::Function *irMain = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, 0, "main", &module);
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(llvmContext, "main", irMain);
    irBuilder.SetInsertPoint(BB);
    symbolTable.pushAR();
    blockStack.push(BB);
}

llvm::Function *
CodeGen::genCFunction(const std::string &name, llvm::Type *returnType, const std::vector<llvm::Type *> &args,
                             bool varLen) {
    llvm::FunctionType *func_type = llvm::FunctionType::get(returnType, args, varLen);
    llvm::Function *func = llvm::Function::Create(func_type,
                                                  llvm::Function::ExternalLinkage, name, &module);
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

void CodeGen::genFunctionContext(const std::string &name, llvm::Function *function) {
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(llvmContext, name, function);
    irBuilder.SetInsertPoint(BB);
    symbolTable.pushAR();
    blockStack.push(BB);
}

void CodeGen::endFunctionOrBlock() {
    blockStack.pop();
    symbolTable.popAR();
    if (! blockStack.empty()) {
        irBuilder.SetInsertPoint(blockStack.top());
    }
}

