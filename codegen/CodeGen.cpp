//
// Created by 游添予 on 2021/6/2.
//

#include "CodeGen.h"

void CodeGen::genCode(const Block *root, const std::string outputFileName) {

}

CodeGen::CodeGen(): module("posfol", llvmContext), irBuilder(llvmContext) {

}
