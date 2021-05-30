%option noyywrap
%{
#include <math.h>
#include <string.h>
#include "y.tab.h"
#include <stdio.h>
#include "tree.h"
#include "token.h"
#define SETLVAL(x) yylval.t = newNode(token_names[x], curLineNum, NULL, 0)
int curLineNum = 1;

void lex_error(char*, int);
int yylex();
%}

FALSE false
TRUE true
PRINT print
BOOL_TYPE bool
CHAR_TYPE CHAR
INT_TYPE int
FLOAT_TYPE float
FUNC_TYPE func
VOID_TYPE void
READ read
INT [0-9]+
FLOAT [0-9]+(".")[0-9]+
CHAR \'[.]\'
ELSE else
FOR for
WHILE while
IF if
ID ([a-zA-Z][_a-zA-Z0-9]*)
PUBLIC public
PRIVATE private
IMPLEMENTS implements
NEW new
CLASS class
INTERFACE interface


%%
[\n] {++curLineNum;}
[ \t\r\a]+ {};
"(" {SETLVAL(T_LP); return LP;}
")" {SETLVAL(T_RP); return RP;}
"[" {SETLVAL(T_LB); return LB;}
"]" {SETLVAL(T_RB); return RB;}
"{" {SETLVAL(T_BEG); return BEG;}
"}" {SETLVAL(T_END); return END;}
"." {SETLVAL(T_DOT); return DOT;}
"," {SETLVAL(T_COMMA); return COMMA;}
":" {SETLVAL(T_COLON); return COLON;}
"*" {SETLVAL(T_MUL); return MUL;}
"/" {SETLVAL(T_DIV); return DIV;}
"%" {SETLVAL(T_MOD); return MOD;}
"!=" {SETLVAL(T_UNEQUAL); return UNEQUAL;}
"!" {SETLVAL(T_NOT); return NOT;}
"+" {SETLVAL(T_PLUS); return PLUS;}
"-" {SETLVAL(T_MINUS); return MINUS;}
">=" {SETLVAL(T_GE); return GE;}
">" {SETLVAL(T_GT); return GT;}
"<=" {SETLVAL(T_LE); return LE;}
"<" {SETLVAL(T_LT); return LT;}
"==" {SETLVAL(T_EQUAL); return EQUAL;}
"&&" {SETLVAL(T_AND); return AND;}
"||" {SETLVAL(T_OR); return OR;}
"=" {SETLVAL(T_ASSIGN); return ASSIGN;}
"+=" {SETLVAL(T_ADD_ASSIGN); return ADD_ASSIGN;}
"-=" {SETLVAL(T_MINUS_ASSIGN); return MINUS_ASSIGN;}
"*=" {SETLVAL(T_MULTIPLE_ASSIGN); return MULTIPLE_ASSIGN;}
"/=" {SETLVAL(T_DIV_ASSIGN); return DIV_ASSIGN;}
"%=" {SETLVAL(T_MOD_ASSIGN); return MOD_ASSIGN;}
";" {SETLVAL(T_SEMI); return SEMI;}
{FALSE} {int val = 0; yylval.t = newNode("BOOLEAN", curLineNum, (void*)&val, 0); return FALSE;}
{TRUE} {int val = 1; yylval.t = newNode("BOOLEAN", curLineNum, (void*)&val, 0); return TRUE;}
{PRINT} {SETLVAL(T_PRINT); return PRINT;}
{BOOL_TYPE} {SETLVAL(T_BOOL_TYPE); return BOOL_TYPE;}
{CHAR_TYPE} {SETLVAL(T_CHAR_TYPE); return CHAR_TYPE;}
{INT_TYPE} {SETLVAL(T_INT_TYPE); return INT_TYPE;}
{FLOAT_TYPE} {SETLVAL(T_FLOAT_TYPE); return FLOAT_TYPE;}
{FUNC_TYPE} {SETLVAL(T_FUNC_TYPE); return FUNC_TYPE;}
{READ} {SETLVAL(T_READ); return READ;}
{FLOAT} {
    double vald = atof(yytext);
    yylval.t = newNode("FLOAT", curLineNum, (void*)&vald, 1);
    return FLOAT;
}
{INT} {
    int val = atoi(yytext);
    yylval.t = newNode("INT", curLineNum, (void*)&val, 0);
    return INT;
}
{CHAR} {
    yylval.t = newNode("CHAR", curLineNum, (void*)&yytext[1], 2);
    return CHAR;
}
{ELSE} {SETLVAL(T_ELSE); return ELSE;}
{FOR} {SETLVAL(T_FOR); return FOR;}
{WHILE} {SETLVAL(T_WHILE); return WHILE;}
{IF} {SETLVAL(T_IF); return IF;}
{ID} {yylval.t = newNode("ID", curLineNum, yytext, 3); return ID;}
{PUBLIC} { SETLVAL(T_PUBLIC) return PUBLIC;}
{PRIVATE} { SETLVAL(T_PRIVATE) return PRIVATE;}
{IMPLEMENTS} { SETLVAL(T_IMPLEMENTS) return IMPLEMENTS;}
{NEW} { SETLVAL(T_NEW) return NEW;}
{CLASS} { SETLVAL(T_CLASS) return CLASS;}
{INTERFACE} { SETLVAL(T_INTERFACE) return INTERFACE;}
<<EOF>> {return -1;}
. {lex_error("Unrecognized character", curLineNum);}

%%
void lex_error(char *msg, int line) {
    printf("Unrecognized character at line %d\n\n", curLineNum);
}