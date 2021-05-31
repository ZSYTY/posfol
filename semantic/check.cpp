#include <string>
#include <unordered_map>
#include <vector>

#include "../tree/node.h"
#include "sem_util.h"
#include "symbol.h"
#include "../tree/type.h"

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