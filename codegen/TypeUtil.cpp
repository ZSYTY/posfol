//
// Created by 游添予 on 2021/6/6.
//

#include "CodeGen.h"

llvm::Type * CodeGen::getType(Type type) {
    switch (type) {
        case INT_DEFINE_TYPE:
            return llvm::Type::getInt32Ty(llvmContext);
        case LONG_DEFINE_TYPE:
            return llvm::Type::getInt64Ty(llvmContext);
        case FLOAT_DEFINE_TYPE:
            return llvm::Type::getFloatTy(llvmContext);
        case DOUBLE_DEFINE_TYPE:
            return llvm::Type::getDoubleTy(llvmContext);
        case BOOLEAN_DEFINE_TYPE:
            return llvm::Type::getInt1Ty(llvmContext);
        case CHAR_DEFINE_TYPE:
            return llvm::Type::getInt8Ty(llvmContext);
        default:
            return llvm::Type::getVoidTy(llvmContext);
    }
}