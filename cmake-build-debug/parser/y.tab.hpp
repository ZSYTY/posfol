/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LP = 258,
     RP = 259,
     LB = 260,
     RB = 261,
     BEG = 262,
     END = 263,
     DOT = 264,
     COMMA = 265,
     COLON = 266,
     MUL = 267,
     DIV = 268,
     MOD = 269,
     UNEQUAL = 270,
     NOT = 271,
     PLUS = 272,
     MINUS = 273,
     GE = 274,
     GT = 275,
     LE = 276,
     LT = 277,
     EQUAL = 278,
     AND = 279,
     OR = 280,
     ASSIGN = 281,
     ADD_ASSIGN = 282,
     SUB_ASSIGN = 283,
     MULTIPLE_ASSIGN = 284,
     DIV_ASSIGN = 285,
     MOD_ASSIGN = 286,
     SEMI = 287,
     ARROR = 288,
     FALSE = 289,
     TRUE = 290,
     PRINT = 291,
     BOOL_TYPE = 292,
     CHAR_TYPE = 293,
     INT_TYPE = 294,
     FLOAT_TYPE = 295,
     FUNC_TYPE = 296,
     VOID_TYPE = 297,
     READ = 298,
     FLOAT = 299,
     INT = 300,
     CHAR = 301,
     STRING = 302,
     ELSE = 303,
     FOR = 304,
     WHILE = 305,
     IF = 306,
     ID = 307,
     PUBLIC = 308,
     PRIVATE = 309,
     IMPLEMENTS = 310,
     NEW = 311,
     CLASS = 312,
     INTERFACE = 313,
     RETURN = 314
   };
#endif
/* Tokens.  */
#define LP 258
#define RP 259
#define LB 260
#define RB 261
#define BEG 262
#define END 263
#define DOT 264
#define COMMA 265
#define COLON 266
#define MUL 267
#define DIV 268
#define MOD 269
#define UNEQUAL 270
#define NOT 271
#define PLUS 272
#define MINUS 273
#define GE 274
#define GT 275
#define LE 276
#define LT 277
#define EQUAL 278
#define AND 279
#define OR 280
#define ASSIGN 281
#define ADD_ASSIGN 282
#define SUB_ASSIGN 283
#define MULTIPLE_ASSIGN 284
#define DIV_ASSIGN 285
#define MOD_ASSIGN 286
#define SEMI 287
#define ARROR 288
#define FALSE 289
#define TRUE 290
#define PRINT 291
#define BOOL_TYPE 292
#define CHAR_TYPE 293
#define INT_TYPE 294
#define FLOAT_TYPE 295
#define FUNC_TYPE 296
#define VOID_TYPE 297
#define READ 298
#define FLOAT 299
#define INT 300
#define CHAR 301
#define STRING 302
#define ELSE 303
#define FOR 304
#define WHILE 305
#define IF 306
#define ID 307
#define PUBLIC 308
#define PRIVATE 309
#define IMPLEMENTS 310
#define NEW 311
#define CLASS 312
#define INTERFACE 313
#define RETURN 314




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
{
    std::string* val;
    Node* node;
    Block* block;
    Statement* statement;
    Declaration* declaration;
    Entity* entity;
    VariableDeclaration* variable_declaration;
    ClassDeclaration* class_declaration;
    FunctionDeclaration* function_declaration;
    InterfaceDeclaration* interface_declaration;
    Identifier* identifier;
    Expression* expression;
    LogicStatement* logic_statement;
    IfStatement* if_statement;
    WhileStatement* while_statement;
    ForStatement* for_statement;
    ReturnStatement* return_statement;
    IOStatement* io_stmt;
    std::vector<Identifier*>* id_list;
    std::vector<VariableDeclaration*>* var_decl_list;
    std::vector<Expression*>* expr_list;
}
/* Line 1529 of yacc.c.  */
#line 191 "y.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

