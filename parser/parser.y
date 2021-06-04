%{
//#include "token.h"
#include "../tree/node.h"
#include "../tree/type.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "lex.yy.c"
#define PARSER
Block* programBlock;
void yyerror(const char* msg) {
    printf("error from yacc: %s\n", msg);
}
%}
%union{
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
%token <val> LP RP LB RB BEG END DOT COMMA COLON MUL DIV MOD UNEQUAL NOT PLUS MINUS GE GT LE LT EQUAL AND OR ASSIGN ADD_ASSIGN SUB_ASSIGN MULTIPLE_ASSIGN DIV_ASSIGN MOD_ASSIGN SEMI ARROR FALSE TRUE PRINT BOOL_TYPE CHAR_TYPE INT_TYPE FLOAT_TYPE FUNC_TYPE VOID_TYPE READ FLOAT INT CHAR STRING ELSE FOR WHILE IF ID PUBLIC PRIVATE IMPLEMENTS NEW CLASS INTERFACE RETURN
%type <val> access_label
%type <block> program global_stmts global_stmts_nonempty class_stmts class_stmts_nonempty interface_stmts interface_stmts_nonempty stmts stmts_nonempty else_clause
%type <statement> global_stmt class_stmt interface_stmt stmt
%type <variable_declaration> id_and_initial varible_decl
%type <identifier> varible_decl_type function_decl_type literal
%type <var_decl_list> id_and_initial_list args_list args_list_nonempty
%type <id_list> id_list id_list_nonempty
%type <class_declaration> class_decl 
%type <function_declaration> construction_decl function_decl
%type <interface_declaration> interface_decl
%type <expression> expr expr0 expr1 expr2 arithmetic term factor factor_nontype_convert
%type <entity> entity entity_inner function_call
%type <expr_list> expr_list expr_list_nonempty array_entity
%type <logic_statement> logical_stmt
%type <if_statement> if_stmt
%type <while_statement> while_stmt
%type <for_statement> for_stmt
%type <return_statement> return_stmt
%type <io_stmt> io_stmt
%left PLUS MINUS
%left MUL DIV MOD
%%

program:
    global_stmts {
        programBlock = $1;
    }
;

global_stmts:
    /* empty */ {
        $$ = new Block();
    }
|   global_stmts_nonempty
;

global_stmts_nonempty:
    global_stmts_nonempty global_stmt {
        $1->getStatementList()->push_back($2);
    }
|   global_stmt {
        $$ = new Block();
        $$->getStatementList()->push_back($1);
    }
;

global_stmt:
    function_decl
|   varible_decl {puts("variable declaration");}
|   class_decl
|   interface_decl
;

varible_decl:
    varible_decl_type id_and_initial SEMI {
        $$ = $2;
        $$->setVarType($1);
    }
;

varible_decl_type:
    BOOL_TYPE {$$ = new Identifier(Type::BOOLEAN_DEFINE_TYPE);}
|   CHAR_TYPE  {$$ = new Identifier(Type::CHAR_DEFINE_TYPE); puts("char types");}
|   INT_TYPE  {$$ = new Identifier(Type::INT_DEFINE_TYPE);  puts("int types");}
|   FLOAT_TYPE  {$$ = new Identifier(Type::FLOAT_DEFINE_TYPE); }
|   FUNC_TYPE  {$$ = new Identifier(Type::FUNC_DEFINE_TYPE); }
|   VOID_TYPE {$$ = new Identifier(Type::VOID_DEFINE_TYPE); puts("void func type"); }
|   ID {$$ = new Identifier(Type::CLASS_DEFINE_TYPE, *($1));}
;

id_and_initial_list:
    id_and_initial_list COMMA id_and_initial {
        $1->push_back($3);
    }
|   id_and_initial {
        $$ = new std::vector<VariableDeclaration*>();
        $$->push_back($1);
    }
;

id_and_initial:
    ID {
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *($1)));
        //delete $1;
    }
|   ID ASSIGN CHAR {
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *($1)), new Identifier(Type::VALUE, *($3)));
        //delete $1;
        //delete $3;
    }
|   ID ASSIGN expr {
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *($1)), $3);
        //delete $1;
    }
|   ID ASSIGN LB id_list RB LP args_list RP ARROR varible_decl_type BEG stmts END {
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *($1)), new LambdaExpression($4, $7, $10, $12));
        //delete $1;
    }
|   array_entity {
        $$ = new VariableDeclaration(nullptr, (Identifier*)((*$1)[0]), new std::vector<Expression*>($1->begin() + 1, $1->end()));
    }
;

id_list:
    /* empty */ {
        $$ = new std::vector<Identifier*>();
    }
|   id_list_nonempty
;

id_list_nonempty:
    id_list_nonempty COMMA ID {
        $1->push_back(new Identifier(Type::NAME, *($3)));
        //delete $3;
    }
|   ID {
        $$ = new std::vector<Identifier*>();
        $$->push_back(new Identifier(Type::NAME, *($1)));
        //delete $1;
    }
;

args_list:
    /* empty */ {
        puts("empty args_list");
        $$ = new std::vector<VariableDeclaration*>();
    }
|   args_list_nonempty
;

args_list_nonempty:
    args_list_nonempty COMMA varible_decl_type ID {
        $1->push_back(new VariableDeclaration($3, new Identifier(Type::NAME, *($4))));
        //delete $4;
    }
|   varible_decl_type ID {
        puts("args_list_nonempty first one");
        $$ = new std::vector<VariableDeclaration*>();
        $$->push_back(new VariableDeclaration($1, new Identifier(Type::NAME, *($2))));
        //delete $2;
    }
;

class_decl:
    CLASS ID SEMI
|   CLASS ID BEG class_stmts END SEMI {
        $$ = new ClassDeclaration(new Identifier(Type::NAME, *($2)), $4);
        //delete $2;
    }
|   CLASS ID IMPLEMENTS ID BEG class_stmts END SEMI {
        $$ = new ClassDeclaration(new Identifier(Type::NAME, *($2)), new Identifier(Type::NAME, *($4)), $6);
        //delete $2;
        //delete $4;
    }
;

class_stmts:
    /* empty */ {
        $$ = new Block();
    }
|   class_stmts_nonempty {puts("class_stmts_nonempty");}
;

class_stmts_nonempty:
    class_stmts_nonempty class_stmt {
        $1->getStatementList()->push_back($2);
    }
|   class_stmt {
        $$ = new Block();
        $$->getStatementList()->push_back($1);
    }
;

class_stmt:
    access_label function_decl {$$ = $2;}
|   access_label varible_decl {$$ = $2;puts("variable declaration");}
|   access_label construction_decl {$$ = $2; puts("construction declaration");}
;

construction_decl:
    ID LP args_list RP BEG stmts END {
        $$ = new FunctionDeclaration(new Identifier(Type::NAME, *($1)), new Identifier(Type::NAME, *($1)), $3, $6);
        //delete $2;
    }
;

access_label:
    PUBLIC {puts("PUBLIC");}
|   PRIVATE {puts("PRIVATE");}
;

interface_decl:
    INTERFACE ID BEG interface_stmts END SEMI {
        $$ = new InterfaceDeclaration(new Identifier(Type::NAME, *($2)), $4);
        //delete $2;
    }
;

interface_stmts:
    /* empty */ {
        $$ = new Block();
    }
|   interface_stmts_nonempty
;

interface_stmts_nonempty:
    interface_stmts_nonempty interface_stmt {
        $1->getStatementList()->push_back($2);
    }
|   interface_stmt {
        $$ = new Block();
        $$->getStatementList()->push_back($1);
    }
;

interface_stmt:
    varible_decl_type ID LP args_list RP SEMI {
        $$ = new FunctionDeclaration($1, new Identifier(Type::NAME, *($2)), $4);
    }
;

function_decl:
    varible_decl_type ID LP args_list RP BEG stmts END {
        $$ = new FunctionDeclaration($1, new Identifier(Type::NAME, *($2)), $4, $7);
        //delete $2;
        puts("finish function declaration");
    }
;

function_decl_type:
    BOOL_TYPE {$$ = new Identifier(Type::BOOLEAN_DEFINE_TYPE); }
|   CHAR_TYPE  {$$ = new Identifier(Type::CHAR_DEFINE_TYPE); }
|   INT_TYPE  {$$ = new Identifier(Type::INT_DEFINE_TYPE); puts("int func type"); }
|   FLOAT_TYPE  {$$ = new Identifier(Type::FLOAT_DEFINE_TYPE); }
|   FUNC_TYPE  {$$ = new Identifier(Type::FUNC_DEFINE_TYPE); }
|   VOID_TYPE {$$ = new Identifier(Type::VOID_DEFINE_TYPE); puts("void func type"); }
|   ID {$$ = new Identifier(Type::CLASS_DEFINE_TYPE, *($1));}
;

stmts:
    /* empty */ {
        $$ = new Block();
    }
|   stmts_nonempty {puts("stmts_nonempty");}
;

stmts_nonempty:
    stmts_nonempty stmt {
        $1->getStatementList()->push_back($2);
    }
|   stmt {
        $$ = new Block();
        $$->getStatementList()->push_back($1);
    }
;

stmt:
    varible_decl
|   expr SEMI
|   logical_stmt
|   io_stmt
;

expr:
    entity ASSIGN expr {$$ = new AssignExpression($1, 0, $3);}
|   entity ADD_ASSIGN expr {$$ = new AssignExpression($1, 1, $3);}
|   entity SUB_ASSIGN expr {$$ = new AssignExpression($1, 2, $3);}
|   entity MULTIPLE_ASSIGN expr {$$ = new AssignExpression($1, 3, $3);}
|   entity DIV_ASSIGN expr {$$ = new AssignExpression($1, 4, $3);}
|   entity MOD_ASSIGN expr {$$ = new AssignExpression($1, 5, $3);}
|   expr0
;

expr0:
    expr0 OR expr1 {$$ = new BinaryOperator($1, 0, $3);}
|   expr1
;

expr1:
    expr1 AND expr2 {$$ = new BinaryOperator($1, 1, $3);}
|   expr2
;

expr2:
    arithmetic
|   expr2 GE arithmetic {$$ = new BinaryOperator($1, 2, $3);}
|   expr2 GT arithmetic {$$ = new BinaryOperator($1, 3, $3);}
|   expr2 LE arithmetic {$$ = new BinaryOperator($1, 4, $3);}
|   expr2 LT arithmetic {$$ = new BinaryOperator($1, 5, $3);}
|   expr2 EQUAL arithmetic {$$ = new BinaryOperator($1, 6, $3);}
|   expr2 UNEQUAL arithmetic {$$ = new BinaryOperator($1, 7, $3);}
;

arithmetic:
    arithmetic PLUS term {$$ = new BinaryOperator($1, 8, $3);}
|   arithmetic MINUS term {$$ = new BinaryOperator($1, 9, $3);}
|   term
;

term:
    term MUL factor {$$ = new BinaryOperator($1, 10, $3);}
|   term DIV factor {$$ = new BinaryOperator($1, 11, $3);}
|   term MOD factor {$$ = new BinaryOperator($1, 12, $3);}
|   factor
;

factor:
    factor_nontype_convert
|   LP varible_decl_type RP factor_nontype_convert {$$ = new TypeConvertOperator($2, $4);}
;

factor_nontype_convert:
    entity
|   function_call
|   NEW ID LP expr_list RP {
        $$ = new ClassNewExpression(new Identifier(Type::NAME, *($2)), $4);
    }
|   literal
|   LP expr RP {$$ = $2;}
|   NOT factor {$$ = new UnaryOperator(1, $2);}
|   MINUS factor {$$ = new UnaryOperator(0, $2);}
;

entity:
    ID {
        $$ = new Entity(new Identifier(Type::NAME, *($1))); 
        //delete $1;
    }
|   entity_inner DOT ID {
        $$ = new Entity($1, new Identifier(Type::NAME, *($3))); 
        //delete $3;
    }
|   entity_inner LB expr RB {$$ = new Entity($1, $3);}
;

entity_inner:
    ID {
        $$ = new Entity(new Identifier(Type::NAME, *($1))); 
        //delete $1;
    }
|   entity_inner DOT ID {
    $$ = new Entity($1, new Identifier(Type::NAME, *($3))); 
        //delete $3;
    }
|   entity_inner LB expr RB {$$ = new Entity($1, $3);}
|   entity_inner LP expr_list RP {$$ = new Entity($1, $3);}
;

array_entity:
    ID LB expr RB {
        $$ = new std::vector<Expression*>();
        $$->push_back(new Identifier(Type::NAME, *($1)));
        $$->push_back($3);
        //delete $1;
    }
|   array_entity LB expr RB {
        $1->push_back($3);
    }
;

function_call:
    entity_inner LP expr_list RP {
        {$$ = new Entity($1, $3);}
    }
;

literal:
    INT {
        $$ = new Identifier(Type::VALUE, *($1)); 
        //delete $1;
    }
|   FLOAT {
        $$ = new Identifier(Type::VALUE, *($1)); 
        //delete $1;
    }
|   CHAR {
        $$ = new Identifier(Type::VALUE, *($1)); 
        //delete $1;
    }
|   TRUE {
        $$ = new Identifier(Type::VALUE, *($1)); 
        //delete $1;
    }
|   FALSE {
        $$ = new Identifier(Type::VALUE, *($1)); 
        //delete $1;
    }
;

expr_list:
    /* empty */ {
        $$ = new std::vector<Expression*>();
    }
|   expr_list_nonempty
;

expr_list_nonempty:
    expr_list_nonempty COMMA expr {
        $1->push_back($3);
    }
|   expr {
        $$ = new std::vector<Expression*>();
        $$->push_back($1);
    }
;


logical_stmt:
    if_stmt
|   while_stmt
|   for_stmt
|   return_stmt
;

if_stmt:
    IF LP expr RP BEG stmts END else_clause {
        $$ = new IfStatement($3, $6, $8);
    }
;

else_clause:
    ELSE BEG stmts END {
        $$ = $3;
    }
|   /* empty */ {
        $$ = nullptr;
    }
;

while_stmt:
    WHILE LP expr RP BEG stmts END {
        $$ = new WhileStatement($3, $6);
    }
;

for_stmt:
    FOR LP expr SEMI expr SEMI expr RP BEG stmts END {
        $$ = new ForStatement($3, $5, $7, $10);
    }
;

return_stmt:
    RETURN expr SEMI {
        $$ = new ReturnStatement($2);
    }
|   RETURN SEMI {
        $$ = new ReturnStatement();
    }
;

io_stmt:
    READ LP entity RP SEMI {
        $$ = new IOStatement($3);
    }
|   PRINT LP expr RP SEMI {
        $$ = new IOStatement($3);
    }
|   PRINT LP STRING RP SEMI {
        $$ = new IOStatement(*($3));
    }
;

%%

Block* buildTree() {
    yyparse();
    return programBlock;
}