#include "check.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "../tree/node.h"
#include "../tree/type.h"
#include "sem_util.h"
#include "symbol.h"

extern Block* programBlock;

SymbolTable symbolTable;
std::unordered_map<Statement*, Type> nodeTypeMap;  // 保存除了Identifier*外的所有节点的类型

/**
 * @author gehao 
 */
bool checkProgram(Block* programBlock) {
    return true;
    // return checkBlock(programBlock);
}

/**
 * @author gehao
 * 
 * 每进入一层block，就创建一个symbolTable的map压入栈中，表示新的一级变量作用域
 */
bool checkBlock(Block* root) {
    symbolTable.pushAR();
    std::vector<Statement*>* stmts = root->getStatementList();

    for (auto it = stmts->begin(); it != stmts->end(); it++) {
        Statement* stmt = *it;
        if (instanceof <Declaration>(stmt)) {
            return checkDeclaration(dynamic_cast<Declaration*>(stmt));
        } else if (instanceof <Expression>(stmt)) {
            return checkExpression(dynamic_cast<Expression*>(stmt));
        } else if (instanceof <LogicStatement>(stmt)) {
            return checkLogicStatement(dynamic_cast<LogicStatement*>(stmt));
        } else if (instanceof <Block>(stmt)) {
            // 进入新的block，递归检查
            return checkBlock(dynamic_cast<Block*>(stmt));
        } else {
            return false;
        }
    }
    // block的type等于最后一条stmt的type
    nodeTypeMap[root] = nodeTypeMap[(*stmts)[stmts->size() - 1]];
    symbolTable.popAR();
}

/**
 * @author gehao
 * 
 * 检查Declaration是否正确 
 */
bool checkDeclaration(Declaration* decl) {
    if (instanceof <VariableDeclaration>(decl)) {
        VariableDeclaration* var = dynamic_cast<VariableDeclaration*>(decl);
        std::string name = var->getVar()->getValue();
        // 如果本作用域内已经声明过该变量，则编译错误
        if (symbolTable.isDeclared(name)) {
            return false;
        }
        // int a;
        if (var->getExpr() == nullptr && var->getArraySizes() == nullptr) {
            return true;
        }
        // int a = expr;
        else if (var->getExpr() != nullptr) {
            if (!checkExpression(var->getExpr()) || var->getVarType()->getType() != nodeTypeMap[var->getExpr()]) {
                return false;
            }
        }
        // int a[100][10];
        else if (var->getArraySizes() != nullptr) {
            std::vector<Expression*>* arraySizes = var->getArraySizes();
            for (Expression* expr : *arraySizes) {
                if (!checkExpression(expr) || nodeTypeMap[expr] != INT_DEFINE_TYPE) {
                    return false;
                }
            }
        }
        nodeTypeMap[var] = var->getVarType()->getType();
        symbolTable.push(name, var);
        return true;
    } else if (instanceof <FunctionDeclaration>(decl)) {
        FunctionDeclaration* func = dynamic_cast<FunctionDeclaration*>(decl);
        std::string name = func->getFunc()->getValue();
        // 如果本作用域内已经声明过该函数，则编译错误
        if (symbolTable.isDeclared(name)) {
            return false;
        }
        std::vector<VariableDeclaration*>* paramList = func->getParamList();
        for (VariableDeclaration* varDecl : *paramList) {
            if (!checkDeclaration(varDecl)) {
                return false;
            }
        }
        // 纯函数声明: int f(int a, int b, ...);
        if (func->getFuncBlock() == nullptr) {
            ;
        }
        // 函数声明+定义: int f(int a, int b, ...){...};
        else {
            if (!checkBlock(func->getFuncBlock()) || func->getReturnType()->getType() != nodeTypeMap[func->getFuncBlock()]) {
                return false;
            }
        }
        nodeTypeMap[func] = func->getReturnType()->getType();
        symbolTable.push(name, func);
        return true;
    } else if (instanceof <ClassDeclaration>(decl)) {
        ClassDeclaration* clz = dynamic_cast<ClassDeclaration*>(decl);
        std::string name = clz->getClass()->getValue();
        // 如果本作用域内已经声明过该函数，则编译错误
        if (symbolTable.isDeclared(name)) {
            return false;
        }
        // 纯类声明 class A;
        if (clz->getInterface() == nullptr && clz->getClassBlock() == nullptr) {
            ;
        }
        // 类声明+定义 class A{...};
        else if (clz->getInterface() == nullptr) {
            if (!checkBlock(clz->getClassBlock())) {
                return false;
            }
        }
        // 类声明+定义+接口 class A implements interface {...};
        else {
            if (!checkBlock(clz->getClassBlock())) {
                return false;
            }
            // 检查是否实现interface？
        }
        nodeTypeMap[clz] = CLASS_DEFINE_TYPE;
        symbolTable.push(name, clz);
        return true;
    } else {
        return false;
    }
}

bool checkExpression(Expression* expr) {
    return true;
}
bool checkLogicStatement(LogicStatement* logic) {
    return true;
}
