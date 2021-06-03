#include <string>
#include <unordered_map>
#include <vector>

#include "../tree/node.h"
#include "../tree/type.h"
#include "sem_util.h"
#include "symbol.h"

extern Block* programBlock;

SymbolTable symbolTable;

/**
 * @author gehao 
 */
bool checkProgram(Block* programBlock) {
    return check(programBlock);
}

/**
 * @author gehao
 * 
 * 每进入一层block，就创建一个symbolTable的map压入栈中，表示新的一级变量作用域
 */
bool check(Block* root) {
    symbolTable.push();
    std::vector<Statement*>* stmts = root->getStatementList();

    for (auto it = stmts->begin(); it != stmts->end(); it++) {
        Statement* stmt = *it;
        if (instanceof <Declaration>(stmt)) {
            if (instanceof <VariableDeclaration>(stmt)) {
                ;
            } else if (instanceof <FunctionDeclaration>(stmt)) {
                ;
            } else if (instanceof <ClassDeclaration>(stmt)) {
                ;
            } else {
                return false;
            }
        } else if (instanceof <Expression>(stmt)) {
            if (instanceof <Identifier>(stmt)) {
                ;
            } else if (instanceof <FuncCallExpression>(stmt)) {
                ;
            } else if (instanceof <ArithmeticExpression>(stmt)) {
                if (instanceof <BinaryOperator>(stmt)) {
                    ;
                } else {
                    return false;
                }
            } else if (instanceof <AssignExpression>(stmt)) {
                if (instanceof <VariableAssign>(stmt)) {
                    ;
                } else if (instanceof <ArrayAssign>(stmt)) {
                    ;
                } else if (instanceof <ClassAssign>(stmt)) {
                    ;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (instanceof <LogicStatement>(stmt)) {
            if (instanceof <IfStatement>(stmt)) {
                ;
            } else if (instanceof <ForStatement>(stmt)) {
                ;
            } else if (instanceof <WhileStatement>(stmt)) {
                ;
            } else {
                return false;
            }
        } else if (instanceof <Block>(stmt)) {
            // 进入新的block，递归检查
            return check(dynamic_cast<Block*>(stmt));
        } else {
            return false;
        }
    }

    symbolTable.pop();
}

/**
 * @author gehao
 * 
 * 校验Expression的类型：Identifier、 FuncCallExpression、ArithmeticExpression、AssignExpression
 */
bool checkExpression(Expression* expr) {
    if (expr == nullptr) {
        return false;
    }

    // Identifier由yacc保证类型✅
    if (instanceof <Identifier>(expr)) {
        return true;
    }
    // 校验Func Call是否正确：
    // - 函数名是否存在于symbolTable中
    // - Func Call参数表传入的参数类型于Func Declaration声明的是否一致
    else if (instanceof <FuncCallExpression>(expr)) {
        FuncCallExpression* func_expr = dynamic_cast<FuncCallExpression*>(expr);
        // 获取func标识符
        Identifier* func = func_expr->getFunc();
        // 在符号表里查找func标识符的Declaration, 并转化为FunctionDeclaration*类型
        FunctionDeclaration* func_decl = dynamic_cast<FunctionDeclaration*>(symbolTable.findSymbol(func->getName()));
        // 如果func还没被声明过，或者并不是函数声明，此时func_decl都是nullptr
        if (func_decl == nullptr) {
            return false;
        }
        std::vector<VariableDeclaration*>* originParamList = func_decl->getParamList();
        std::vector<Expression*>* paramExprList = func_expr->getParamExprList();

    } else {
        return false;
    }
}