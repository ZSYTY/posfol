%option noyywrap
%{
#include <math.h>
#include <string.h>
#include "y.tab.h"
#include <stdio.h>
#include "tree.h"
#include "token.h"
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
"(" {return LP;}
")" {return RP;}
"[" {return LB;}
"]" {return RB;}
"{" {return BEG;}
"}" {return END;}
"." {return DOT;}
"," {return COMMA;}
":" {return COLON;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}
"!=" {return UNEQUAL;}
"!" {return NOT;}
"+" {return PLUS;}
"-" {return MINUS;}
">=" {return GE;}
">" {return GT;}
"<=" {return LE;}
"<" {return LT;}
"==" {return EQUAL;}
"&&" {return AND;}
"||" {return OR;}
"=" {return ASSIGN;}
"+=" {return ADD_ASSIGN;}
"-=" {return MINUS_ASSIGN;}
"*=" {return MULTIPLE_ASSIGN;}
"/=" {return DIV_ASSIGN;}
"%=" {return MOD_ASSIGN;}
";" {return SEMI;}
{FALSE} {yylval.val = yytext; return FALSE;}
{TRUE} {yylval.val = yytext; return TRUE;}
{PRINT} {return PRINT;}
{BOOL_TYPE} {return BOOL_TYPE;}
{CHAR_TYPE} {return CHAR_TYPE;}
{INT_TYPE} {return INT_TYPE;}
{FLOAT_TYPE} {return FLOAT_TYPE;}
{FUNC_TYPE} {return FUNC_TYPE;}
{READ} {return READ;}
{FLOAT} {
    yylval.val = yytext;
    return FLOAT;
}
{INT} {
    yylval.val = yytext;
    return INT;
}
{CHAR} {
    std::string val(1, yytext[1]);
    yylval.val = val;
    return CHAR;
}
{ELSE} {return ELSE;}
{FOR} {return FOR;}
{WHILE} {return WHILE;}
{IF} {return IF;}
{ID} {yylval.valString = yytext; return ID;}
{PUBLIC} { return PUBLIC;}
{PRIVATE} { return PRIVATE;}
{IMPLEMENTS} { return IMPLEMENTS;}
{NEW} { return NEW;}
{CLASS} { return CLASS;}
{INTERFACE} { return INTERFACE;}
<<EOF>> {return -1;}
. {lex_error("Unrecognized character", curLineNum);}

%%
void lex_error(char *msg, int line) {
    printf("Unrecognized character at line %d\n\n", curLineNum);
}