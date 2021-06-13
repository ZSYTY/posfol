//
// Created by GuoZiYang on 2021/6/13.
//

#include "CodeGen.h"

int CodeGen::getNameIdInClass(const ClassDeclaration * classDeclaration, std::string name) {
    int idx = 0;
    for (const auto &stmt : *classDeclaration->getClassBlock()->getStatementList()) {
        if (dynamic_cast<const VariableDeclaration*>(stmt) != nullptr) {
            auto varDecl = reinterpret_cast<const VariableDeclaration*>(stmt);
            if (varDecl->getVar()->getValue() == name) {
                return idx;
            }
            idx++;
        }
    }
    return -1;
}
