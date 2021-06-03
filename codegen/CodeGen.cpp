//
// Created by 游添予 on 2021/6/2.
//

#include "CodeGen.h"

void CodeGen::genCode(const Block *root, const std::string outputFileName) {

}

CodeGen::CodeGen(): module("posfol", llvmContext), irBuilder(llvmContext) {

}

void CodeGen::visit(Statement *stmt) {
    switch (stmt->getType()) {
        case BLOCK:
            visit(dynamic_cast<Block *>(stmt));
            break;
        case IDENTIFIER:
            visit(dynamic_cast<Identifier *>(stmt));
            break;
        case ARITHMETICEXPRESSION:
            visit(dynamic_cast<ArithmeticExpression *>(stmt));
            break;
        case BINARYOPERATOR:
            visit(dynamic_cast<BinaryOperator *>(stmt));
            break;
        case UNARYOPERATOR:
            visit(dynamic_cast<UnaryOperator *>(stmt));
            break;
        case TYPECONVERTOPERATOR:
            visit(dynamic_cast<TypeConvertOperator *>(stmt));
            break;
        case CLASSNEWEXPRESSION:
            visit(dynamic_cast<ClassNewExpression *>(stmt));
            break;
        case ENTITYEXPRESSION:
            visit(dynamic_cast<Entity *>(stmt));
            break;
        case VARIABLEDECLARATION:
            visit(dynamic_cast<VariableDeclaration *>(stmt));
            break;
        case LAMBDADECLARATION:
            visit(dynamic_cast<LambdaExpression *>(stmt));
            break;
        case FUNCTIONDECLARATION:
            visit(dynamic_cast<FunctionDeclaration *>(stmt));
            break;
        case CLASSDECLARATION:
            visit(dynamic_cast<ClassDeclaration *>(stmt));
            break;
        case INTERFACEDECLARATION:
            visit(dynamic_cast<InterfaceDeclaration *>(stmt));
            break;
        case IFSTATEMENT:
            visit(dynamic_cast<IfStatement *>(stmt));
            break;
        case FORSTATEMENT:
            visit(dynamic_cast<ForStatement *>(stmt));
            break;
        case WHILESTATEMENT:
            visit(dynamic_cast<WhileStatement *>(stmt));
            break;
        case RETURNSTATEMENT:
            visit(dynamic_cast<ReturnStatement *>(stmt));
            break;
        case IOSTATEMENT:
            visit(dynamic_cast<IOStatement *>(stmt));
            break;
        case FUNCCALLEXPRESSION:
            visit(dynamic_cast<FuncCallExpression *>(stmt));
            break;
        case VARIABLEASSIGN:
            visit(dynamic_cast<VariableAssign* >(stmt));
            break;
        case ARRAYASSIGN:
            visit(dynamic_cast<ArrayAssign *>(stmt));
            break;
        case CLASSASSIGN:
            visit(dynamic_cast<ClassAssign *>(stmt));
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

void CodeGen::visit(Block *block) {
    for (auto stmt : *block->getStatementList()) {
        visit(stmt);
    }
}

void CodeGen::visit(Identifier *) {

}

void CodeGen::visit(ArithmeticExpression *) {

}

void CodeGen::visit(BinaryOperator *) {

}

void CodeGen::visit(UnaryOperator *) {

}

void CodeGen::visit(TypeConvertOperator *) {

}

void CodeGen::visit(ClassNewExpression *) {

}

void CodeGen::visit(Entity *) {

}

void CodeGen::visit(VariableDeclaration * variableDeclaration) {

}

void CodeGen::visit(LambdaExpression *) {

}

void CodeGen::visit(FunctionDeclaration *) {

}

void CodeGen::visit(ClassDeclaration *) {

}

void CodeGen::visit(InterfaceDeclaration *) {

}

void CodeGen::visit(IfStatement *) {

}

void CodeGen::visit(ForStatement *) {

}

void CodeGen::visit(WhileStatement *) {

}

void CodeGen::visit(ReturnStatement *) {

}

void CodeGen::visit(IOStatement *) {

}

void CodeGen::visit(FuncCallExpression *) {

}

void CodeGen::visit(VariableAssign *) {

}

void CodeGen::visit(ArrayAssign *) {

}

void CodeGen::visit(ClassAssign *) {

}
