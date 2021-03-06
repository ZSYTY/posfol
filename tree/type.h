#ifndef __TYPE_H__
#define __TYPE_H__

enum Type {
    NODE,

    BLOCK,

    EXPRESSION,
    IDENTIFIER,
    CLASSNEWEXPRESSION,
    ARITHMETICEXPRESSION,
    BINARYOPERATOR,
    UNARYOPERATOR,
    TYPECONVERTOPERATOR,
    CLASSEXPRESSION,
    CLASSVARIABLEEXPRESSION,
    CLASSFUNCEXPRESSION,
    ASSIGNEXPRESSION,
    ENTITYEXPRESSION,

    DECLARATION,
    VARIABLEDECLARATION,
    FUNCTIONDECLARATION,
    CLASSDECLARATION,
    INTERFACEDECLARATION,
    LAMBDADECLARATION,

    STATEMENT,
    LOGICSTATEMENT,
    IFSTATEMENT,
    FORSTATEMENT,
    WHILESTATEMENT,
    RETURNSTATEMENT,
    CONTINUESTATEMENT,
    BREAKSTATEMENT,
    IOSTATEMENT,

    INT_DEFINE_TYPE,
    LONG_DEFINE_TYPE,
    FLOAT_DEFINE_TYPE,
    DOUBLE_DEFINE_TYPE,
    BOOLEAN_DEFINE_TYPE,
    CHAR_DEFINE_TYPE,
    FUNC_DEFINE_TYPE,
    VOID_DEFINE_TYPE,
    CLASS_DEFINE_TYPE,

    INT_VALUE,
    LONG_VALUE,
    FLOAT_VALUE,
    DOUBLE_VALUE,
    BOOLEAN_VALUE,
    CHAR_VALUE,
    FUNC_VALUE,
    VOID_VALUE,
    CLASS_VALUE,

    ARRAY,
    TYPE,
    NAME,
    VALUE,
    FUNCTION_REAL,
    CLASS_REAL,
    INTERFACE_REAL,

    ERROR
};

#endif