#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>

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
    Block() : statementList(new  std::vector<Statement*>()) {}
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
 * identifier主要是：
 * 类型本身：基本类型(如"int")、数组类型(如int a[n])、类类型(如class A中的"class")
 * 自定义变量：如int a中的"a", int b[n]中的"b", class A中的"A"
 * 常数：如666
 * 
 * identifier需要在创建对象时传入变量值：Identifier->numeric{$$=$1}, numeric->INT{$$=new Identifier(INT, $1->c_str())}|DOUBLE{$$=new Identifier(DOUBLE, $1->c_str())}
 * 基本类型：INT、LONG、FLOAT、DOUBLE、BOOLEAN、CHAR
 * 数组类型：ARRAY
 * 类类型：CLASS
 */
class Identifier : public Expression {
   private:
    Type type = IDENTIFIER;       // type需要在yacc创建对象时(比如在创建Declaration对象时，就可以把类型参数set到Identifier上了)被修改，这里只是给一个默认初始值
    std::string name = nullptr;   // 保存identifier的name，主要是保存自定义变量名
    std::string value = nullptr;  // 如果Identifier是常数，则用string形式的value保存其值
    bool isType = false;
    bool isVariable = false;
    bool isConst = false;

   public:
    // 类型：type
    Identifier(Type type) : type(type), isType(true) {}
    // 变量：type : name
    Identifier(Type type, const std::string& name) : type(type), name(name), isVariable(true) {}
    // 常量：type : value
    Identifier(Type type, std::string value) : type(type), value(value), isConst(true) {}
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

    std::string getValue() const {
        return this->value;
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
 * 二元操作：expr op expr, || $$ >= > <= < == != + - * / %
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
 * @author guoziyang
 *
 * 一元操作：op expr, - !
 * 最终expr会转化为Identifier, 即变量
 */
class UnaryOperator : public ArithmeticExpression {
private:
    Type type = BINARYOPERATOR;
    int op = -1;
    Expression* hs = nullptr;

public:
    UnaryOperator(int op, Expression* hs) : op(op), hs(hs) {}
    ~UnaryOperator() {
        delete hs;
    }

    Type getType() const override {
        return this->type;
    }

    int getOp() {
        return op;
    }

    Expression* getHs() {
        return hs;
    }
};


/**
 * @author guoziyang
 *
 * (int|float) a
 */
class TypeConvertOperator : public ArithmeticExpression {
private:
    Type type = TYPECONVERTOPERATOR;
    Identifier* targetType;
    Expression* expr = nullptr;

public:
    TypeConvertOperator(Identifier* targetType, Expression* expr) : targetType(targetType), expr(expr) {}
    ~TypeConvertOperator() {
        delete targetType;
        delete expr;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getOp() {
        return targetType;
    }

    Expression* getExpr() {
        return expr;
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
 * 类表达式：访问类成员变量a.b, 调用类成员函数a.f()
 */
class ClassExpression : public Expression {
   private:
    Type type = CLASSEXPRESSION;

   public:
    ClassExpression() {}
    ~ClassExpression() {}

    Type getType() const override {
        return this->type;
    }
};

/**
 * @author gehao
 * 
 * 访问类成员变量表达式：Identifier_obj.Identifier_obj.Identifier_obj....Identifier_member
 * a.b.c or a.b 
 */
class ClassVariableExpression : public ClassExpression {
   private:
    Type type = CLASSVARIABLEEXPRESSION;
    Identifier* obj = nullptr;
    std::vector<Identifier*>* objList = nullptr;  // 必须保证objList里除了最后一个Identifier，其余都是类对象，否则检查时报错

   public:
    ClassVariableExpression(Identifier* obj, std::vector<Identifier*>* objList) : obj(obj), objList(objList) {}
    ~ClassVariableExpression() {
        delete obj;
        delete objList;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getObj() {
        return obj;
    }

    std::vector<Identifier*>* getObjList() {
        return objList;
    }
};

/**
 * @author gehao
 * 
 * 访问类成员函数： Identifier_obj.Identifier_obj.Identifier_obj....Identifier_func
 * a.b.c.func or a.func
 */
class ClassFuncExpression : public ClassExpression {
   private:
    Type type = CLASSFUNCEXPRESSION;
    Identifier* obj = nullptr;
    std::vector<Identifier*>* objList = nullptr;  // 必须保证objList里除了最后一个Identifier，其余都是类对象，否则检查时报错
    FuncCallExpression* func = nullptr; // 通过前面的对象block作用域，确定到当前的func，随后就可以像普通函数那样调用

   public:
    // a.f()
    ClassFuncExpression(Identifier* obj, FuncCallExpression* func) : obj(obj), func(func) {}
    // a.b.c.f()
    ClassFuncExpression(Identifier* obj, std::vector<Identifier*>* objList, FuncCallExpression* func) : obj(obj), objList(objList), func(func) {}
    ~ClassFuncExpression() {
        delete obj;
        delete objList;
        delete func;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getObj() {
        return obj;
    }

    std::vector<Identifier*>* getObjList() {
        return objList;
    }    

    FuncCallExpression* getFunc() {
        return func;
    }    
};

class Entity : public Expression {
private:
    Type type = ENTITYEXPRESSION;
    bool isTerminal;
    Entity* entity = nullptr;

    Identifier* identifier = nullptr;
    Expression* expression = nullptr;
    std::vector<Expression*>* vectorExpression = nullptr;

public:
    // a = xxx
    Entity(Identifier* variable) : isTerminal(true), identifier(variable) {}
    // a.b = xxx
    Entity(Entity* entity, Identifier* variable) : isTerminal(false), entity(entity), identifier(variable) {}
    // a[b+1] = xxx
    Entity(Entity* entity, Expression* variable) : isTerminal(false), entity(entity), expression(variable) {}
    // a(b,c) = xxx
    Entity(Entity* entity, std::vector<Expression*>* variable) : isTerminal(false), entity(entity), vectorExpression(variable) {}

    ~Entity() {
        if(identifier != nullptr) {
            delete identifier;
        }
        if(expression != nullptr) {
            delete expression;
        }
        if(vectorExpression != nullptr) {
            for (auto it = vectorExpression->begin(); it != vectorExpression->end(); ++it) {
                delete *it;
            }
            delete vectorExpression;
        }
        if (entity != nullptr) {
            delete entity;
        }
    }

    bool getIsTerminal() {
        return isTerminal;
    }
    Entity* getEntity() {
        return entity;
    }
    Identifier* getIdentifier() {
        return identifier;
    }
    Expression* getExpression() {
        return expression;
    }
    std::vector<Expression*>* getVectorExpression() {
        return vectorExpression;
    }

};

/** 
 * @author gehao, guoziyang
 *
 * op: = += -= *= /= %=
 *
 * 赋值语句：变量赋值、数组赋值、类成员赋值
 */
class AssignExpression : public Expression {
   private:
    Type type = ASSIGNEXPRESSION;
    Entity* entity;
    int op = -1;
    Expression* expr;

   public:
    AssignExpression(Entity* entity, int op, Expression* expr): entity(entity), op(op), expr(expr) {}
    ~AssignExpression() {
        delete entity;
        delete expr;
    }

    Type getType() const override {
        return this->type;
    }
    Entity* getEntity() {
        return entity;
    }
    Expression* getExpr() {
        return expr;
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


class VariableDeclaration;

/**
 * @author guoziyang
 *
 * [outerVars](paramList) {funcBlock}
 *
 */
class LambdaExpression : public Expression {
private:
    Type type = LAMBDADECLARATION;
    std::vector<Identifier*>* outerVars = nullptr;
    std::vector<VariableDeclaration*>* paramList = nullptr;
    Block* funcBlock = nullptr;

public:
    LambdaExpression(std::vector<Identifier*>* outerVars, std::vector<VariableDeclaration*>* paramList, Block* funcBlock) : outerVars(outerVars), paramList(paramList), funcBlock(funcBlock) {}
    ~LambdaExpression() {
        for (auto it = outerVars->begin(); it != outerVars->end(); ++it) {
            delete *it;
        }
        for (auto it = paramList->begin(); it != paramList->end(); ++it) {
            delete *it;
        }
        delete outerVars;
        delete paramList;
        delete funcBlock;
    }

    Type getType() const override {
        return this->type;
    }

    std::vector<Identifier*>* getOuterVars() {
        return this->outerVars;
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
 * 变量声明：Identifier_type Identifier_var = expr
 * - 基本变量声明：int a;  int a = expr;
 * - 类变量声明：A a = new A();
 * 这里int, A, a都是Identifier，详情参考Identifier类
 * 
 * TODO: type不写成Identifier，而是直接通过判断来设置var的type
 */
class VariableDeclaration : public Declaration {
public:
   private:
    Type type = VARIABLEDECLARATION;
    Identifier* varType = nullptr;
    Identifier* var = nullptr;
    Expression* expr = nullptr;
    std::vector<Expression*>* arraySizes = nullptr;

   public:
    // 构造函数1：如int a;
    VariableDeclaration(Identifier* varType, Identifier* var) : varType(varType), var(var) {}
    // 构造函数2：如int a = b + 1;
    VariableDeclaration(Identifier* varType, Identifier* var, Expression* expr) : varType(varType), var(var), expr(expr) {}
    // 构造函数4：如int a[100][10];
    VariableDeclaration(Identifier* varType, Identifier* var, std::vector<Expression*>* arraySizes) : varType(varType), var(var), arraySizes(arraySizes) {}

    ~VariableDeclaration() {
        delete varType;
        delete var;
        for (auto it = arraySizes->begin(); it != arraySizes->end(); ++it) {
            delete *it;
        }
        delete arraySizes;
        delete expr;
    }

    void setVarType(Identifier* varType) {
        this->varType = varType;
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
    std::vector<Expression*>* getArraySizes() {
        return this->arraySizes;
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
    Identifier* _interface = nullptr;
    Block* classBlock = nullptr;

   public:
    // 纯类声明
    ClassDeclaration(Identifier* _class) : _class(_class) {}
    // 类声明+定义
    ClassDeclaration(Identifier* _class, Block* classBlock) : _class(_class), classBlock(classBlock) {}
    // 类声明+定义+接口
    ClassDeclaration(Identifier* _class, Identifier* _interface, Block* classBlock) : _class(_class), _interface(_interface)), classBlock(classBlock) {}
    
    ~ClassDeclaration() {
        delete _class;
        delete _interface;
        delete classBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getClass() {
        return this->_class;
    }

    Identifier* getInterface() {
        return this->_interface;
    }

    Block* getClassBlock() {
        return this->classBlock;
    }
};

class InterfaceDeclaration : public Declaration {
private:
    Type type = INTERFACEDECLARATION;
    Identifier* _interface = nullptr;
    Block* interfaceBlock = nullptr;

public:
    // 类声明+定义
    InterfaceDeclaration(Identifier* _interface, Block* interfaceBlock) : _interface(_interface), interfaceBlock(interfaceBlock) {}

    ~InterfaceDeclaration() {
        delete _interface;
        delete interfaceBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getInterface() {
        return this->_interface;
    }

    Block* getInterfaceBlock() {
        return this->interfaceBlock;
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