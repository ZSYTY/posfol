//
// Created by GuoZiYang on 2021/5/26.
//

#ifndef POSFOL_TOKEN_H
#define POSFOL_TOKEN_H
#include <cstdio>
typedef enum
{
    T_LP = 0,
    T_RP,
    T_LB,
    T_RB,
    T_DOT,
    T_COMMA,
    T_COLON,
    T_MUL,
    T_DIV,
    T_UNEQUAL,
    T_NOT,
    T_PLUS,
    T_MINUS,
    T_GE,
    T_GT,
    T_LE,
    T_LT,
    T_EQUAL,
    T_ASSIGN,
    T_MOD,
    T_SEMI,
    T_FALSE,
    T_TRUE,
    T_PRINT,
    T_BOOL_TYPE,
    T_STRING_TYPE,
    T_INT_TYPE,
    T_FLOAT_TYPE,
    T_FUNC_TYPE,
    T_READ,
    T_INT,
    T_FLOAT,
    T_STRING,
    T_AND,
    T_BEG,
    T_ELSE,
    T_END,
    T_FOR,
    T_WHILE,
    T_IF,
    T_OR,
    T_ID,
    T_ADD_ASSIGN,
    T_MINUS_ASSIGN,
    T_MULTIPLE_ASSIGN,
    T_DIV_ASSIGN,
    T_MOD_ASSIGN,
    T_PUBLIC,
    T_PRIVATE,
    T_IMPLEMENTS,
    T_NEW,
    T_CLASS,
    T_INTERFACE
} TokenType;

const char *token_names[] = {
        "LP",
        "RP",
        "LB",
        "RB",
        "DOT",
        "COMMA",
        "COLON",
        "MUL",
        "DIV",
        "UNEQUAL",
        "NOT",
        "PLUS",
        "MINUS",
        "GE",
        "GT",
        "LE",
        "LT",
        "EQUAL",
        "ASSIGN",
        "MOD",
        "SEMI",
        "FALSE",
        "TRUE",
        "PRINT",
        "BOOL_TYPE",
        "STRING_TYPE",
        "INT_TYPE",
        "FLOAT_TYPE",
        "FUNC_TYPE",
        "READ",
        "INT",
        "FLOAT",
        "STRING",
        "AND",
        "BEG",
        "ELSE",
        "END",
        "FOR",
        "WHILE",
        "IF",
        "OR",
        "ID",
        "ADD_ASSIGN",
        "MINUS_ASSIGN",
        "MULTIPLE_ASSIGN",
        "DIV_ASSIGN",
<<<<<<< HEAD
        "MOD_ASSIGN"
=======
        "MOD_ASSIGN",
>>>>>>> feature/codegen
        "PUBLIC",
        "PRIVATE",
        "IMPLEMENTS",
        "NEW",
        "CLASS",
        "INTERFACE"};

void print_token(int token)
{
    printf("%s\n", token_names[token]);
}

#endif //POSFOL_TOKEN_H
