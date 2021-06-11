//
// Created by 游添予 on 2021/6/2.
//

#include "CodeGen.h"

#define ISTYPE(value, id) (value->getType()->getTypeID() == id)

llvm::Value *CodeGen::deRef(llvm::Value *ptr) {
    return irBuilder.CreateLoad(ptr, "deref");
};

llvm::Value* CodeGen::CastToBoolean(llvm::LLVMContext& context, llvm::Value* condValue){
    if(ISTYPE(condValue, llvm::Type::IntegerTyID)){
        condValue = irBuilder.CreateIntCast(condValue, llvm::Type::getInt1Ty(context), true);
        return irBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true));
    }else if(ISTYPE(condValue, llvm::Type::DoubleTyID)){
        return irBuilder.CreateFCmpONE(condValue, llvm::ConstantFP::get(context, llvm::APFloat(0.0)));
    }else{
        return condValue;
    }
}


void CodeGen::init(const std::string& inputFileName) {

}

void CodeGen::dump(const std::string& outputFileName) {
    this->module.print(llvm::outs(), nullptr);
    std::error_code EC;
    llvm::raw_fd_ostream os(outputFileName, EC);
    this->module.print(os, nullptr);
}

void CodeGen::genCode(const Block *root, const std::string& inputFileName, const std::string& outputFileName) {
//    init(inputFileName);
    rootBlock = root;
    new llvm::GlobalVariable(module, llvm::Type::getInt1Ty(llvmContext), false,
                             llvm::GlobalValue::CommonLinkage, getInitValue(llvm::Type::getInt1Ty(llvmContext)), "_#_bool_sc");
    visit(root);
    if (! hasVisitedMainFunction) {
        genMainFunctionContext();
    }
    dump(outputFileName);
}

void CodeGen::genBinary(const Block *root, const std::string &inputFileName, const std::string &outputFileName) {
    genCode(root, inputFileName, "a.ll");
    system("llc a.ll");
    system(("gcc -o " + outputFileName + " -lm a.ll").c_str());
}

CodeGen::CodeGen(): module("posfol", llvmContext), irBuilder(llvmContext) {

}

llvm::Value *CodeGen::visit(const Statement *stmt) {
    switch (stmt->getType()) {
        case BLOCK:
            return visit(dynamic_cast<const Block *>(stmt));
            break;
        case IDENTIFIER:
            return visit(dynamic_cast<const Identifier *>(stmt));
            break;
        case ARITHMETICEXPRESSION:
            return visit(dynamic_cast<const ArithmeticExpression *>(stmt));
            break;
        case BINARYOPERATOR:
            return visit(dynamic_cast<const BinaryOperator *>(stmt));
            break;
        case UNARYOPERATOR:
            return visit(dynamic_cast<const UnaryOperator *>(stmt));
            break;
        case TYPECONVERTOPERATOR:
            return visit(dynamic_cast<const TypeConvertOperator *>(stmt));
            break;
        case CLASSNEWEXPRESSION:
            return visit(dynamic_cast<const ClassNewExpression *>(stmt));
            break;
        case ENTITYEXPRESSION:
            return visit(dynamic_cast<const Entity *>(stmt));
            break;
        case VARIABLEDECLARATION:
            return visit(dynamic_cast<const VariableDeclaration *>(stmt));
            break;
        case LAMBDADECLARATION:
            return visit(dynamic_cast<const LambdaExpression *>(stmt));
            break;
        case FUNCTIONDECLARATION:
            return visit(dynamic_cast<const FunctionDeclaration *>(stmt));
            break;
        case CLASSDECLARATION:
            return visit(dynamic_cast<const ClassDeclaration *>(stmt));
            break;
        case INTERFACEDECLARATION:
            return visit(dynamic_cast<const InterfaceDeclaration *>(stmt));
            break;
        case IFSTATEMENT:
            return visit(dynamic_cast<const IfStatement *>(stmt));
            break;
        case FORSTATEMENT:
            return visit(dynamic_cast<const ForStatement *>(stmt));
            break;
        case WHILESTATEMENT:
            return visit(dynamic_cast<const WhileStatement *>(stmt));
            break;
        case RETURNSTATEMENT:
            return visit(dynamic_cast<const ReturnStatement *>(stmt));
            break;
        case IOSTATEMENT:
            return visit(dynamic_cast<const IOStatement *>(stmt));
            break;
        case NODE:
            break;
        case EXPRESSION:
            return visit(dynamic_cast<const Expression *>(stmt));
            break;
        case CLASSEXPRESSION:
            break;
        case CLASSVARIABLEEXPRESSION:
            break;
        case CLASSFUNCEXPRESSION:
            break;
        case ASSIGNEXPRESSION:
            return visit(dynamic_cast<const AssignExpression *>(stmt));
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

llvm::BasicBlock *CodeGen::visit(const Block *block, bool shouldCreateNewBlock) {
    if (block == nullptr) {
        return nullptr;
    }
    llvm::BasicBlock *BB = nullptr;
    if (block != rootBlock) {
        symbolTable.pushAR();
    }
    if (! symbolTable.isGlobal() and shouldCreateNewBlock) {
        llvm::Function *function = irBuilder.GetInsertBlock()->getParent();
        BB = llvm::BasicBlock::Create(llvmContext, "", function);
        irBuilder.SetInsertPoint(BB);
    }
    for (auto stmt : *block->getStatementList()) {
        visit(stmt);
    }
//    if (BB) {
//        llvm::Function *function = irBuilder.GetInsertBlock()->getParent();
//        irBuilder.SetInsertPoint(llvm::BasicBlock::Create(llvmContext, "", function));
//    }
    if (block != rootBlock) {
        symbolTable.popAR();
    }
    return BB;
}

llvm::Value *CodeGen::visit(const Identifier *identifier, bool deref) {
    assert(! identifier->getIsType());
    if (identifier->getType() == NAME) {
        auto value = llvmSymbolTable[symbolTable.findSymbol(identifier->getValue())];
        if (deref) {
            return irBuilder.CreateLoad(value, "deref");
        } else {
            return value;
        }
    } else {
        return genConstant(identifier);
    }
}

llvm::Value *CodeGen::visit(const ArithmeticExpression *arithmeticExpression) {
    switch (arithmeticExpression->getType()) {
        case BINARYOPERATOR:
            return visit(dynamic_cast<const BinaryOperator *>(arithmeticExpression));
        case UNARYOPERATOR:
            return visit(dynamic_cast<const UnaryOperator *>(arithmeticExpression));
        case TYPECONVERTOPERATOR:
            return visit(dynamic_cast<const TypeConvertOperator *>(arithmeticExpression));
    }
}

llvm::Value *CodeGen::visit(const BinaryOperator *binaryOperator) {
    llvm::Value *lhs = visit(binaryOperator->getLhs(), true);
    llvm::Value *rhs = visit(binaryOperator->getRhs(), true);
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

llvm::Value *CodeGen::visit(const Entity *entity, bool deref) {

    if (entity->getIsTerminal()) {
        return visit(entity->getIdentifier(), deref);
    } else if (entity->getIsArrayIndex()) {
        // TODO:
        llvm::Value* array = visit(entity->getEntity());
        llvm::Value* indexExpr = visit(entity->getExpression());
        return irBuilder.CreateGEP(array, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), 0, true), indexExpr});
    } else if (entity->getIsFunctionCall()) {
        auto fn = visit(entity->getEntity());
//        auto deRef = [this](llvm::Value *ptr) {
//            return this->irBuilder.CreateLoad(ptr, "deref");
//        };
        std::vector<llvm::Value *> paramsVal;
        if (lambdaOuterArgsTable.find(reinterpret_cast<llvm::Function*>(fn)) != lambdaOuterArgsTable.end()) {
            auto pregs = lambdaOuterArgsTable[reinterpret_cast<llvm::Function*>(fn)];
            for (const auto &preg : *pregs) {
                paramsVal.emplace_back(deRef(preg));
            }
        }
        for (const auto &arg : *entity->getVectorExpression()) {
            auto expr = visit(arg);
            paramsVal.emplace_back(deRef(expr));
        }
        auto* func = reinterpret_cast<llvm::Function *>(fn);
        if (func->getReturnType()->isVoidTy()) {
            return irBuilder.CreateCall(func, paramsVal);
        } else {
            return irBuilder.CreateCall(func, paramsVal, "call_fn");
        }
    } else if (entity->getIsObjectCall()) {
        // TODO:
    }
}

llvm::Value *CodeGen::visit(const VariableDeclaration * variableDeclaration) {
    auto varType = variableDeclaration->getVarType()->getType();
    auto expression = variableDeclaration->getExpr();
    auto expressionResult = expression ? visit(expression) : nullptr;
    llvm::Value *value = nullptr;
    auto arraySizes = variableDeclaration->getArraySizes();
    llvm::Value *arraySize = nullptr;
    auto *sizeList = new std::vector<llvm::ConstantInt *>;
    if (arraySizes) {

        for (auto &item : *arraySizes) {
            sizeList->push_back(static_cast<llvm::ConstantInt *>(visit(item)));
        }

        arraySize = sizeList->front();
        for (int i = 1; i < sizeList->size(); i++) {
            arraySize = irBuilder.CreateMul(arraySize, (*sizeList)[i]);
        }
    }

    auto type = getType(varType, arraySizes ? sizeList : nullptr);

    if (varType == FUNC_DEFINE_TYPE) {
        auto name = variableDeclaration->getVar()->getValue();
        value = expressionResult;
        symbolTable.push(name, variableDeclaration);
        llvmSymbolTable[variableDeclaration] = value;
    } else if (! type->isVoidTy()) {
        auto name = variableDeclaration->getVar()->getValue();
        if (symbolTable.isGlobal()) {
            llvm::Constant *initValue = nullptr;
            if (expressionResult) {
                if (expressionResult->getType()->isPointerTy()) {
                    initValue = static_cast<llvm::Constant *>(deRef(expressionResult));
                } else {
                    initValue = static_cast<llvm::Constant *>(expressionResult);
                }
            } else {
                initValue = getInitValue(type);
            }
            value = new llvm::GlobalVariable(module, type, false,
                                     llvm::GlobalValue::CommonLinkage, initValue, name);
        } else {
            value = irBuilder.CreateAlloca(type, arraySize, name);
            if (expressionResult) {
                if (expressionResult->getType()->isPointerTy()) {
                    expressionResult = deRef(expressionResult);
                }
                irBuilder.CreateStore(expressionResult, value);
            }
        }
        symbolTable.push(name, variableDeclaration);
        llvmSymbolTable[variableDeclaration] = value;
    }
    return value;
}

llvm::Value *CodeGen::visit(const LambdaExpression *lambdaExpression) {
    std::vector<llvm::Type *> args;
    auto outerArgs = new std::vector<llvm::Value *>();
    auto* outerArgsDecl = new std::vector<VariableDeclaration*>();
    for (auto item : *lambdaExpression->getOuterVars()) {
        auto outerArg = visit(item);
        outerArgs->push_back(outerArg);
        VariableDeclaration* outerArgDecl = (VariableDeclaration *) symbolTable.findSymbol(item->getValue());
        outerArgsDecl->push_back(reinterpret_cast<VariableDeclaration *const>(outerArgDecl));
        args.push_back(getType(outerArgDecl->getVarType()->getType()));
    }
    for (auto item : *lambdaExpression->getParamList()) {
        args.push_back(getType(item->getVarType()->getType()));
    }

    llvm::Function *function = genCFunction("lambda", getType(lambdaExpression->getReturnType()->getType()), args, false);
    genFunctionContext("lambda", function);

    int idx = 0;
    for (auto &argItem : function->args()) {

        auto varDeclaration = idx < outerArgsDecl->size()
                ? outerArgsDecl->at(idx++)
                : lambdaExpression->getParamList()->at(idx++ - outerArgsDecl->size());
        argItem.setName(varDeclaration->getVar()->getValue());
        irBuilder.CreateStore(&argItem, visit(varDeclaration));
    }
    lambdaOuterArgsTable[function] = outerArgs;
    visit(lambdaExpression->getFuncBlock());
    endFunctionOrBlock();

    return function;
}

llvm::Value *CodeGen::visit(const FunctionDeclaration *functionDeclaration) {
    std::string name = functionDeclaration->getFunc()->getValue();
    llvm::Function *function = nullptr;
    if (name == "main") {
        genMainFunctionContext();
        hasVisitedMainFunction = true;
    } else {
        std::vector<llvm::Type *> args;
        for (auto item : *functionDeclaration->getParamList()) {
            args.push_back(getType(item->getVarType()->getType()));
        }
        function = genCFunction(name, getType(functionDeclaration->getReturnType()->getType()), args, false);
        genFunctionContext(name, function);
        llvmSymbolTable[functionDeclaration] = function;
        int idx = 0;
        for (auto &argItem : function->args()) {
            auto varDeclaration = functionDeclaration->getParamList()->at(idx++);
            argItem.setName(varDeclaration->getVar()->getValue());
            irBuilder.CreateStore(&argItem, visit(varDeclaration));
        }
    }
    visit(functionDeclaration->getFuncBlock());
    endFunctionOrBlock();
    symbolTable.push(name, functionDeclaration);
    return function;
}

llvm::Value *CodeGen::visit(const ClassDeclaration *) {

}

llvm::Value *CodeGen::visit(const InterfaceDeclaration *) {

}

llvm::Value *CodeGen::visit(const IfStatement *ifStatement) {
    llvm::Function* theFunction = irBuilder.GetInsertBlock()->getParent();
    llvm::Value* condValue = visit(ifStatement->getCondition());
    llvm::BasicBlock* beforeBlock = irBuilder.GetInsertBlock();
    llvm::BasicBlock* trueBlock = visit(ifStatement->getTrueBlock(), true);
    llvm::BasicBlock* falseBlock = visit(ifStatement->getFalseBlock(), true);
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(llvmContext, "after", theFunction);
    if (falseBlock) {
        irBuilder.SetInsertPoint(beforeBlock);
        irBuilder.CreateCondBr(CastToBoolean(llvmContext, condValue), trueBlock, falseBlock);
        irBuilder.SetInsertPoint(trueBlock);
        irBuilder.CreateBr(afterBlock);
        irBuilder.SetInsertPoint(falseBlock);
        irBuilder.CreateBr(afterBlock);
        irBuilder.SetInsertPoint(afterBlock);
//        irBuilder.SetInsertPoint();
    } else {
        irBuilder.SetInsertPoint(beforeBlock);
        irBuilder.CreateCondBr(CastToBoolean(llvmContext, condValue), trueBlock, afterBlock);
        irBuilder.SetInsertPoint(trueBlock);
        irBuilder.CreateBr(afterBlock);
        irBuilder.SetInsertPoint(afterBlock);
    }
}

llvm::Value *CodeGen::visit(const ForStatement * forStatement) {
    llvm::Function* theFunction = irBuilder.GetInsertBlock()->getParent();
    llvm::BasicBlock* block = llvm::BasicBlock::Create(llvmContext, "forloop", theFunction);
    llvm::BasicBlock* after = llvm::BasicBlock::Create(llvmContext, "forcont");

    // 执行初始化语句
    if(forStatement->getInitial()) {
        visit(forStatement->getInitial());
    }

    // 获取条件语句
    llvm::Value* condValue = visit(forStatement->getCondition());
    if(!condValue) {
        return nullptr;
    }
    // 转化为boolean
    condValue = CastToBoolean(llvmContext, condValue);
    // 创建跳转指令
    irBuilder.CreateCondBr(condValue, block, after);
    //设置插入点，之后的插入就都在这个block块里面
    irBuilder.SetInsertPoint(block);
    // 进入新的block作用域，栈pushAR
    symbolTable.pushAR();
    // 执行block里的函数体
    visit(forStatement->getForBlock());
    // 函数体执行完毕，栈popAR
    symbolTable.popAR();
    // 做change语句
    if(forStatement->getChange()) {
        visit(forStatement->getChange());
    }
    // 再次执行for条件语句，如果不满足则跳出循环
    condValue = visit(forStatement->getCondition());
    condValue = CastToBoolean(llvmContext, condValue);
    irBuilder.CreateCondBr(condValue, block, after);

    // 插入after block
    theFunction->getBasicBlockList().push_back(after);
    irBuilder.SetInsertPoint(after);

    return nullptr;
}

llvm::Value *CodeGen::visit(const WhileStatement *whileStatement) {
    llvm::Function* theFunction = irBuilder.GetInsertBlock()->getParent();
    llvm::BasicBlock* block = llvm::BasicBlock::Create(llvmContext, "whileloop", theFunction);
    llvm::BasicBlock* after = llvm::BasicBlock::Create(llvmContext, "whilecont");

    llvm::Value* condValue = visit(whileStatement->getCondition());
    if(!condValue) {
        return nullptr;
    }
    condValue = CastToBoolean(llvmContext, condValue);
    irBuilder.CreateCondBr(condValue, block, after);
    irBuilder.SetInsertPoint(block);
    symbolTable.pushAR();
    visit(whileStatement->getWhileBlock());
    symbolTable.popAR();
    condValue = visit(whileStatement->getCondition());
    condValue = CastToBoolean(llvmContext, condValue);
    irBuilder.CreateCondBr(condValue, block, after);
    theFunction->getBasicBlockList().push_back(after);
    irBuilder.SetInsertPoint(after);

    return nullptr;
}

llvm::Value *CodeGen::visit(const ReturnStatement *returnStatement) {
    if (returnStatement->getReturnExpr()) {
        llvm::Value *returnValue = visit(returnStatement->getReturnExpr());
        return irBuilder.CreateRet(returnValue);
    } else {
        return irBuilder.CreateRetVoid();
    }
}

llvm::Value *CodeGen::visit(const IOStatement *ioStatement) {
    static llvm::Function *printfFunc = genCFunction("printf",
                                                      llvm::Type::getInt32Ty(llvmContext), { llvm::Type::getInt8PtrTy(llvmContext) }, true);
    static llvm::Function *scanfFunc = genCFunction("scanf",
                                                    llvm::Type::getInt32Ty(llvmContext), { llvm::Type::getInt8PtrTy(llvmContext) }, true);
    std::vector<llvm::Value *> args;
    args.push_back(irBuilder.CreateGlobalStringPtr(ioStatement->getPrintText(), "formatString", 0, &module));

    if (ioStatement->getVectorExpression()) {
        for (auto item : *ioStatement->getVectorExpression()) {
            llvm::Value *arg = visit(item);
            auto zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), 0, true);
            if (arg->getType()->isPointerTy()) {
                auto value = deRef(arg);
                if (value->getType()->isArrayTy()) {
                    arg = irBuilder.CreateGEP(arg, {zero, zero});
                } else {
                    if (!ioStatement->getIsRead()) {
                        arg = value;
                    }
                }
            }
            args.push_back(arg);
        }
    }

    if (ioStatement->getIsRead()) {
        irBuilder.CreateCall(scanfFunc, args);
    } else {
        irBuilder.CreateCall(printfFunc, args);
    }
}

llvm::Value *CodeGen::visit(const Expression * expression, bool deref) {
    switch (expression->getType()) {
        case ARITHMETICEXPRESSION: case BINARYOPERATOR: case UNARYOPERATOR: case TYPECONVERTOPERATOR:
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
            return visit(dynamic_cast<const Entity *>(expression), deref);
        case INT_VALUE: case LONG_VALUE: case FLOAT_VALUE: case DOUBLE_VALUE: case CHAR_VALUE: case BOOLEAN_VALUE:
            return visit(dynamic_cast<const Identifier *>(expression), true);
        case LAMBDADECLARATION:
            return visit(dynamic_cast<const LambdaExpression *>(expression));
        default:
            return nullptr;
    }
}

llvm::Value *CodeGen::visit(const AssignExpression *assignExpression) {
    llvm::Value *target = visit(assignExpression->getEntity());
    llvm::Value *source = visit(assignExpression->getExpr());
    if (source->getType()->isPointerTy()) {
        source = deRef(source);
    }
    irBuilder.CreateStore(source, target);
    return target;
}
