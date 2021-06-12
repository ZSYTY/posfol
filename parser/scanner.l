%option noyywrap
%{
#include <cmath>
#include <cstring>
#include <cstdio>
#include "y.tab.hpp"
#include <cstdio>
#include "token.h"
int curLineNum = 1;

void lex_error(char*, int);
int yylex();
%}

FALSE false
TRUE true
PRINT print
BOOL_TYPE bool
CHAR_TYPE char
INT_TYPE int
FLOAT_TYPE float
FUNC_TYPE func
VOID_TYPE void
READ read
INT [0-9]+
FLOAT [0-9]+(".")[0-9]+
CHAR (\'.\')|(\'\\.\')
STRING \"[^"]*\"
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
RETURN return
CONTINUE continue
BREAK break

%%
[\n] {++curLineNum;}
[ \t\r\a]+ {};
"//"[^\n]* {};
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" {};
"(" {return LP;}
")" {return RP;}
"[" {return LB;}
"]" {return RB;}
"{" {return BEG;}
"}" {return END;}
"." {return DOT;}
"->" {return ARROR;}
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
"-=" {return SUB_ASSIGN;}
"*=" {return MULTIPLE_ASSIGN;}
"/=" {return DIV_ASSIGN;}
"%=" {return MOD_ASSIGN;}
";" {return SEMI;}
{FALSE} {yylval.val = new std::string(yytext); return FALSE;}
{TRUE} {yylval.val = new std::string(yytext); return TRUE;}
{PRINT} {return PRINT;}
{BOOL_TYPE} {return BOOL_TYPE;}
{CHAR_TYPE} {return CHAR_TYPE;}
{INT_TYPE} {return INT_TYPE;}
{FLOAT_TYPE} {return FLOAT_TYPE;}
{FUNC_TYPE} {return FUNC_TYPE;}
{VOID_TYPE} {return VOID_TYPE;}
{READ} {return READ;}
{FLOAT} {
    yylval.val = new std::string(yytext);
    return FLOAT;
}
{INT} {
    yylval.val = new std::string(yytext);
    return INT;
}
{CHAR} {
    printf("char text: %s\n", yytext);
    if (yytext[1] != '\\') {
        std::string val(1, yytext[1]);
        yylval.val = new std::string(val);
    } else {
        if (yytext[2] >= '0' && yytext[2] <= '9') {
            yylval.val = new std::string(1, yytext[2] - '0');
        } else if (yytext[2] == 'a') {
            yylval.val = new std::string(1, '\a');
        } else if (yytext[2] == 'b') {
            yylval.val = new std::string(1, '\b');
        } else if (yytext[2] == 'f') {
            yylval.val = new std::string(1, '\f');
        } else if (yytext[2] == 'n') {
            yylval.val = new std::string(1, '\n');
        } else if (yytext[2] == 'r') {
            yylval.val = new std::string(1, '\r');
        } else if (yytext[2] == 't') {
            yylval.val = new std::string(1, '\t');
        } else if (yytext[2] == 'v') {
            yylval.val = new std::string(1, '\v');
        } else if (yytext[2] == '\'') {
            yylval.val = new std::string(1, '\'');
        } else if (yytext[2] == '\"') {
            yylval.val = new std::string(1, '\"');
        } else if (yytext[2] == '\\') {
            yylval.val = new std::string(1, '\\');
        }
    }
    return CHAR;
}
{STRING} {
    std::string string_yy(yytext);
    size_t start_pos = 0;
    std::string from = "\\\\";
    std::string to = "\\";
    while((start_pos = string_yy.find(from, start_pos)) != std::string::npos) {
        string_yy.replace(start_pos, std::string(from).length(), to);
        start_pos += to.length();
    }
    yylval.val = new std::string(string_yy.begin() + 1, string_yy.end() - 1);
    return STRING;
}
{ELSE} {return ELSE;}
{FOR} {return FOR;}
{WHILE} {return WHILE;}
{IF} {return IF;}
{PUBLIC} { return PUBLIC;}
{PRIVATE} { return PRIVATE;}
{IMPLEMENTS} { return IMPLEMENTS;}
{NEW} { puts("scan new"); return NEW;}
{CLASS} { return CLASS;}
{INTERFACE} { return INTERFACE;}
{RETURN} {return RETURN;}
{CONTINUE} {return CONTINUE;}
{BREAK} {return BREAK;}
{ID} {yylval.val = new std::string(yytext); return ID;}
<<EOF>> {return -1;}
. {lex_error("Unrecognized character", curLineNum);}

%%
void lex_error(char *msg, int line) {
    printf("Unrecognized character at line %d\n\n", curLineNum);
}