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
#include "../semantic/symbol.h"

class CodeGen {
    llvm::LLVMContext llvmContext;
    llvm::Module module;
    llvm::IRBuilder<> irBuilder;

    void visit(const Statement *);
    void visit(const Block *);
//    void visit(const Expression *);
    void visit(const Identifier *);
    void visit(const ArithmeticExpression *);
    void visit(const BinaryOperator *);
    void visit(const UnaryOperator *);
    void visit(const TypeConvertOperator *);
    void visit(const ClassNewExpression *);
    void visit(const Entity *);
//    void visit(const AssignExpression *);
//    void visit(const Declaration *);
    void visit(const VariableDeclaration *);
    void visit(const LambdaExpression *);
    void visit(const FunctionDeclaration *);
    void visit(const ClassDeclaration *);
    void visit(const InterfaceDeclaration *);
//    void visit(const LogicStatement *);
    void visit(const IfStatement *);
    void visit(const ForStatement *);
    void visit(const WhileStatement *);
    void visit(const ReturnStatement *);
    void visit(const IOStatement *);
    void visit(const FuncCallExpression *);
    void visit(const VariableAssign *);
    void visit(const ArrayAssign *);
    void visit(const ClassAssign *);
public:
    CodeGen();

    void genCode(const Block *root, std::string outputFileName);
};


#endif //POSFOL_CODEGEN_H
