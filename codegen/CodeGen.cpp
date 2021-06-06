//
// Created by 游添予 on 2021/6/2.
//

#include "CodeGen.h"

void CodeGen::init(const std::string& inputFileName) {

}

void CodeGen::dump(const std::string& outputFileName) {
    std::string output;
    llvm::raw_string_ostream out(output);
    this->module.print(llvm::outs(), nullptr);

    std::cout << output << std::endl;
    std::ofstream os(outputFileName);
    os << output << std::endl; // TODO: cannot output to file
//    module.dump();
}

void CodeGen::genCode(const Block *root, const std::string& inputFileName, const std::string& outputFileName) {
//    init(inputFileName);
    visit(root);
    if (! hasVisitedMainFunction) {
        genMainFunctionContext();
    }
    dump(outputFileName);
}

CodeGen::CodeGen(): module("posfol", llvmContext), irBuilder(llvmContext) {

}

llvm::Value *CodeGen::visit(const Statement *stmt) {
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
            visit(dynamic_cast<const Expression *>(stmt));
            break;
        case CLASSEXPRESSION:
            break;
        case CLASSVARIABLEEXPRESSION:
            break;
        case CLASSFUNCEXPRESSION:
            break;
        case ASSIGNEXPRESSION:
            visit(dynamic_cast<const AssignExpression *>(stmt));
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

llvm::Value *CodeGen::visit(const Block *block) {
    for (auto stmt : *block->getStatementList()) {
        visit(stmt);
    }
}

llvm::Value *CodeGen::visit(const Identifier *) {

}

llvm::Value *CodeGen::visit(const ArithmeticExpression *arithmeticExpression) {
    switch (arithmeticExpression->getType()) {
        case BINARYOPERATOR:
            return visit(dynamic_cast<const BinaryOperator *>(arithmeticExpression));
            break;
        case UNARYOPERATOR:
            return visit(dynamic_cast<const UnaryOperator *>(arithmeticExpression));
            break;
        case TYPECONVERTOPERATOR:
            return visit(dynamic_cast<const TypeConvertOperator *>(arithmeticExpression));
            break;
    }
}

llvm::Value *CodeGen::visit(const BinaryOperator *binaryOperator) {
    llvm::Value *lhs = visit(binaryOperator->getLhs());
    llvm::Value *rhs = visit(binaryOperator->getRhs());
    // std::string op_name[] = {"||", "&&", ">=", ">", "<=", "<", "==", "!=", "+", "-", "*", "/", "%"};
    bool isFP = lhs->getType()->isFloatTy() || rhs->getType()->isFloatTy();
    switch (binaryOperator->getOp()) {
        case 0: // ||
            return irBuilder.CreateOr(lhs, rhs, "orResult");
        case 1: // &&
            return irBuilder.CreateAnd(lhs, rhs, "andResult");
        case 2: // >=
            return isFP ? irBuilder.CreateFCmpOGE(lhs, rhs, "geqResult") : irBuilder.CreateICmpSGE(lhs, rhs, "geqResult");
        case 3: // >
            return isFP ? irBuilder.CreateFCmpOGT(lhs, rhs, "gtResult") : irBuilder.CreateICmpSGT(lhs, rhs, "gtResult");
        case 4: // <=
            return isFP ? irBuilder.CreateFCmpOLE(lhs, rhs, "leqResult") : irBuilder.CreateICmpSLE(lhs, rhs, "leqResult");
        case 5: // <
            return isFP ? irBuilder.CreateFCmpOLT(lhs, rhs, "leResult") : irBuilder.CreateICmpSLT(lhs, rhs, "leResult");
        case 6: // ==
            return irBuilder.CreateICmpEQ(lhs, rhs, "eqResult");
        case 7: // !=
            return irBuilder.CreateICmpNE(lhs, rhs, "neResult");
        case 8: // +
            return isFP ? irBuilder.CreateFAdd(lhs, rhs, "addResult") : irBuilder.CreateAdd(lhs, rhs, "addResult");
        case 9: // -
            return isFP ? irBuilder.CreateFSub(lhs, rhs, "subResult") : irBuilder.CreateSub(lhs, rhs, "subResult");
        case 10: // *
            return isFP ? irBuilder.CreateFMul(lhs, rhs, "mulResult") : irBuilder.CreateMul(lhs, rhs, "mulResult");
        case 11: // /
            return isFP ? irBuilder.CreateFDiv(lhs, rhs, "divResult") : irBuilder.CreateSDiv(lhs, rhs, "divResult");
        case 12: // %
            assert(! isFP);
            return irBuilder.CreateSRem(lhs, rhs, "modResult");
        default:
            return nullptr;
    }
}

llvm::Value *CodeGen::visit(const UnaryOperator *unaryOperator) {
    llvm::Value *hs = visit(unaryOperator->getHs());
    bool isFP = hs->getType()->isFloatTy();
    switch (unaryOperator->getType()) {
        case 0: // -
            return isFP ? irBuilder.CreateFNeg(hs, "negResult") : irBuilder.CreateNeg(hs, "negResult");
        case 1: // !
            return irBuilder.CreateNot(hs, "notResult");
        default:
            return nullptr;
    }
}

llvm::Value *CodeGen::visit(const TypeConvertOperator *typeConvertOperator) {
    llvm::Value *value = visit(typeConvertOperator->getExpr());
    // TODO: casting
}

llvm::Value *CodeGen::visit(const ClassNewExpression *) {

}

llvm::Value *CodeGen::visit(const Entity *) {

}

llvm::Value *CodeGen::visit(const VariableDeclaration * variableDeclaration) {
    auto varType = variableDeclaration->getVarType()->getType();
    auto expression = variableDeclaration->getExpr();
    // TODO: calculate the expression
    auto expressionResult = 0;
    llvm::Constant *constant = nullptr;
    llvm::Value *value = nullptr;
    auto arraySizes = variableDeclaration->getArraySizes();
    llvm::Value *arraySize = nullptr;
    auto type = getType(varType);
    if (arraySizes) {
        // TODO:
        /* Define an array */
    } else {
        switch (varType) {
            case INT_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(type,expression ? expressionResult : 0);
                break;
            case LONG_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(type,expression ? expressionResult : 0);
                break;
            case FLOAT_DEFINE_TYPE:
                constant = llvm::ConstantFP::get(type, expression ? expressionResult : 0);
                break;
            case DOUBLE_DEFINE_TYPE:
                constant = llvm::ConstantFP::get(type, expression ? expressionResult : 0);
                break;
            case BOOLEAN_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(type,expression ? expressionResult : 0);
                break;
            case CHAR_DEFINE_TYPE:
                constant = llvm::ConstantInt::get(type, expression ? expressionResult : 0);
                break;
            default:
                break;
        }
    }
    if (! type->isVoidTy()) {
        auto name = variableDeclaration->getVar()->getValue();
        if (symbolTable.isGlobal()) {
            // TODO: support global array variables
            value = new llvm::GlobalVariable(module, type, false,
                                     llvm::GlobalValue::CommonLinkage, constant, name);
        } else {
            value = irBuilder.CreateAlloca(type, arraySize, name);
            irBuilder.CreateStore(constant, value);
        }
        symbolTable.push(name, variableDeclaration);
    }
    return value;
}

llvm::Value *CodeGen::visit(const LambdaExpression *) {

}

llvm::Value *CodeGen::visit(const FunctionDeclaration *functionDeclaration) {
    std::string name = functionDeclaration->getFunc()->getValue();
    if (name == "main") {
        genMainFunctionContext();
        hasVisitedMainFunction = true;
    } else {
        std::vector<llvm::Type *> args;
        for (auto item : *functionDeclaration->getParamList()) {
            args.push_back(getType(item->getType()));
        }
        llvm::Function *function = genCFunction(name, getType(functionDeclaration->getReturnType()->getType()), args, false);
        genFunctionContext(name, function);
    }
    visit(functionDeclaration->getFuncBlock());
    endFunctionOrBlock();
}

llvm::Value *CodeGen::visit(const ClassDeclaration *) {

}

llvm::Value *CodeGen::visit(const InterfaceDeclaration *) {

}

llvm::Value *CodeGen::visit(const IfStatement *) {

}

llvm::Value *CodeGen::visit(const ForStatement *) {

}

llvm::Value *CodeGen::visit(const WhileStatement *) {

}

llvm::Value *CodeGen::visit(const ReturnStatement *) {

}

llvm::Value *CodeGen::visit(const IOStatement *ioStatement) {
    static llvm::Function *printfFunc = genCFunction("printf",
                                                      llvm::Type::getInt32Ty(llvmContext), { llvm::Type::getInt8PtrTy(llvmContext) }, true);
    static llvm::Function *scanfFunc = genCFunction("scanf",
                                                    llvm::Type::getInt32Ty(llvmContext), { llvm::Type::getInt8PtrTy(llvmContext) }, true);
    // TODO:
    if (ioStatement->getIsRead()) {

    } else {
        if (ioStatement->getExpr()) {

        } else {

        }
    }
}

llvm::Value *CodeGen::visit(const Expression * expression) {
    switch (expression->getType()) {
        case ARITHMETICEXPRESSION:
            return visit(dynamic_cast<const ArithmeticExpression *>(expression));
        case ASSIGNEXPRESSION:
            return visit(dynamic_cast<const AssignExpression *>(expression));
        case CLASSNEWEXPRESSION:
            break;
        case CLASSEXPRESSION:
            break;
        case CLASSVARIABLEEXPRESSION:
            break;
        case CLASSFUNCEXPRESSION:
            break;
        case ENTITYEXPRESSION:
            return visit(dynamic_cast<const Entity *>(expression));
        default:
            return nullptr;
    }
}

llvm::Value *CodeGen::visit(const AssignExpression *assignExpression) {
    llvm::Value *target = visit(assignExpression->getEntity());
    llvm::Value *source = visit(assignExpression->getExpr());
    irBuilder.CreateStore(source, target);
    return target;
}
