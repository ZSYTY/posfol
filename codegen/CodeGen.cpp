//
// Created by 游添予 on 2021/6/2.
//

#include "CodeGen.h"

#define ISTYPE(value, id) (value->getType()->getTypeID() == id)

llvm::Value *CodeGen::deRef(llvm::Value *ptr) {
    if (ptr->getType()->isPointerTy()) {
        return irBuilder.CreateLoad(ptr, "deref");
    } else {
        return ptr;
    }
};

llvm::Value* CodeGen::CastToBoolean(llvm::LLVMContext& context, llvm::Value* condValue){
    if(ISTYPE(condValue, llvm::Type::IntegerTyID)){
        condValue = irBuilder.CreateIntCast(condValue, llvm::Type::getInt1Ty(context), true, "intCast");
        return irBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true), "intCmp");
    }else if(ISTYPE(condValue, llvm::Type::DoubleTyID)){
        return irBuilder.CreateFCmpONE(condValue, llvm::ConstantFP::get(context, llvm::APFloat(0.0)), "floatCmp");
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
        case IDENTIFIER:
            return visit(dynamic_cast<const Identifier *>(stmt)).value;
        case ARITHMETICEXPRESSION:
            return visit(dynamic_cast<const ArithmeticExpression *>(stmt));
        case BINARYOPERATOR:
            return visit(dynamic_cast<const BinaryOperator *>(stmt));
        case UNARYOPERATOR:
            return visit(dynamic_cast<const UnaryOperator *>(stmt));
        case TYPECONVERTOPERATOR:
            return visit(dynamic_cast<const TypeConvertOperator *>(stmt));
        case CLASSNEWEXPRESSION:
            return visit(dynamic_cast<const ClassNewExpression *>(stmt));
        case ENTITYEXPRESSION:
            return visit(dynamic_cast<const Entity *>(stmt)).value;
        case VARIABLEDECLARATION:
            return visit(dynamic_cast<const VariableDeclaration *>(stmt));
        case LAMBDADECLARATION:
            return visit(dynamic_cast<const LambdaExpression *>(stmt));
        case FUNCTIONDECLARATION:
            return visit(dynamic_cast<const FunctionDeclaration *>(stmt));
        case CLASSDECLARATION:
            return visit(dynamic_cast<const ClassDeclaration *>(stmt));
        case INTERFACEDECLARATION:
            return visit(dynamic_cast<const InterfaceDeclaration *>(stmt));
        case IFSTATEMENT:
            return visit(dynamic_cast<const IfStatement *>(stmt));
        case FORSTATEMENT:
            return visit(dynamic_cast<const ForStatement *>(stmt));
        case WHILESTATEMENT:
            return visit(dynamic_cast<const WhileStatement *>(stmt));
        case RETURNSTATEMENT:
            return visit(dynamic_cast<const ReturnStatement *>(stmt));
        case IOSTATEMENT:
            return visit(dynamic_cast<const IOStatement *>(stmt));
        case BREAKSTATEMENT:
            return visit(dynamic_cast<const BreakStatement *>(stmt));
        case CONTINUESTATEMENT:
            return visit(dynamic_cast<const ContinueStatement *>(stmt));
        case EXPRESSION:
            return visit(dynamic_cast<const Expression *>(stmt));
        case ASSIGNEXPRESSION:
            return visit(dynamic_cast<const AssignExpression *>(stmt));
        case NODE:
        case CLASSEXPRESSION:
        case CLASSVARIABLEEXPRESSION:
        case CLASSFUNCEXPRESSION:
        case DECLARATION:
        case STATEMENT:
        case LOGICSTATEMENT:
        case INT_DEFINE_TYPE:
        case LONG_DEFINE_TYPE:
        case FLOAT_DEFINE_TYPE:
        case DOUBLE_DEFINE_TYPE:
        case BOOLEAN_DEFINE_TYPE:
        case CHAR_DEFINE_TYPE:
        case FUNC_DEFINE_TYPE:
        case VOID_DEFINE_TYPE:
        case CLASS_DEFINE_TYPE:
        case ARRAY:
        case TYPE:
        case NAME:
        case VALUE:
        case ERROR:
            return nullptr;
    }
}

llvm::BasicBlock *CodeGen::visit(const Block *block, bool shouldCreateNewBlock, std::string blockName) {
    if (block == nullptr) {
        return nullptr;
    }
    llvm::BasicBlock *BB = nullptr;
    if (block != rootBlock) {
        symbolTable.pushAR();
    }
    if (! symbolTable.isGlobal() and shouldCreateNewBlock) {
        llvm::Function *function = irBuilder.GetInsertBlock()->getParent();
        BB = llvm::BasicBlock::Create(llvmContext, blockName, function);
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

ExValue CodeGen::visit(const Identifier *identifier, bool deref) {
    assert(! identifier->getIsType());
    if (identifier->getType() == NAME) {
        auto value = llvmSymbolTable[symbolTable.findSymbol(identifier->getValue())];
        auto variableDeclaration = dynamic_cast<const VariableDeclaration*>(symbolTable.findSymbol(identifier->getValue()));
        auto functionDeclaration = dynamic_cast<const FunctionDeclaration*>(symbolTable.findSymbol(identifier->getValue()));
        Type type = variableDeclaration ? variableDeclaration->getVarType()->getType() :
                functionDeclaration ? functionDeclaration->getReturnType()->getType() : NAME;
        std::string className = variableDeclaration ? variableDeclaration->getVarType()->getValue() :
                                functionDeclaration ? functionDeclaration->getReturnType()->getValue() : "";
        if (deref) {
            return ExValue(irBuilder.CreateLoad(value, "deref"), type, className);
        } else {
            return ExValue(value, type, className);
        }
    } else {
        return ExValue(genConstant(identifier), NAME, "");
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
    llvm::Value *hs = visit(unaryOperator->getHs(), true);
    bool isFP = hs->getType()->isFloatTy();
    switch (unaryOperator->getOp()) {
        case 0: // -
            return isFP ? irBuilder.CreateFNeg(hs, "negResult") : irBuilder.CreateNeg(hs, "negResult");
        case 1: // !
            return irBuilder.CreateNot(hs, "notResult");
        default:
            return nullptr;
    }
}

llvm::Value *CodeGen::visit(const TypeConvertOperator *typeConvertOperator) {
    llvm::Value *value = deRef(visit(typeConvertOperator->getExpr()));
    // TODO: casting
    auto targetType = typeConvertOperator->getOp()->getType();
    if (targetType == INT_DEFINE_TYPE) {
        return irBuilder.CreateSExt(value, getType(targetType), "charToInt");
    } else if (targetType == FLOAT_DEFINE_TYPE) {
        return irBuilder.CreateSIToFP(value, getType(targetType), "intToFloat");
    }
    // TODO:
    return value;
}

llvm::Value *CodeGen::visit(const ClassNewExpression *classNewExpression) {
    return visit(new Entity(new Entity(new Identifier(NAME, classNewExpression->getClassName()->getValue() + "constructor")), classNewExpression->getParamExprList())).value;
}

ExValue CodeGen::visit(const Entity *entity, bool deref) {

    if (entity->getIsTerminal()) {
        return visit(entity->getIdentifier(), deref);
    } else if (entity->getIsArrayIndex()) {
        // TODO:
        ExValue visitValue = visit(entity->getEntity());
        llvm::Value* array = visitValue.value;
        llvm::Value* indexExpr = visit(entity->getExpression(), true);
        llvm::Value* result = irBuilder.CreateGEP(array, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), 0, true), indexExpr}, "arrayIndex");
        if (deref and result->getType()->isPointerTy()) {
            result = deRef(result);
        }
        return ExValue(result, visitValue.type, visitValue.className);
    } else if (entity->getIsFunctionCall()) {
        ExValue visitValue = visit(entity->getEntity());
        auto fn = visitValue.value;
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
        if (visitValue.objValue != nullptr) {
            paramsVal.emplace_back(deRef(visitValue.objValue));
        }
        auto* func = reinterpret_cast<llvm::Function *>(fn);
        if (func->getReturnType()->isVoidTy()) {
            return ExValue(irBuilder.CreateCall(func, paramsVal), visitValue.type, visitValue.className);
        } else {
            llvm::Value *returnValue = irBuilder.CreateCall(func, paramsVal, "call_fn");
            if (deref and returnValue->getType()->isPointerTy()) {
                returnValue = deRef(returnValue);
            }
            return ExValue(returnValue, visitValue.type, visitValue.className);;
        }
    } else if (entity->getIsObjectCall()) {
        // TODO:
        ExValue visitValue = visit(entity->getEntity());
        llvm::Value* obj = visitValue.value;
        ClassDeclaration* classDeclaration = (ClassDeclaration *) symbolTable.findSymbol(visitValue.className);
        if (classMemberTable[classDeclaration].find(entity->getIdentifier()->getValue()) != classMemberTable[classDeclaration].end()) {
            int bias = getNameIdInClass(classDeclaration, entity->getIdentifier()->getValue());
            auto memberDecl = classMemberTable[classDeclaration][entity->getIdentifier()->getValue()];
            return ExValue(irBuilder.CreateGEP(obj,
                                               {llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), 0, true),
                                                llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvmContext), bias,
                                                                       true)}),
                           memberDecl.first, memberDecl.second);
        } else {
            ExValue func = visit(new Identifier(NAME, entity->getIdentifier()->getValue() + "_of_" + classDeclaration->getClass()->getValue()));
            return ExValue(func.value, func.type, func.className, obj);
        }
    }
}

llvm::Value *CodeGen::visit(const VariableDeclaration * variableDeclaration) {
    auto varType = variableDeclaration->getVarType()->getType();
    auto expression = variableDeclaration->getExpr();
    auto expressionResult = expression ? visit(expression) : nullptr;
    llvm::Value *value = nullptr;
    auto arraySizes = variableDeclaration->getArraySizes();
    llvm::Value *arraySize = nullptr;
    auto *sizeList = getSizeList(arraySizes);

    if (arraySizes) {
        arraySize = sizeList->front();
        for (int i = 1; i < sizeList->size(); i++) {
            arraySize = irBuilder.CreateMul(arraySize, (*sizeList)[i]);
        }
    }

    auto type = getType(varType, variableDeclaration->getVarType()->getValue(), arraySizes ? sizeList : nullptr);

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
    delete sizeList;
    return value;
}

llvm::Value *CodeGen::visit(const LambdaExpression *lambdaExpression) {
    std::vector<llvm::Type *> args;
    auto outerArgs = new std::vector<llvm::Value *>();
    auto* outerArgsDecl = new std::vector<VariableDeclaration*>();
    for (auto item : *lambdaExpression->getOuterVars()) {
        auto outerArg = visit(item);
        outerArgs->push_back(outerArg.value);
        VariableDeclaration* outerArgDecl = (VariableDeclaration *) symbolTable.findSymbol(item->getValue());
        outerArgsDecl->push_back(reinterpret_cast<VariableDeclaration *const>(outerArgDecl));
        args.push_back(getType(outerArgDecl->getVarType()->getType(), outerArgDecl->getVarType()->getValue()));
    }
    for (auto item : *lambdaExpression->getParamList()) {
        args.push_back(getType(item->getVarType()->getType(), item->getVarType()->getValue()));
    }

    llvm::Function *function = genCFunction("lambda", getType(lambdaExpression->getReturnType()->getType(), lambdaExpression->getReturnType()->getValue()), args, false);
    genFunctionContext("lambda", function);

    int idx = 0;
    for (auto &argItem : function->args()) {
        VariableDeclaration *variableDeclaration = nullptr;
        if (idx < outerArgsDecl->size()) {
            auto originalDeclaration = outerArgsDecl->at(idx++);
            variableDeclaration = new VariableDeclaration(originalDeclaration->getVarType(), originalDeclaration->getVar());
        } else {
            variableDeclaration = lambdaExpression->getParamList()->at(idx++ - outerArgsDecl->size());
        }
        argItem.setName(variableDeclaration->getVar()->getValue());
        irBuilder.CreateStore(&argItem, visit(variableDeclaration));
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
            if (item->getArraySizes()) {
                args.push_back(getType(item->getVarType()->getType(), item->getVarType()->getValue(), getSizeList(item->getArraySizes())));
            } else {
                args.push_back(getType(item->getVarType()->getType(), item->getVarType()->getValue()));
            }
        }
        function = genCFunction(name, getType(functionDeclaration->getReturnType()->getType(), functionDeclaration->getReturnType()->getValue()), args, false);
        genFunctionContext(name, function);
        llvmSymbolTable[functionDeclaration] = function;
        int idx = 0;
        for (auto &argItem : function->args()) {
            auto varDeclaration = functionDeclaration->getParamList()->at(idx++);
            argItem.setName(varDeclaration->getVar()->getValue());
            irBuilder.CreateStore(&argItem, visit(varDeclaration));
        }
    }
    symbolTable.push(name, functionDeclaration);
    visit(functionDeclaration->getFuncBlock());
    endFunctionOrBlock();
    symbolTable.push(name, functionDeclaration);
    return function;
}

llvm::Value *CodeGen::visit(const ClassDeclaration *classDeclaration) {
    std::vector<llvm::Type *> vec;
    classMemberTable[classDeclaration] = std::unordered_map<std::string, std::pair<Type, std::string>>();
    for (const auto &stmt : *classDeclaration->getClassBlock()->getStatementList()) {
        if (dynamic_cast<const VariableDeclaration*>(stmt) != nullptr) {
            auto varDecl = reinterpret_cast<const VariableDeclaration*>(stmt);
            auto arraySizes = varDecl->getArraySizes();
            llvm::Value *arraySize = nullptr;
            auto *sizeList = getSizeList(arraySizes);
            if (arraySizes) {
                arraySize = sizeList->front();
                for (int i = 1; i < sizeList->size(); i++) {
                    arraySize = irBuilder.CreateMul(arraySize, (*sizeList)[i]);
                }
            }
            classMemberTable[classDeclaration][varDecl->getVar()->getValue()] = make_pair(varDecl->getVarType()->getType(), varDecl->getVarType()->getValue());
            vec.emplace_back(getType(varDecl->getVarType()->getType(), varDecl->getVarType()->getValue(), arraySizes ? sizeList : nullptr, nullptr));
        }
    }
    auto type = llvm::StructType::get(llvmContext, vec);
    symbolTable.push(classDeclaration->getClass()->getValue(), classDeclaration);
    llvmTypeTable[classDeclaration] = type;
    std::unordered_map<std::string, std::vector<Identifier*>> methods;
    for (const auto &stmt : *classDeclaration->getClassBlock()->getStatementList()) {
        if (dynamic_cast<const FunctionDeclaration*>(stmt) != nullptr) {
            auto funcDecl = reinterpret_cast<const FunctionDeclaration*>(stmt);
            if (funcDecl->getReturnType()->getType() == NAME) {
                auto beg = funcDecl->getFuncBlock()->getStatementList()->begin();
                funcDecl->getFuncBlock()->getStatementList()->insert(beg,
                        new VariableDeclaration(new Identifier(CLASS_DEFINE_TYPE, funcDecl->getFunc()->getValue()),
                                                new Identifier(NAME, "self")));
                funcDecl->getFuncBlock()->getStatementList()->push_back(
                        new ReturnStatement(new Entity(new Identifier(NAME, "self"))));
                visit(new FunctionDeclaration(
                        new Identifier(CLASS_DEFINE_TYPE, funcDecl->getReturnType()->getValue()),
                        new Identifier(NAME, funcDecl->getFunc()->getValue() + "constructor"),
                        funcDecl->getParamList(), funcDecl->getFuncBlock()));
            } else {
                funcDecl->getParamList()->push_back(new VariableDeclaration(new Identifier(CLASS_DEFINE_TYPE, classDeclaration->getClass()->getValue()),
                                                                                             new Identifier(NAME, "self")));
                visit(new FunctionDeclaration(
                        funcDecl->getReturnType(),
                        new Identifier(NAME, funcDecl->getFunc()->getValue() + "_of_" + classDeclaration->getClass()->getValue()),
                        funcDecl->getParamList(), funcDecl->getFuncBlock()));
                methods[funcDecl->getFunc()->getValue()] = std::vector<Identifier*>();
                methods[funcDecl->getFunc()->getValue()].push_back(funcDecl->getReturnType());
                for (const auto &type : *funcDecl->getParamList()) {
                    methods[funcDecl->getFunc()->getValue()].push_back(
                            reinterpret_cast<Identifier *const>(type));
                }
            }
        }
    }
    if (classDeclaration->getInterface() != nullptr) {
        std::unordered_map<std::string, std::vector<Identifier*>> interfaceMethods = interfaceMethodTable[symbolTable.findSymbol(classDeclaration->getInterface()->getValue())];
        for (const auto &[name, vec] : interfaceMethods) {
            if (methods.find(name) == methods.end()) {
                std::cerr << "Class " << classDeclaration->getClass()->getValue() << " does not implement the method " << name << " in interface " << classDeclaration->getInterface()->getValue() << std::endl;
                exit(2);
            }
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i]->getType() == CLASS_DEFINE_TYPE) {
                    if (methods[name][i]->getType() != CLASS_DEFINE_TYPE
                    || vec[i]->getValue() != methods[name][i]->getValue()) {
                        std::cerr << "Class " << classDeclaration->getClass()->getValue() << " does not implement the method " << name << " in interface " << classDeclaration->getInterface()->getValue() << std::endl;
                        exit(2);
                    }
                } else {
                    if (vec[i]->getValue() != methods[name][i]->getValue()) {
                        std::cerr << "Class " << classDeclaration->getClass()->getValue() << " does not implement the method " << name << " in interface " << classDeclaration->getInterface()->getValue() << std::endl;
                        exit(2);
                    }
                }
            }
        }
    }
    return nullptr;
}

llvm::Value *CodeGen::visit(const InterfaceDeclaration *interfaceDeclaration) {
    interfaceMethodTable[interfaceDeclaration] = std::unordered_map<std::string, std::vector<Identifier*>>();
    symbolTable.push(interfaceDeclaration->getInterface()->getValue(), interfaceDeclaration);
    for (const auto &stmt : *interfaceDeclaration->getInterfaceBlock()->getStatementList()) {
        if (dynamic_cast<const FunctionDeclaration *>(stmt) != nullptr) {
            auto funcDecl = reinterpret_cast<const FunctionDeclaration*>(stmt);
            interfaceMethodTable[interfaceDeclaration][funcDecl->getFunc()->getValue()] = std::vector<Identifier*>();
            interfaceMethodTable[interfaceDeclaration][funcDecl->getFunc()->getValue()].push_back(funcDecl->getReturnType());
            for (const auto &type : *funcDecl->getParamList()) {
                interfaceMethodTable[interfaceDeclaration][funcDecl->getFunc()->getValue()].push_back(
                        reinterpret_cast<Identifier *const>(type));
            }
        }
    }
    return nullptr;
}

llvm::Value *CodeGen::visit(const IfStatement *ifStatement) {
    llvm::Function* theFunction = irBuilder.GetInsertBlock()->getParent();
    llvm::Value* condValue = deRef(visit(ifStatement->getCondition()));
    llvm::BasicBlock* beforeBlock = irBuilder.GetInsertBlock();
    llvm::BasicBlock* trueBlock = visit(ifStatement->getTrueBlock(), true, "trueBlock");
    llvm::BasicBlock* afterTrueBlock = irBuilder.GetInsertBlock();
    llvm::BasicBlock* falseBlock = visit(ifStatement->getFalseBlock(), true, "falseBlock");
    llvm::BasicBlock* afterFalseBlock = irBuilder.GetInsertBlock();
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(llvmContext, "after", theFunction);
    if (falseBlock) {
        irBuilder.SetInsertPoint(beforeBlock);
        irBuilder.CreateCondBr(CastToBoolean(llvmContext, condValue), trueBlock, falseBlock);
        irBuilder.SetInsertPoint(afterTrueBlock);
        irBuilder.CreateBr(afterBlock);
        irBuilder.SetInsertPoint(afterFalseBlock);
        irBuilder.CreateBr(afterBlock);
        irBuilder.SetInsertPoint(afterBlock);
//        irBuilder.SetInsertPoint();
    } else {
        irBuilder.SetInsertPoint(beforeBlock);
        irBuilder.CreateCondBr(CastToBoolean(llvmContext, condValue), trueBlock, afterBlock);
        irBuilder.SetInsertPoint(afterTrueBlock);
        irBuilder.CreateBr(afterBlock);
        irBuilder.SetInsertPoint(afterBlock);
    }
}

llvm::Value *CodeGen::visit(const ForStatement * forStatement) {
    llvm::Function* theFunction = irBuilder.GetInsertBlock()->getParent();
    llvm::BasicBlock* block = llvm::BasicBlock::Create(llvmContext, "forloop", theFunction);
    llvm::BasicBlock* after = llvm::BasicBlock::Create(llvmContext, "forcont");
    llvm::BasicBlock* continueBlock = llvm::BasicBlock::Create(llvmContext, "continueBlock");

    continueStack.push(continueBlock);
    breakStack.push(after);

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
    theFunction->getBasicBlockList().push_back(continueBlock);
    irBuilder.CreateBr(continueBlock);
    irBuilder.SetInsertPoint(continueBlock);
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

    continueStack.pop();
    breakStack.pop();

    return nullptr;
}

llvm::Value *CodeGen::visit(const WhileStatement *whileStatement) {
    llvm::Function* theFunction = irBuilder.GetInsertBlock()->getParent();
    llvm::BasicBlock* block = llvm::BasicBlock::Create(llvmContext, "whileloop", theFunction);
    llvm::BasicBlock* after = llvm::BasicBlock::Create(llvmContext, "whilecont");
    llvm::BasicBlock* continueBlock = llvm::BasicBlock::Create(llvmContext, "continueBlock");

    continueStack.push(continueBlock);
    breakStack.push(after);

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
    theFunction->getBasicBlockList().push_back(continueBlock);
    irBuilder.CreateBr(continueBlock);
    irBuilder.SetInsertPoint(continueBlock);
    condValue = visit(whileStatement->getCondition());
    condValue = CastToBoolean(llvmContext, condValue);
    irBuilder.CreateCondBr(condValue, block, after);
    theFunction->getBasicBlockList().push_back(after);
    irBuilder.SetInsertPoint(after);

    continueStack.pop();
    breakStack.pop();

    return nullptr;
}

llvm::Value *CodeGen::visit(const ReturnStatement *returnStatement) {
    if (returnStatement->getReturnExpr()) {
        llvm::Value *returnValue = visit(returnStatement->getReturnExpr(), true);
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
                    arg = irBuilder.CreateGEP(arg, {zero, zero}, "arrayIndex");
                } else {
                    if (!ioStatement->getIsRead()) {
                        arg = value;
                    }
                }
            }
            if (arg->getType()->isFloatTy()) {
                arg = irBuilder.CreateFPExt(arg, llvm::Type::getDoubleTy(llvmContext), "promoteToDouble");
            }
            args.push_back(arg);
        }
    }

    if (ioStatement->getIsRead()) {
        irBuilder.CreateCall(scanfFunc, args, "scanfResult");
    } else {
        irBuilder.CreateCall(printfFunc, args, "printfResult");
    }
}

llvm::Value *CodeGen::visit(const Expression * expression, bool deref) {
    switch (expression->getType()) {
        case ARITHMETICEXPRESSION: case BINARYOPERATOR: case UNARYOPERATOR: case TYPECONVERTOPERATOR:
            return visit(dynamic_cast<const ArithmeticExpression *>(expression));
        case ASSIGNEXPRESSION:
            return visit(dynamic_cast<const AssignExpression *>(expression));
        case CLASSNEWEXPRESSION:
            return visit(dynamic_cast<const ClassNewExpression *>(expression));
            break;
        case CLASSEXPRESSION:
            break;
        case CLASSVARIABLEEXPRESSION:
            break;
        case CLASSFUNCEXPRESSION:
            break;
        case ENTITYEXPRESSION:
            return visit(dynamic_cast<const Entity *>(expression), deref).value;
        case INT_VALUE: case LONG_VALUE: case FLOAT_VALUE: case DOUBLE_VALUE: case CHAR_VALUE: case BOOLEAN_VALUE:
            return visit(dynamic_cast<const Identifier *>(expression), true).value;
        case LAMBDADECLARATION:
            return visit(dynamic_cast<const LambdaExpression *>(expression));
        default:
            return nullptr;
    }
}

llvm::Value *CodeGen::visit(const AssignExpression *assignExpression) {
    llvm::Value *target = visit(assignExpression->getEntity()).value;
    llvm::Value *source = visit(assignExpression->getExpr());
    if (source->getType()->isPointerTy()) {
        source = deRef(source);
    }
    irBuilder.CreateStore(source, target);
    return target;
}

llvm::Value *CodeGen::visit(const BreakStatement *breakStatement) {
    auto targetBlock = breakStack.top();
    return irBuilder.CreateBr(targetBlock);
}

llvm::Value *CodeGen::visit(const ContinueStatement *continueStatement) {
    auto targetBlock = continueStack.top();
    return irBuilder.CreateBr(targetBlock);
}


