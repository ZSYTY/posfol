#ifndef __CHECK_H__
#define __CHECK_H__

#include "../tree/node.h"
#include "../tree/type.h"

bool checkProgram(Block* programBlock);
bool checkBlock(Block* root);
bool checkDeclaration(Declaration* decl);
bool checkExpression(Expression* expr);
bool checkLogicStatement(LogicStatement* logic);
#endif