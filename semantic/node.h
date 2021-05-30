#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>
#include <vector>

#include "type.h"

class Node {
   private:
    Type type = NODE;

   public:
    Node() {}
    virtual ~Node() {}

    std::vector<Node*> children;
    virtual Type getType() const {
        return this->type;
    }
};

class Statement : public Node {
   private:
    Type type = STATEMENT;

   public:
    Statement() {}
    ~Statement() {}

    Type getType() const override {
        return this->type;
    }
};

/**
 * @author gehao
 * 
 * Block -> {stmts} 
 */
class Block : public Statement {
   private:
    Type type = BLOCK;
    std::vector<Statement*>* statementList = nullptr;

   public:
    Block(std::vector<Statement*>* statementList) : statementList(statementList) {}
    ~Block() {
        delete statementList;
    }

    Type getType() const override {
        return this->type;
    }
    std::vector<Statement*>* getStatementList() {
        return this->statementList;
    }
};

/**
 * @author gehao
 * 
 * Expression -> Identifier, ArithmeticExpression, AssignExpression, FuncCallExpression
 */
class Expression : public Statement {
   private:
    Type type = EXPRESSION;

   public:
    Expression() {}
    ~Expression() {}

    Type getType() const override {
        return this->type;
    }
};

/**
 * @author gehao
 * 
 * identifier主要是：基本类型(如"int")、类类型(如class A中的"class")和自定义变量(如int a中的"a", class A中的"A")
 * identifier只负责保存该标识符的名称，具体type由yacc传入时决定
 * 基本类型：INT、LONG、FLOAT、DOUBLE、BOOLEAN、CHAR
 * 类类型：CLASS
 * 自定义变量：VARIABLE
 */
class Identifier : public Expression {
   private:
    Type type = IDENTIFIER;  // type需要在yacc创建对象时被修改，这里只是给一个默认初始值
    std::string name;        // 保存identifier的name，主要是保存自定义变量名

   public:
    Identifier(const std::string& name, Type type) {
        this->name = name;
        this->type = type;
    }
    ~Identifier() {}

    Type getType() const override {
        return this->type;
    }

    std::string getName() const {
        return this->name;
    }
};

/**
 * @author gehao
 * 
 * 变量声明、函数声明、类声明
 */
class Declaration : public Statement {
   private:
    Type type = DECLARATION;

   public:
    Declaration() {}
    ~Declaration() {}

    Type getType() const override {
        return this->type;
    }
};

/**
 * @author gehao
 * 
 * 变量声明：Identifier_type Identifier_var = expr
 * - 基本变量声明：int a;  int a = expr;
 * - 类变量声明：A a = new A();
 * 这里int, A, a都是Identifier，详情参考Identifier类
 */
class VariableDeclaration : public Declaration {
   private:
    Type type = VARIABLEDECLARATION;
    Identifier* varType = nullptr;
    Identifier* var = nullptr;
    Expression* expr = nullptr;

   public:
    // 构造函数1：如int a;
    VariableDeclaration(Identifier* varType, Identifier* var) : varType(varType), var(var) {}
    // 构造函数2：如int a = b + 1;
    VariableDeclaration(Identifier* varType, Identifier* var, Expression* expr) : varType(varType), var(var), expr(expr) {}
    ~VariableDeclaration() {
        delete varType;
        delete var;
        delete expr;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getVarType() {
        return this->varType;
    }

    Identifier* getVar() {
        return this->var;
    }

    Expression* getExpr() {
        return this->expr;
    }
};

/**
 * @author gehao
 * 
 * 函数声明：Identifier_type Identifier_func_var(Identifier_type1 Identifier_var1, Identifier_type2 Identifier_var2, ...){...}
 * - int f(int a, int b, ...); 
 * - int f(int a, int b, ...){...};
 */
class FunctionDeclaration : public Declaration {
   private:
    Type type = FUNCTIONDECLARATION;
    Identifier* returnType = nullptr;
    Identifier* func = nullptr;
    std::vector<VariableDeclaration*>* paramList = nullptr;  // 不单独为paramList创建一个类，因此这里用vector表示
    Block* funcBlock = nullptr;                              // 函数体

   public:
    // 纯函数声明
    FunctionDeclaration(Identifier* returnType, Identifier* func, std::vector<VariableDeclaration*>* paramList) : returnType(returnType), func(func), paramList(paramList) {}
    // 函数声明+定义
    FunctionDeclaration(Identifier* returnType, Identifier* func, std::vector<VariableDeclaration*>* paramList, Block* funcBlock) : returnType(returnType), func(func), paramList(paramList), funcBlock(funcBlock) {}
    ~FunctionDeclaration() {
        delete returnType;
        delete func;
        delete paramList;
        delete funcBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getReturnType() {
        return this->returnType;
    }

    Identifier* getFunc() {
        return this->func;
    }

    std::vector<VariableDeclaration*>* getParamList() {
        return this->paramList;
    }

    Block* getFuncBlock() {
        return this->funcBlock;
    }
};

/**
 * @author gehao
 * 
 * 类声明：Idenrifier_class Identifier_class_var Block;
 * - class A;
 * - class A{...}; 
 */
class ClassDeclaration : public Declaration {
   private:
    Type type = CLASSDECLARATION;
    Identifier* _class = nullptr;
    Block* classBlock = nullptr;

   public:
    // 纯类声明
    ClassDeclaration(Identifier* _class) : _class(_class) {}
    // 类声明+定义
    ClassDeclaration(Identifier* _class, Block* classBlock) : _class(_class), classBlock(classBlock) {}
    ~ClassDeclaration() {
        delete _class;
        delete classBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getClass() {
        return this->_class;
    }

    Block* getClassBlock() {
        return this->classBlock;
    }
};

/**
 * @author gehao
 * 
 * logic statement: if、for、while 
 */
class LogicStatement : public Statement {
   private:
    Type type = LOGICSTATEMENT;

   public:
    LogicStatement() {}
    ~LogicStatement() {}

    Type getType() const override {
        return this->type;
    }
};

/**
 * @author gehao
 * 
 * if语句：if (expr_condition) {block_true} else {block_false}
 * - if () {}
 * - if () {} else {}
 */
class IfStatement : public LogicStatement {
   private:
    Type type = IFSTATEMENT;
    Expression* condition = nullptr;
    Block* trueBlock = nullptr;
    Block* falseBlock = nullptr;

   public:
    // if () {}
    IfStatement(Expression* condition, Block* trueBlock) : condition(condition), trueBlock(trueBlock) {}
    // if () {} else {}
    IfStatement(Expression* condition, Block* trueBlock, Block* falseBlock) : condition(condition), trueBlock(trueBlock), falseBlock(falseBlock) {}
    ~IfStatement() {
        delete condition;
        delete trueBlock;
        delete falseBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Expression* getCondition() {
        return this->condition;
    }

    Block* getTrueBlock() {
        return this->trueBlock;
    }

    Block* getFalseBlock() {
        return this->falseBlock;
    }
};

/**
 * @author gehao
 * 
 * for语句：for (expr_init; expr_condition; expr_change) {block}
 */
class ForStatement : public LogicStatement {
   private:
    Type type = FORSTATEMENT;
    Expression* initial = nullptr;
    Expression* condition = nullptr;
    Expression* change = nullptr;
    Block* forBlock = nullptr;

   public:
    ForStatement(Expression* initial, Expression* condition, Expression* change, Block* forBlock) : initial(initial), condition(condition), change(change), forBlock(forBlock) {}
    ~ForStatement() {
        delete initial;
        delete condition;
        delete change;
        delete forBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Expression* getInitial() {
        return initial;
    }

    Expression* getCondition() {
        return condition;
    }

    Expression* getChange() {
        return change;
    }

    Block* getForBlock() {
        return forBlock;
    }
};

/**
 * @author gehao
 * 
 * while语句：while(expr_condition) {block} 
 */
class WhileStatement : public LogicStatement {
   private:
    Type type = WHILESTATEMENT;
    Expression* condition = nullptr;
    Block* whileBlock = nullptr;

   public:
    WhileStatement(Expression* condition, Block* whileBlock) : condition(condition), whileBlock(whileBlock) {}
    ~WhileStatement() {
        delete condition;
        delete whileBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Expression* getCondition() {
        return condition;
    }

    Block* getWhileBlock() {
        return whileBlock;
    }
};

#endif