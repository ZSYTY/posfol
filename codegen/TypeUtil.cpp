//
// Created by 游添予 on 2021/6/6.
//

#include "CodeGen.h"

llvm::Type * CodeGen::getType(Type type, uint32_t arraySize) {
    llvm::Type* llvmType = nullptr;
    switch (type) {
        case INT_DEFINE_TYPE:
        case INT_VALUE:
            llvmType = llvm::Type::getInt32Ty(llvmContext);
            break;
        case LONG_DEFINE_TYPE:
        case LONG_VALUE:
            llvmType = llvm::Type::getInt64Ty(llvmContext);
            break;
        case FLOAT_DEFINE_TYPE:
        case FLOAT_VALUE:
            llvmType = llvm::Type::getFloatTy(llvmContext);
            break;
        case DOUBLE_DEFINE_TYPE:
        case DOUBLE_VALUE:
            llvmType = llvm::Type::getDoubleTy(llvmContext);
            break;
        case BOOLEAN_DEFINE_TYPE:
        case BOOLEAN_VALUE:
            llvmType = llvm::Type::getInt1Ty(llvmContext);
            break;
        case CHAR_DEFINE_TYPE:
        case CHAR_VALUE:
            llvmType = llvm::Type::getInt8Ty(llvmContext);
            break;
        default:
            llvmType = llvm::Type::getVoidTy(llvmContext);
            break;
    }
    if (arraySize) {
        return llvm::ArrayType::get(llvmType, arraySize);
    } else {
        return llvmType;
    }
}

std::string CodeGen::getFmtStr(llvm::Type *type) {
    if (type->isFloatTy()) {
        return "%lf";
    } else if (type->isIntegerTy()) {
        return "%d";
    } else if (type->isArrayTy() or type->isPointerTy()) {
        return "%s";
    }
}

llvm::Constant *CodeGen::genConstant(const Identifier *identifier) {
    auto type = getType(identifier->getType());
    switch (identifier->getType()) {
        case INT_VALUE:
            return llvm::ConstantInt::get(type, std::stoi(identifier->getValue()));
            break;
        case LONG_VALUE:
            return llvm::ConstantInt::get(type, std::stoi(identifier->getValue()));
            break;
        case FLOAT_VALUE:
            return llvm::ConstantFP::get(type, identifier->getValue());
            break;
        case DOUBLE_VALUE:
            return llvm::ConstantFP::get(type, identifier->getValue());
            break;
        case BOOLEAN_VALUE:
            return llvm::ConstantInt::get(type, identifier->getValue() == "true" ? 1 : 0);
            break;
        case CHAR_VALUE:
            return llvm::ConstantInt::get(type, *identifier->getValue().c_str());
            break;
        case FUNC_VALUE:
            break;
        default:
            break;
    }
}

