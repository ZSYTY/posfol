%{
//#include "token.h"
#include "../tree/node.h"
#include "../tree/type.h"
#include <stdio.h>
#include <vector>
#include <string>
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
    std::string val;
    Node* node;
    Block* block;
    Entity* entity;
    std::vector<Identifier*>* id_list;
    std::vector<VariableDeclaration*>* var_decl_list;
    std::vector<Expression*>* expr_list;
}
%token <t> LP RP LB RB BEG END DOT COMMA COLON MUL DIV MOD UNEQUAL NOT PLUS MINUS GE GT LE LT EQUAL AND OR ASSIGN ADD_ASSIGN SUB_ASSIGN MULTIPLE_ASSIGN DIV_ASSIGN MOD_ASSIGN SEMI FALSE TRUE PRINT BOOL_TYPE CHAR_TYPE INT_TYPE FLOAT_TYPE FUNC_TYPE VOID_TYPE READ FLOAT INT CHAR ELSE FOR WHILE IF ID PUBLIC PRIVATE IMPLEMENTS NEW CLASS INTERFACE
%type <t> program global_stmts global_stmts_nonempty global_stmt varible_decl varible_decl_type id_and_initial_list id_and_initial id_list id_list_nonempty args_list args_list_nonempty class_decl class_stmts class_stmts_nonempty class_stmt construction_decl access_label interface_decl interface_stmts interface_stmts_nonempty interface_stmt function_decl function_decl_type stmts stmts_nonempty stmt expr expr0 expr1 expr2 arithmetic term factor factor_nontype_convert entity entity_inner array_entity function_call literal expr_list expr_list_nonempty logical_stmt if_stmt else_clause while_stmt for_stmt
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
        $1->statements->push_back($2);
    }
|   global_stmt {
        $$ = new Block();
        $$->statements->push_back($1);
    }
;

global_stmt:
    varible_decl
|   class_decl
|   interface_decl
|   function_decl
;

varible_decl:
    varible_decl_type id_and_initial_list SEMI {
        $$ = $2;
        for (auto it = $$->begin(); it != $$->end(); ++it) {
            it->setVarType($1);
        }
    }
;

varible_decl_type:
    BOOL_TYPE {$$ = new Identifier(Type::BOOLEAN); }
|   CHAR_TYPE  {$$ = new Identifier(Type::CHAR); }
|   INT_TYPE  {$$ = new Identifier(Type::INT); }
|   FLOAT_TYPE  {$$ = new Identifier(Type::FLOAT); }
|   FUNC_TYPE  {$$ = new Identifier(Type::FUNC); }
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
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, $1));
    }
|   ID ASSIGN CHAR {
        std::string str(1, $3);
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, $1), new Identifier(Type::VALUE, str));
    }
|   ID ASSIGN expr {
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, $1), $3);
    }
|   ID ASSIGN LB id_list RB LP args_list RP BEG stmts END {
        $$ = new VariableDeclaration(nullptr, new Identifier(Type::NAME, $1), new LambdaExpression($4, $7, $10));
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
        $1->push_back(new Identifier(Type::NAME, $3));
    }
|   ID {
        $$ = new std::vector<Identifier*>();
        $$->push_back(new Identifier(Type::NAME, $1));
    }
;

args_list:
    /* empty */ {
        $$ = new std::vector<VariableDeclaration*>();
    }
|   args_list_nonempty
;

args_list_nonempty:
    args_list_nonempty COMMA varible_decl_type ID {
        $1->push_back(new VariableDeclaration($3, new Identifier(Type::NAME, $3)));
    }
|   varible_decl_type ID {
        $$ = new std::vector<VariableDeclaration*>();
        $$->push_back(new VariableDeclaration($1, new Identifier(Type::NAME, $2)));
    }
;

class_decl:
    CLASS ID SEMI
|   CLASS ID BEG class_stmts END SEMI {
        $$ = new ClassDeclaration(new Identifier(Type::NAME, $2), $4);
    }
|   CLASS ID IMPLEMENTS ID BEG class_stmts END SEMI {
        $$ = new ClassDeclaration(new Identifier(Type::NAME, $2), new Identifier(Type::NAME, $4), $6);
    }
;

class_stmts:
    /* empty */ {
        $$ = new Block();
    }
|   class_stmts_nonempty
;

class_stmts_nonempty:
    class_stmts_nonempty class_stmt {
        $1->statements->push_back($2);
    }
|   class_stmt {
        $$ = new Block();
        $$->statements->push_back($1);
    }
;

class_stmt:
    access_label varible_decl {$$ = $2;}
|   access_label function_decl {$$ = $2;}
|   access_label construction_decl {$$ = $2;}
;

construction_decl:
    access_label ID LP args_list RP BEG stmts END {
        $$ = new FunctionDeclaration(new Identifier(Type::NAME, $2), new Identifier(Type::NAME, $2), $4, $7);
    }
;

access_label:
    PUBLIC
|   PRIVATE
;

interface_decl:
    INTERFACE ID BEG interface_stmts END {
        $$ = new InterfaceDeclaration(new Identifier(Type::NAME, $2), $4);
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
        $1->statements->push_back($2);
    }
|   interface_stmt {
        $$ = new Block();
        $$->statements->push_back($1);
    }
;

interface_stmt:
    function_decl
;

function_decl:
    function_decl_type ID LP args_list RP BEG stmts END {
        $$ = new FunctionDeclaration($1, new Identifier(Type::NAME, $2), $4, $7);
    }
;

function_decl_type:
    BOOL_TYPE {$$ = new Identifier(Type::BOOLEAN); }
|   CHAR_TYPE  {$$ = new Identifier(Type::CHAR); }
|   INT_TYPE  {$$ = new Identifier(Type::INT); }
|   FLOAT_TYPE  {$$ = new Identifier(Type::FLOAT); }
|   FUNC_TYPE  {$$ = new Identifier(Type::FUNC); }
|   VOID_TYPE {$$ = new Identifier(Type::VOID); }
;

stmts:
    /* empty */ {
        $$ = new Block();
    }
|   stmts_nonempty
;

stmts_nonempty:
    stmts_nonempty stmt {
        $1->statements->push_back($2);
    }
|   stmt {
        $$ = new Block();
        $$->statements->push_back($1);
    }
;

stmt:
    varible_decl
|   expr SEMI
|   logical_stmt
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
|   literal
|   LP expr RP {$$ = $2;}
|   NOT factor {$$ = new UnaryOperator(1, $2);}
|   MINUS factor {$$ = new UnaryOperator(0, $2);}
;

entity:
    ID {$$ = new Entity(new Identifier(Type::NAME, $1));}
|   entity_inner DOT ID {$$ = new Entity($1, new Identifier(Type::NAME, $3));}
|   entity_inner LB expr RB {$$ = new Entity($1, $3);}
;

entity_inner:
    ID {$$ = new Entity(new Identifier(Type::NAME, $1));}
|   entity_inner DOT ID {$$ = new Entity($1, new Identifier(Type::NAME, $3));}
|   entity_inner LB expr RB {$$ = new Entity($1, $3);}
|   entity_inner LP expr_list RP {$$ = new Entity($1, $3);}
;

array_entity:
    ID LB expr RB {
        $$ = new std::vector<Expression*>();
        $$->push_back(new Identifier(Type::NAME, $1));
        $$->push_back($3);
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
    INT {$$ = new Identifier(Type::VALUE, $1);}
|   FLOAT {$$ = new Identifier(Type::VALUE, $1);}
|   CHAR {$$ = new Identifier(Type::VALUE, $1);}
|   TRUE {$$ = new Identifier(Type::VALUE, $1);}
|   FALSE {$$ = new Identifier(Type::VALUE, $1);}
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

%%

pTNode buildTree() {
    yyparse();
    return p;
}