//
// Created by 游添予 on 2021/6/2.
//

#ifndef POSFOL_CODEGEN_H
#define POSFOL_CODEGEN_H

#include "../tree/node.h"
#include "../tree/type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include <string>
#include "symbol.h"

class CodeGen {
    llvm::LLVMContext llvmContext;
    llvm::Module module;
    llvm::IRBuilder<> irBuilder;

    void visit(Statement *);
    void visit(Block *);
//    void visit(Expression *);
    void visit(Identifier *);
    void visit(ArithmeticExpression *);
    void visit(BinaryOperator *);
    void visit(UnaryOperator *);
    void visit(TypeConvertOperator *);
    void visit(ClassNewExpression *);
    void visit(Entity *);
//    void visit(AssignExpression *);
//    void visit(Declaration *);
    void visit(VariableDeclaration *);
    void visit(LambdaExpression *);
    void visit(FunctionDeclaration *);
    void visit(ClassDeclaration *);
    void visit(InterfaceDeclaration *);
//    void visit(LogicStatement *);
    void visit(IfStatement *);
    void visit(ForStatement *);
    void visit(WhileStatement *);
    void visit(ReturnStatement *);
    void visit(IOStatement *);
    void visit(FuncCallExpression *);
    void visit(VariableAssign *);
    void visit(ArrayAssign *);
    void visit(ClassAssign *);
public:
    CodeGen();

    void genCode(const Block *root, std::string outputFileName);
};


#endif //POSFOL_CODEGEN_H
