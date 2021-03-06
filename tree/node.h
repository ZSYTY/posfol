#ifndef __NODE_H__
#define __NODE_H__

#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "../json/json.hpp"
#include "type.h"

using json = nlohmann::json;

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
    virtual json genJSON() const {
        return json();
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
    Block() : statementList(new std::vector<Statement*>()) {}
    Block(std::vector<Statement*>* statementList) : statementList(statementList) {}
    ~Block() {
        delete statementList;
    }

    Type getType() const override {
        return this->type;
    }
    std::vector<Statement*>* getStatementList() const {
        return this->statementList;
    }
    json genJSON() const override {
        json root;
        root["name"] = "Block";
        for (auto it = statementList->begin(); it != statementList->end(); it++) {
            root["children"].push_back((*it)->genJSON());
        }
        return root;
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
 * identifier????????????
 * ???????????????????????????(???"int")???????????????(???int a[n])????????????(???class A??????"class")
 * ?????????????????????int a??????"a", int b[n]??????"b", class A??????"A"
 * ????????????666
 * 
 * identifier??????????????????????????????????????????Identifier->numeric{$$=$1}, numeric->INT{$$=new Identifier(INT, $1->c_str())}|DOUBLE{$$=new Identifier(DOUBLE, $1->c_str())}
 * ???????????????INT???LONG???FLOAT???DOUBLE???BOOLEAN???CHAR
 * ???????????????ARRAY
 * ????????????CLASS
 */
class Identifier : public Expression {
   private:
    Type type = IDENTIFIER;  // type?????????yacc???????????????(???????????????Declaration????????????????????????????????????set???Identifier??????)????????????????????????????????????????????????
    std::string value;       // ??????Identifier??????????????????string?????????value????????????
    bool isType = false;

   public:
    // ?????????type
    Identifier(Type type) : type(type), isType(true) {}
    // ?????????type : value
    Identifier(Type type, std::string value) : type(type), value(value) {}
    ~Identifier() {}

    void setType(Type type) {
        this->type = type;
    }

    Type getType() const override {
        return this->type;
    }

    std::string getValue() const {
        return this->value;
    }

    bool getIsType() const {
        return this->isType;
    }

    json genJSON() const override {
        json root;
        std::string type_name[] = {"INT",
                                   "LONG",
                                   "FLOAT",
                                   "DOUBLE",
                                   "BOOLEAN",
                                   "CHAR",
                                   "FUNC",
                                   "VOID"};
        root["name"] = "Identifier: " + (isType ? type_name[type - Type::INT_DEFINE_TYPE] : value);
        return root;
    }
};

/**
 * @author gehao
 * 
 * ???????????????
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
 * ???????????????expr op expr, || && >= > <= < == != + - * / %
 * ??????expr????????????Identifier, ????????? 
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

    int getOp() const {
        return op;
    }

    Expression* getLhs() const {
        return lhs;
    }

    Expression* getRhs() const {
        return rhs;
    }

    json genJSON() const override {
        json root;
        std::string op_name[] = {"||", "&&", ">=", ">", "<=", "<", "==", "!=", "+", "-", "*", "/", "%"};
        root["name"] = "BinaryOperator" + (op != -1 ? op_name[op] : "");
        root["children"].push_back(lhs->genJSON());
        root["children"].push_back(rhs->genJSON());
        return root;
    }
};

/**
 * @author guoziyang
 *
 * ???????????????op expr, - !
 * ??????expr????????????Identifier, ?????????
 */
class UnaryOperator : public ArithmeticExpression {
   private:
    Type type = UNARYOPERATOR;
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

    int getOp() const {
        return op;
    }

    Expression* getHs() const {
        return hs;
    }
    json genJSON() const override {
        json root;
        std::string op_name[] = {"-", "!"};
        root["name"] = "UnaryOperator" + (op != -1 ? op_name[op] : "");
        root["children"].push_back(hs->genJSON());
        return root;
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

    Identifier* getOp() const {
        return targetType;
    }

    Expression* getExpr() const {
        return expr;
    }
    json genJSON() const override {
        json root;
        root["name"] = "TypeConvertOperator";
        root["children"].push_back(targetType->genJSON());
        root["children"].push_back(expr->genJSON());
        return root;
    }
};

/**
 * @author guoziyang
 * ???????????????new Identifier_class (expr_list)
 * ??????????????????list?????????????????????Expression
 */
class ClassNewExpression : public Expression {
   private:
    Type type = CLASSNEWEXPRESSION;
    Identifier* className = nullptr;
    std::vector<Expression*>* paramExprList = nullptr;

   public:
    ClassNewExpression(Identifier* className, std::vector<Expression*>* paramExprList) : className(className), paramExprList(paramExprList) {}
    ~ClassNewExpression() {
        delete className;
        delete paramExprList;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getClassName() const {
        return className;
    }

    std::vector<Expression*>* getParamExprList() const {
        return paramExprList;
    }
    json genJSON() const override {
        json root;
        root["name"] = "ClassNewExpression";
        root["children"].push_back(className->genJSON());
        for (auto it = paramExprList->begin(); it != paramExprList->end(); ++it) {
            root["children"].push_back((*it)->genJSON());
        }
        return root;
    }
};

class Entity : public Expression {
   private:
    Type type = ENTITYEXPRESSION;
    bool isTerminal;
    Entity* entity = nullptr;

    bool objectCall = false;
    Identifier* identifier = nullptr;
    bool arrayIndex = false;
    Expression* expression = nullptr;
    bool functionCall = false;
    std::vector<Expression*>* vectorExpression = nullptr;

   public:
    // a = xxx
    Entity(Identifier* variable) : isTerminal(true), identifier(variable) {}
    // a.b = xxx
    Entity(Entity* entity, Identifier* variable) : isTerminal(false), objectCall(true), entity(entity), identifier(variable) {}
    // a[b+1] = xxx
    Entity(Entity* entity, Expression* variable) : isTerminal(false), arrayIndex(true), entity(entity), expression(variable) {}
    // a(b,c) = xxx
    Entity(Entity* entity, std::vector<Expression*>* variable) : isTerminal(false), functionCall(true), entity(entity), vectorExpression(variable) {}

    ~Entity() {
        if (identifier != nullptr) {
            delete identifier;
        }
        if (expression != nullptr) {
            delete expression;
        }
        if (vectorExpression != nullptr) {
            for (auto it = vectorExpression->begin(); it != vectorExpression->end(); ++it) {
                delete *it;
            }
            delete vectorExpression;
        }
        if (entity != nullptr) {
            delete entity;
        }
    }

    bool getIsObjectCall() const {
        return objectCall;
    }

    bool getIsArrayIndex() const {
        return arrayIndex;
    }

    bool getIsFunctionCall() const {
        return functionCall;
    }

    bool getIsTerminal() const {
        return isTerminal;
    }
    Entity* getEntity() const {
        return entity;
    }
    Identifier* getIdentifier() const {
        return identifier;
    }
    Expression* getExpression() const {
        return expression;
    }
    std::vector<Expression*>* getVectorExpression() const {
        return vectorExpression;
    }

    Type getType() const override {
        return type;
    }

    json genJSON() const override {
        json root;
        root["name"] = "Entity" + std::string(objectCall ? ": attr_call" : "") + std::string(arrayIndex ? ": array_index" : "") + (functionCall ? ": functionCall" : "");
        entity != nullptr ? root["children"].push_back(entity->genJSON()) : (void)0;
        identifier != nullptr ? root["children"].push_back(identifier->genJSON()) : (void)0;
        expression != nullptr ? root["children"].push_back(expression->genJSON()) : (void)0;

        if (vectorExpression != nullptr) {
            for (auto it = vectorExpression->begin(); it != vectorExpression->end(); ++it) {
                root["children"].push_back((*it)->genJSON());
            }
        }
        return root;
    }
};

/** 
 * @author gehao, guoziyang
 *
 * op: = += -= *= /= %=
 *
 * ????????????????????????????????????????????????????????????
 */
class AssignExpression : public Expression {
   private:
    Type type = ASSIGNEXPRESSION;
    Entity* entity;
    int op = -1;
    Expression* expr;

   public:
    AssignExpression(Entity* entity, int op, Expression* expr) : entity(entity), op(op), expr(expr) {}
    ~AssignExpression() {
        delete entity;
        delete expr;
    }

    Type getType() const override {
        return this->type;
    }
    Entity* getEntity() const {
        return entity;
    }
    Expression* getExpr() const {
        return expr;
    }

    json genJSON() const override {
        json root;
        std::string op_name[] = {"=", "+=", "-=", "*=", "/=", "%="};
        root["name"] = "AssignExpression" + (op != -1 ? op_name[op] : "");
        root["children"].push_back(entity->genJSON());
        root["children"].push_back(expr->genJSON());
        return root;
    }
};

/**
 * @author gehao
 * 
 * ???????????????????????????????????????
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
 * ???????????????Identifier_type Identifier_var = expr
 * - ?????????????????????int a;  int a = expr;
 * - ??????????????????A a = new A();
 * ??????int, A, a??????Identifier???????????????Identifier???
 * 
 * TODO: type?????????Identifier????????????????????????????????????var???type
 */
class VariableDeclaration : public Declaration {
   public:
   private:
    Type type = VARIABLEDECLARATION;
    Identifier* varType = nullptr;
    Identifier* var = nullptr;
    Expression* expr = nullptr;
    std::vector<Expression*>* arraySizes = nullptr;
    Identifier* funcReturnType = nullptr;
    std::vector<Identifier*>* funcParaList = nullptr;

   public:
    // ????????????1??????int a;
    VariableDeclaration(Identifier* varType, Identifier* var) : varType(varType), var(var) {}
    // ????????????2??????int a = b + 1;
    VariableDeclaration(Identifier* varType, Identifier* var, Expression* expr) : varType(varType), var(var), expr(expr) {}
    // ????????????4??????int a[100][10];
    VariableDeclaration(Identifier* varType, Identifier* var, std::vector<Expression*>* arraySizes) : varType(varType), var(var), arraySizes(arraySizes) {}
    // ????????????5:???func f<int(int, float)> = []() {}
    VariableDeclaration(Identifier* varType, Identifier* var, Identifier* funcReturnType, std::vector<Identifier*>* funcParaList, Expression* expr) : varType(varType), var(var), expr(expr), funcReturnType(funcReturnType), funcParaList(funcParaList) {}
    // ????????????6:???func f<char()> ?????????????????????????????????
    VariableDeclaration(Identifier* varType, Identifier* var, Identifier* funcReturnType, std::vector<Identifier*>* funcParaList) : varType(varType), var(var), funcReturnType(funcReturnType), funcParaList(funcParaList) {}
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

    Identifier* getVarType() const {
        return this->varType;
    }

    Identifier* getVar() const {
        return this->var;
    }
    Expression* getExpr() const {
        return this->expr;
    }

    std::vector<Expression*>* getArraySizes() const {
        return this->arraySizes;
    }

    Identifier* getFuncReturnType() const {
        return this->funcReturnType;
    }

    std::vector<Identifier*>* getFuncParaList() const {
        return this->funcParaList;
    }

    json genJSON() const override {
        json root;
        root["name"] = "VariableDeclaration";
        varType != nullptr ? root["children"].push_back(varType->genJSON()) : (void)0;
        var != nullptr ? root["children"].push_back(var->genJSON()) : (void)0;
        expr != nullptr ? root["children"].push_back(expr->genJSON()) : (void)0;
        funcReturnType != nullptr ? root["children"].push_back(funcReturnType->genJSON()) : (void)0;
        if (arraySizes != nullptr) {
            for (auto it = arraySizes->begin(); it != arraySizes->end(); ++it) {
                root["children"].push_back((*it)->genJSON());
            }
        }
        if (funcParaList != nullptr) {
            for (auto it = funcParaList->begin(); it != funcParaList->end(); ++it) {
                root["children"].push_back((*it)->genJSON());
            }
        }
        return root;
    }
};

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
    Identifier* returnType;
    Block* funcBlock = nullptr;

   public:
    LambdaExpression(std::vector<Identifier*>* outerVars, std::vector<VariableDeclaration*>* paramList, Identifier* returnType, Block* funcBlock) : outerVars(outerVars), paramList(paramList), returnType(returnType), funcBlock(funcBlock) {}
    ~LambdaExpression() {
        for (auto it = outerVars->begin(); it != outerVars->end(); ++it) {
            delete *it;
        }
        for (auto it = paramList->begin(); it != paramList->end(); ++it) {
            delete *it;
        }
        delete outerVars;
        delete paramList;
        delete returnType;
        delete funcBlock;
    }

    Type getType() const override {
        return this->type;
    }

    std::vector<Identifier*>* getOuterVars() const {
        return this->outerVars;
    }

    std::vector<VariableDeclaration*>* getParamList() const {
        return this->paramList;
    }

    Identifier* getReturnType() const {
        return this->returnType;
    }

    Block* getFuncBlock() const {
        return this->funcBlock;
    }

    json genJSON() const override {
        json root;
        root["name"] = "LambdaExpression";
        for (auto it = outerVars->begin(); it != outerVars->end(); ++it) {
            root["children"].push_back((*it)->genJSON());
        }
        for (auto it = paramList->begin(); it != paramList->end(); ++it) {
            root["children"].push_back((*it)->genJSON());
        }
        root["children"].push_back(returnType->genJSON());
        root["children"].push_back(funcBlock->genJSON());
        return root;
    }
};

/**
 * @author gehao
 * 
 * ???????????????Identifier_type Identifier_func_var(Identifier_type1 Identifier_var1, Identifier_type2 Identifier_var2, ...){...}
 * - int f(int a, int b, ...); 
 * - int f(int a, int b, ...){...};
 */
class FunctionDeclaration : public Declaration {
   private:
    Type type = FUNCTIONDECLARATION;
    Identifier* returnType = nullptr;
    Identifier* func = nullptr;
    std::vector<VariableDeclaration*>* paramList = nullptr;  // ????????????paramList?????????????????????????????????vector??????
    Block* funcBlock = nullptr;                              // ?????????

   public:
    // ???????????????
    FunctionDeclaration(Identifier* returnType, Identifier* func, std::vector<VariableDeclaration*>* paramList) : returnType(returnType), func(func), paramList(paramList) {}
    // ????????????+??????
    FunctionDeclaration(Identifier* returnType, Identifier* func, std::vector<VariableDeclaration*>* paramList, Block* funcBlock) : returnType(returnType), func(func), paramList(paramList), funcBlock(funcBlock) {}
    ~FunctionDeclaration() {
        delete returnType;
        delete func;
        for (auto it = paramList->begin(); it != paramList->end(); ++it) {
            delete *it;
        }
        delete paramList;
        delete funcBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getReturnType() const {
        return this->returnType;
    }

    Identifier* getFunc() const {
        return this->func;
    }

    std::vector<VariableDeclaration*>* getParamList() const {
        return this->paramList;
    }

    Block* getFuncBlock() const {
        return this->funcBlock;
    }
    json genJSON() const override {
        json root;
        root["name"] = "FunctionDeclaration";
        returnType != nullptr ? root["children"].push_back(returnType->genJSON()) : (void)0;
        func != nullptr ? root["children"].push_back(func->genJSON()) : (void)0;
        if (paramList != nullptr) {
            for (auto it = paramList->begin(); it != paramList->end(); ++it) {
                root["children"].push_back((*it)->genJSON());
            }
        }
        funcBlock != nullptr ? root["children"].push_back(funcBlock->genJSON()) : (void)0;
        return root;
    }
};

/**
 * @author gehao
 * 
 * ????????????Idenrifier_class Identifier_class_var Block;
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
    // ????????????
    ClassDeclaration(Identifier* _class) : _class(_class) {}
    // ?????????+??????
    ClassDeclaration(Identifier* _class, Block* classBlock) : _class(_class), classBlock(classBlock) {}
    // ?????????+??????+??????
    ClassDeclaration(Identifier* _class, Identifier* _interface, Block* classBlock) : _class(_class), _interface(_interface), classBlock(classBlock) {}

    ~ClassDeclaration() {
        delete _class;
        delete _interface;
        delete classBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getClass() const {
        return this->_class;
    }

    Identifier* getInterface() const {
        return this->_interface;
    }

    Block* getClassBlock() const {
        return this->classBlock;
    }
    json genJSON() const override {
        json root;
        root["name"] = "ClassDeclaration";
        _class != nullptr ? root["children"].push_back(_class->genJSON()) : (void)0;
        _interface != nullptr ? root["children"].push_back(_interface->genJSON()) : (void)0;
        classBlock != nullptr ? root["children"].push_back(classBlock->genJSON()) : (void)0;
        return root;
    }
};

class InterfaceDeclaration : public Declaration {
   private:
    Type type = INTERFACEDECLARATION;
    Identifier* _interface = nullptr;
    Block* interfaceBlock = nullptr;

   public:
    // ?????????+??????
    InterfaceDeclaration(Identifier* _interface, Block* interfaceBlock) : _interface(_interface), interfaceBlock(interfaceBlock) {}

    ~InterfaceDeclaration() {
        delete _interface;
        delete interfaceBlock;
    }

    Type getType() const override {
        return this->type;
    }

    Identifier* getInterface() const {
        return this->_interface;
    }

    Block* getInterfaceBlock() const {
        return this->interfaceBlock;
    }
    json genJSON() const override {
        json root;
        root["name"] = "InterfaceDeclaration";
        _interface != nullptr ? root["children"].push_back(_interface->genJSON()) : (void)0;
        interfaceBlock != nullptr ? root["children"].push_back(interfaceBlock->genJSON()) : (void)0;
        return root;
    }
};

/**
 * @author gehao
 * 
 * logic statement: if???for???while 
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
 * if?????????if (expr_condition) {block_true} else {block_false}
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

    Expression* getCondition() const {
        return this->condition;
    }

    Block* getTrueBlock() const {
        return this->trueBlock;
    }

    Block* getFalseBlock() const {
        return this->falseBlock;
    }
    json genJSON() const override {
        json root;
        root["name"] = "IfStatement";
        condition != nullptr ? root["children"].push_back(condition->genJSON()) : (void)0;
        trueBlock != nullptr ? root["children"].push_back(trueBlock->genJSON()) : (void)0;
        falseBlock != nullptr ? root["children"].push_back(falseBlock->genJSON()) : (void)0;
        return root;
    }
};

/**
 * @author gehao
 * 
 * for?????????for (expr_init; expr_condition; expr_change) {block}
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

    Expression* getInitial() const {
        return initial;
    }

    Expression* getCondition() const {
        return condition;
    }

    Expression* getChange() const {
        return change;
    }

    Block* getForBlock() const {
        return forBlock;
    }
    json genJSON() const override {
        json root;
        root["name"] = "ForStatement";
        initial != nullptr ? root["children"].push_back(initial->genJSON()) : (void)0;
        condition != nullptr ? root["children"].push_back(condition->genJSON()) : (void)0;
        change != nullptr ? root["children"].push_back(change->genJSON()) : (void)0;
        forBlock != nullptr ? root["children"].push_back(forBlock->genJSON()) : (void)0;
        return root;
    }
};

/**
 * @author gehao
 * 
 * while?????????while(expr_condition) {block} 
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

    Expression* getCondition() const {
        return condition;
    }

    Block* getWhileBlock() const {
        return whileBlock;
    }
    json genJSON() const override {
        json root;
        root["name"] = "WhileStatement";
        condition != nullptr ? root["children"].push_back(condition->genJSON()) : (void)0;
        whileBlock != nullptr ? root["children"].push_back(whileBlock->genJSON()) : (void)0;
        return root;
    }
};

/**
 * @author guoziyang
 *
 * return?????????return; return expr;
 */
class ReturnStatement : public LogicStatement {
   private:
    Type type = RETURNSTATEMENT;
    Expression* expr = nullptr;

   public:
    ReturnStatement(Expression* expr) : expr(expr) {}
    ReturnStatement() : expr(nullptr) {}
    ~ReturnStatement() {
        delete expr;
    }

    Type getType() const override {
        return this->type;
    }

    Expression* getReturnExpr() const {
        return expr;
    }

    json genJSON() const override {
        json root;
        root["name"] = "ReturnStatement";
        expr != nullptr ? root["children"].push_back(expr->genJSON()) : (void)0;
        return root;
    }
};


/**
 * @author guoziyang
 *
 * continue?????????continue;
 */
class ContinueStatement : public LogicStatement {
private:
    Type type = CONTINUESTATEMENT;

public:
    ContinueStatement() {}

    Type getType() const override {
        return this->type;
    }


    json genJSON() const override {
        json root;
        root["name"] = "ContinueStatement";
        return root;
    }
};

/**
 * @author guoziyang
 *
 * break?????????break;
 */
class BreakStatement : public LogicStatement {
private:
    Type type = BREAKSTATEMENT;

public:
    BreakStatement() {}

    Type getType() const override {
        return this->type;
    }


    json genJSON() const override {
        json root;
        root["name"] = "BreakStatement";
        return root;
    }
};

/**
 * @author guoziyang
 *
 * op?????????read (entity); print (expr); print(STRING);
 * STRING only used in print
 */

class IOStatement : public LogicStatement {
   private:
    Type type = IOSTATEMENT;
    bool isRead = false;
    std::string formatString = "";
    std::vector<Expression*>* vectorExpression = nullptr;

    void prepareString() {
        std::string rst;
        std::string::const_iterator it = formatString.begin();
        while (it != formatString.end())
        {
            char c = *it++;
            if (c == '\\' && it != formatString.end())
            {
                switch (*it++) {
                    case '\'': c = '\''; break;
                    case '\"': c = '\"'; break;
                    case '\?': c = '\?'; break;
                    case '\\': c = '\\'; break;
                    case 'a': c = '\a'; break;
                    case 'b': c = '\b'; break;
                    case 'f': c = '\f'; break;
                    case 'n': c = '\n'; break;
                    case 'r': c = '\r'; break;
                    case 't': c = '\t'; break;
                    case 'v': c = '\v'; break;
                        // all other escapes
                    default:
                        // invalid escape sequence - skip it.
                        continue;
                }
            }
            rst += c;
        }
        formatString = rst;
    }

   public:
    IOStatement(std::string formatString, std::vector<Expression*>* vectorExpression, bool isRead) : formatString(formatString), vectorExpression(vectorExpression), isRead(isRead) {
        prepareString();
    }
    IOStatement(std::string formatString) : formatString(formatString), isRead(false) {
        prepareString();
    }
    IOStatement() {}
    ~IOStatement() {
        if (vectorExpression != nullptr) {
            for (auto it = vectorExpression->begin(); it != vectorExpression->end(); ++it) {
                delete *it;
            }
            delete vectorExpression;
        }
    }

    Type getType() const override {
        return this->type;
    }

    std::vector<Expression*>* getVectorExpression() const {
        return vectorExpression;
    }

    std::string getPrintText() const {
        return formatString;
    }
    bool getIsRead() const {
        return isRead;
    }

    json genJSON() const override {
        json root;
        root["name"] = formatString != "" ? "IOStatement: " + formatString : "IOStatement";
        if (vectorExpression != nullptr) {
            for (auto it = vectorExpression->begin(); it != vectorExpression->end(); ++it) {
                root["children"].push_back((*it)->genJSON());
            }
        }
        return root;
    }
};

#endif