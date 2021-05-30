%{
//#include "token.h"
#include "../semantic/node.h"
#include <stdio.h>
#include "lex.yy.c"
#define PARSER
Block* programBlock;
void yyerror(const char* msg) {
    if(yylval.t) printf("%s at line %d.\n", msg, yylval.t->lineNumber);
    else printf("%s\n", msg);
}
}
%}
%union{
    struct TreeNode* t;
}
%token <t> LP RP LB RB BEG END DOT COMMA COLON MUL DIV MOD UNEQUAL NOT PLUS MINUS GE GT LE LT EQUAL AND OR ASSIGN ADD_ASSIGN MINUS_ASSIGN MULTIPLE_ASSIGN DIV_ASSIGN MOD_ASSIGN SEMI FALSE TRUE PRINT BOOL_TYPE CHAR_TYPE INT_TYPE FLOAT_TYPE FUNC_TYPE READ FLOAT INT CHAR ELSE FOR WHILE IF ID PUBLIC PRIVATE IMPLEMENTS NEW CLASS INTERFACE
%type <t>  program global_stmts global_stmts_nonempty global_stmt varible_decl varible_decl_type id_and_initial_list id_and_initial id_list id_list_nonempty args_list args_list_nonempty class_decl class_stmts class_stmts_nonempty class_stmt construction_decl access_label interface_decl interface_stmts interface_stmts_nonempty interface_stmt function_decl function_decl_type stmts stmts_nonempty stmt expr arithmetic term factor factor_nontype_convert entity object_member_entity array_entity function_call literal assign_expr logical_stmt if_stmt else_clause while_stmt for_stmt
%left PLUS MINUS
%left MUL DIV MOD
%%

program: 
    global_stmts 
;

global_stmts:
    /* empty */
|   global_stmts_nonempty
;

global_stmts_nonempty:
    global_stmts_nonempty global_stmt {
        $1->statements->push_back(shared_ptr<Statement>($2));
    }
|   global_stmt {
        $$ = new Block(); $$->statements->push_back(shared_ptr<Statement>($1));
    }
;

global_stmt:
    varible_decl
|   class_decl
|   interface_decl
|   function_decl
;

varible_decl:
    varible_decl_type id_and_initial_list SEMI
;

varible_decl_type:
    BOOL_TYPE
|   CHAR_TYPE
|   INT_TYPE
|   FLOAT_TYPE
|   FUNC_TYPE
;

id_and_initial_list:
    id_and_initial_list COMMA id_and_initial
|   id_and_initial
;

id_and_initial:
    ID
|   ID ASSIGN CHAR
|   ID ASSIGN expr
|   ID ASSIGN LP id_list RP LB args_list RB BEG stmts END
|   array_entity
;

id_list:
    /* empty */
|   id_list_nonempty
;

id_list_nonempty:
    id_list_nonempty COMMA ID
|   ID
;

args_list:
    /* empty */
|   args_list_nonempty
;

args_list_nonempty:
    args_list_nonempty COMMA varible_decl_type ID
|   varible_decl_type ID
;

class_decl:
    CLASS ID BEG class_stmts END
|   CLASS ID IMPLEMENTS id_list BEG class_stmts END
;

class_stmts:
    /* empty */
|   class_stmts_nonempty
;

class_stmts_nonempty:
    class_stmts_nonempty class_stmt
|   class_stmt
;

class_stmt:
    access_label varible_decl
|   access_label function_decl
|   access_label construction_decl
;

construction_decl:
    access_label ID LP args_list RP BEG stmts END
;

access_label:
    PUBLIC
|   PRIVATE
;

interface_decl:
    INTERFACE ID BEG interface_stmts END
;

interface_stmts:
    /* empty */
|   interface_stmts_nonempty
;

interface_stmts_nonempty:
    interface_stmts_nonempty interface_stmt
|   interface_stmt
;

interface_stmt:
    function_decl
;

function_decl:
    function_decl_type ID LP args_list RP BEG stmts END
;

function_decl_type:
    BOOL_TYPE
|   CHAR_TYPE
|   INT_TYPE
|   FLOAT_TYPE
|   FUNC_TYPE
|   VOID_TYPE
;

stmts:
    /* empty */
|   stmts_nonempty
;

stmts_nonempty:
    stmts_nonempty stmt
|   stmt
;

stmt:
    varible_decl
|   expr SEMI
|   logical_stmt
;

expr:
    arithmetic
|   expr GE arithmetic
|   expr GT arithmetic
|   expr LE arithmetic
|   expr LT arithmetic
|   expr EQUAL arithmetic
|   expr UNEQUAL arithmetic
;

arithmetic:
    assign_expr
|   arithmetic PLUS term
|   arithmetic MINUS term
|   term
;

term:
    term MUL factor
|   term DIV factor
|   term MOD factor
|   factor
;

factor:
    factor_nontype_convert
|   LP varible_decl_type RP factor_nontype_convert
;

factor_nontype_convert:
    entity
|   function_call
|   system_function LP id_list RP
|   literal
|   LP expr RP
|   NOT factor
|   MINUS factor
;

entity:
    ID
|   object_member_entity
|   array_entity
;

object_member_entity:
    ID DOT ID
|   object_member_entity DOT ID
;

array_entity:
    ID LB expr RB
|   array_entity LB expr RB
;

function_call:
    entity LP id_list RP
|   function_call LP id_list RP
;

literal:
    INT
|   FLOAT
|   CHAR
|   TRUE
|   FALSE
;

assign_expr:
    entity ASSIGN expr
|   entity ADD_ASSIGN expr
|   entity SUB_ASSIGN expr
|   entity MULTIPLE_ASSIGN expr
|   entity DIV_ASSIGN expr
|   entity MOD_ASSIGN expr
;

logical_stmt:
    if_stmt
|   while_stmt
|   for_stmt
;

if_stmt:
    IF LP expr RP BEG stmts END else_clause
;

else_clause:
    ELSE BEG stmts END
|   /* empty */
;

while_stmt:
    WHILE LP expr RP BEG stmts END
;

for_stmt:
    FOR LP expr SEMI expr SEMI expr RP BEG stmts END
;

%%

pTNode buildTree() {
    yyparse();
    return p;
}