//
// Created by 游添予 on 2021/6/2.
//

#include "CodeGen.h"

void CodeGen::genCode(const Block *root, const std::string outputFileName) {
    visit(root);
}

CodeGen::CodeGen(): module("posfol", llvmContext), irBuilder(llvmContext) {

}

void CodeGen::visit(const Statement *stmt) {
    switch (stmt->getType()) {
        case BLOCK:
            visit(dynamic_cast<const Block *>(stmt));
            break;
        case IDENTIFIER:
            visit(dynamic_cast<const Identifier *>(stmt));
            break;
        case ARITHMETICEXPRESSION:
            visit(dynamic_cast<const ArithmeticExpression *>(stmt));
            break;
        case BINARYOPERATOR:
            visit(dynamic_cast<const BinaryOperator *>(stmt));
            break;
        case UNARYOPERATOR:
            visit(dynamic_cast<const UnaryOperator *>(stmt));
            break;
        case TYPECONVERTOPERATOR:
            visit(dynamic_cast<const TypeConvertOperator *>(stmt));
            break;
        case CLASSNEWEXPRESSION:
            visit(dynamic_cast<const ClassNewExpression *>(stmt));
            break;
        case ENTITYEXPRESSION:
            visit(dynamic_cast<const Entity *>(stmt));
            break;
        case VARIABLEDECLARATION:
            visit(dynamic_cast<const VariableDeclaration *>(stmt));
            break;
        case LAMBDADECLARATION:
            visit(dynamic_cast<const LambdaExpression *>(stmt));
            break;
        case FUNCTIONDECLARATION:
            visit(dynamic_cast<const FunctionDeclaration *>(stmt));
            break;
        case CLASSDECLARATION:
            visit(dynamic_cast<const ClassDeclaration *>(stmt));
            break;
        case INTERFACEDECLARATION:
            visit(dynamic_cast<const InterfaceDeclaration *>(stmt));
            break;
        case IFSTATEMENT:
            visit(dynamic_cast<const IfStatement *>(stmt));
            break;
        case FORSTATEMENT:
            visit(dynamic_cast<const ForStatement *>(stmt));
            break;
        case WHILESTATEMENT:
            visit(dynamic_cast<const WhileStatement *>(stmt));
            break;
        case RETURNSTATEMENT:
            visit(dynamic_cast<const ReturnStatement *>(stmt));
            break;
        case IOSTATEMENT:
            visit(dynamic_cast<const IOStatement *>(stmt));
            break;
        case NODE:
            break;
        case EXPRESSION:
            break;
        case CLASSEXPRESSION:
            break;
        case CLASSVARIABLEEXPRESSION:
            break;
        case CLASSFUNCEXPRESSION:
            break;
        case ASSIGNEXPRESSION:
            break;
        case DECLARATION:
            break;
        case STATEMENT:
            break;
        case LOGICSTATEMENT:
            break;
        case INT_DEFINE_TYPE:
            break;
        case LONG_DEFINE_TYPE:
            break;
        case FLOAT_DEFINE_TYPE:
            break;
        case DOUBLE_DEFINE_TYPE:
            break;
        case BOOLEAN_DEFINE_TYPE:
            break;
        case CHAR_DEFINE_TYPE:
            break;
        case FUNC_DEFINE_TYPE:
            break;
        case VOID_DEFINE_TYPE:
            break;
        case CLASS_DEFINE_TYPE:
            break;
        case ARRAY:
            break;
        case TYPE:
            break;
        case NAME:
            break;
        case VALUE:
            break;
        case ERROR:
            break;
    }
}

void CodeGen::visit(const Block *block) {
    for (auto stmt : *block->getStatementList()) {
        visit(stmt);
    }
}

void CodeGen::visit(const Identifier *) {

}

void CodeGen::visit(const ArithmeticExpression *) {

}

void CodeGen::visit(const BinaryOperator *) {

}

void CodeGen::visit(const UnaryOperator *) {

}

void CodeGen::visit(const TypeConvertOperator *) {

}

void CodeGen::visit(const ClassNewExpression *) {

}

void CodeGen::visit(const Entity *) {

}

void CodeGen::visit(const VariableDeclaration * variableDeclaration) {
    auto varType = variableDeclaration->getVarType()->getType();
    auto expression = variableDeclaration->getExpr();
    // TODO: calculate the expression
    auto expressionResult = 0;
    llvm::Constant *constant = nullptr;
    llvm::Value *value = nullptr;
    auto arraySizes = variableDeclaration->getArraySizes();
    if (arraySizes) {
        // TODO:
        /* Define an array */
    } else {
        switch (varType) {
            case INT_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext),
                                                  expression ? expressionResult : 0);
                value = irBuilder.CreateAlloca(llvm::Type::getInt32Ty(llvmContext));
                break;
            case LONG_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvmContext),
                                                  expression ? expressionResult : 0);
                value = irBuilder.CreateAlloca(llvm::Type::getInt64Ty(llvmContext));
                break;
            case FLOAT_DEFINE_TYPE:
                constant = llvm::ConstantFP::get(llvm::Type::getFloatTy(llvmContext),
                                                 expression ? expressionResult : 0);
                value = irBuilder.CreateAlloca(llvm::Type::getFloatTy(llvmContext));
                break;
            case DOUBLE_DEFINE_TYPE:
                constant = llvm::ConstantFP::get(llvm::Type::getDoubleTy(llvmContext),
                                                 expression ? expressionResult : 0);
                value = irBuilder.CreateAlloca(llvm::Type::getDoubleTy(llvmContext));
                break;
            case BOOLEAN_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvmContext),
                                                  expression ? expressionResult : 0);
                value = irBuilder.CreateAlloca(llvm::Type::getInt1Ty(llvmContext));
                break;
            case CHAR_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvmContext),
                                                  expression ? expressionResult : 0);
                value = irBuilder.CreateAlloca(llvm::Type::getInt8Ty(llvmContext));
                break;
            default:
                break;
        }
    }
    if (value) {
        value->setName(variableDeclaration->getVar()->getValue());
        if (constant) {
            irBuilder.CreateStore(constant, value);
        }
    }

}

void CodeGen::visit(const LambdaExpression *) {

}

void CodeGen::visit(const FunctionDeclaration *) {

}

void CodeGen::visit(const ClassDeclaration *) {

}

void CodeGen::visit(const InterfaceDeclaration *) {

}

void CodeGen::visit(const IfStatement *) {

}

void CodeGen::visit(const ForStatement *) {

}

void CodeGen::visit(const WhileStatement *) {

}

void CodeGen::visit(const ReturnStatement *) {

}

void CodeGen::visit(const IOStatement *) {

}
