#ifndef __TYPE_H__
#define __TYPE_H__

enum Type {
    NODE,

    BLOCK,

    EXPRESSION,
    IDENTIFIER,
    ARITHMETICEXPRESSION,
    BINARYOPERATOR,
    ASSIGNEXPRESSION,
    VARIABLEASSIGN,
    ARRAYASSIGN,
    CLASSASSIGN,
    FUNCCALLEXPRESSION,

    DECLARATION,
    VARIABLEDECLARATION,
    FUNCTIONDECLARATION,
    CLASSDECLARATION,

    STATEMENT,
    LOGICSTATEMENT,
    IFSTATEMENT,
    FORSTATEMENT,
    WHILESTATEMENT,

    INT,
    LONG,
    FLOAT,
    DOUBLE,
    BOOLEAN,
    CHAR,
    ARRAY,
    CLASS,
    TYPE,

    ERROR
};

#endif