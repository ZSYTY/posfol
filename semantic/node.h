#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "type.h"

// Type getTypeByName_233(std::string name) {
//     std::unordered_map<std::string, Type> map;
//     map["int"] = INT;
//     map["long"] = LONG;
//     map["float"] = FLOAT;
//     map["double"] = DOUBLE;
//     map["boolean"] = BOOLEAN;
//     map["char"] = CHAR;
//     map["array"] = ARRAY;
//     map["class"] = CLASS;

//     if (map.count(name) != 0) {
//         return map[name];
//     } else {
//         return ERROR;
//     }
// }
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
 * identifier主要是：基本类型(如"int")、数组类型(如int a[n])、类类型(如class A中的"class")和自定义变量(如int a中的"a", int b[n]中的"b", class A中的"A")
 * identifier只负责保存该标识符的名称，具体type由yacc传入时决定
 * 基本类型：INT、LONG、FLOAT、DOUBLE、BOOLEAN、CHAR
 * 数组类型：ARRAY
 * 类类型：CLASS
 * 自定义变量：VARIABLE
 */
class Identifier : public Expression {
   private:
    Type type = IDENTIFIER;  // type需要在yacc创建对象时(比如在创建Declaration对象时，就可以把类型参数set到Identifier上了)被修改，这里只是给一个默认初始值
    std::string name;        // 保存identifier的name，主要是保存自定义变量名

   public:
    Identifier(const std::string& name, Type type) {
        this->name = name;
        this->type = type;
    }
    ~Identifier() {}

    void setType(Type type) {
        this->type = type;
    }

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
 * 算术表达式
 */
class ArithmeticExpression : public Expression {
   private:
    Type type = ARITHMETICEXPRESSION;

   public:
    ArithmeticExpression() {}
    ~ArithmeticExpression() {}

    Type getType() const override {
        return this->type;
    }
};

/** 
 * @author gehao
 * 
 * 二元操作：expr op expr, + - * / < > <= >= = == 
 * 最终expr会转化为Identifier, 即变量 
 */
class BinaryOperator : public ArithmeticExpression {
   private:
    Type type = BINARYOPERATOR;
    int op = -1;
    Expression* lhs = nullptr;
    Expression* rhs = nullptr;

   public:
    BinaryOperator(Expression* lhs, int op, Expression* rhs) : lhs(lhs), op(op), rhs(rhs) {}
    ~BinaryOperator() {
        delete lhs;
        delete rhs;
    }

    Type getType() const override {
        return this->type;
    }

    int getOp() {
        return op;
    }

    Expression* getLhs() {
        return lhs;
    }

    Expression* getRhs() {
        return rhs;
    }
};

/** 
 * @author gehao
 * 函数调用：Identifier_func (expr_list)
 * 参数表是一个list，每个元素都是Expression
 */
class FuncCallExpression : public Expression {
   private:
    Type type = FUNCCALLEXPRESSION;
    Identifier* func = nullptr;
    std::vector<Expression*>* paramExprList = nullptr;

   public:
    FuncCallExpression(Identifier* func, std::vector<Expression*>* paramExprList) : func(func), paramExprList(paramExprList) {}
    ~FuncCallExpression() {
        delete func;
        delete paramExprList;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getFunc() {
        return func;
    }

    std::vector<Expression*>* getParamExprList() {
        return paramExprList;
    }
};

/** 
 * @author gehao
 * 
 * 赋值语句：变量赋值、数组赋值、类成员赋值
 */
class AssignExpression : public Expression {
   private:
    Type type = ASSIGNEXPRESSION;

   public:
    AssignExpression() {}
    ~AssignExpression() {}

    Type getType() const override {
        return this->type;
    }
};

/** 
 * @author gehao
 * 
 * 变量赋值：Identifier_target = expr_source
 * 这里的source是Expression的结果，可以是变量Identifier、数学运算结果BinaryOperator或者函数返回值FuncCall
 */
class VariableAssign : public AssignExpression {
   private:
    Type type = VARIABLEASSIGN;
    Identifier* target = nullptr;
    Expression* source = nullptr;

   public:
    VariableAssign(Identifier* target, Expression* source) : target(target), source(source) {}
    ~VariableAssign() {
        delete target;
        delete source;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getTarget() {
        return target;
    }

    Expression* getSource() {
        return source;
    }
};

/** 
 * @author gehao
 * 
 * 数组赋值：Identifier_target[expr_index] = expr_val  如a[i]=1;
 * index可能是表达式
 */
class ArrayAssign : public AssignExpression {
   private:
    Type type = ARRAYASSIGN;
    Identifier* array = nullptr;
    Expression* index = nullptr;
    Expression* value = nullptr;

   public:
    ArrayAssign(Identifier* array, Expression* index, Expression* value) : array(array), index(index), value(value) {}
    ~ArrayAssign() {
        delete array;
        delete index;
        delete value;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getArray() {
        return array;
    }

    Expression* getIndex() {
        return index;
    }

    Expression* getValue() {
        return value;
    }
};

/** 
 * @author gehao
 * 
 * 类变量赋值：Identifier_class.Identifier_member = expr_value
 */
class ClassAssign : public AssignExpression {
   private:
    Type type = CLASSASSIGN;
    Identifier* _class;
    Identifier* member;
    Expression* value;

   public:
    ClassAssign(Identifier* _class, Identifier* member, Expression* value) : _class(_class), member(member), value(value) {}
    ~ClassAssign() {
        delete _class;
        delete member;
        delete value;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getClass() {
        return _class;
    }

    Identifier* getMember() {
        return member;
    }

    Expression* getValue() {
        return value;
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
 * 
 * TODO: type不写成Identifier，而是直接通过判断来设置var的type
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