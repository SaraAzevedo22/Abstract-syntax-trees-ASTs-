// Tokens
%token 
  INT  
  PLUS
  MINUS
  TIMES
  DIV
  REST
  VAR 
  STRING
  GT
  LT
  GET
  LLET
  IG
  EQ
  DIF
  PA
  PF
  CA
  CF
  ACAB
  EC
  VIRG
  FN
  MAIN
  IF
  ELSE
  WHILE
  PRINTLN
  READLINE
  LET


// Operator associativity & precedence
%left PLUS
%left MINUS
%left TIMES
%left DIV
%left REST

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue; 
  BoolExpr* boolexp;
  char* charValue;
  CmdLista* list;
  Cmd* cmd;
}

%type <intValue> INT
%type <exprValue> expr
%type <boolexp> bool
%type <charValue> VAR
%type <charValue> STRING
%type <list> cmdlist
%type <cmd> cmd

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CmdLista* root;
}

%%
program: FN MAIN PA PF CA cmdlist CF { root = $6; }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  }
  |
  expr MINUS expr {
    $$ = ast_operation(MINUS, $1, $3);
  }
  |
  expr TIMES expr {
    $$ = ast_operation(TIMES, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr REST expr {
    $$ = ast_operation(REST, $1, $3);
  } 
  ;
bool:
  expr GT expr {
  $$ = expression_operation(GT, $1, $3);
  }
  |
  expr LT expr {
  $$ = expression_operation(LT, $1, $3);
  }
  |
  expr GET expr {
  $$ = expression_operation(GET, $1, $3);
  }
  |
  expr LLET expr {
  $$ = expression_operation(LLET, $1, $3);
  }
  |
  expr EQ expr {
  $$ = expression_operation(EQ, $1, $3);
  }
  |
  expr DIF expr {
  $$ = expression_operation(DIF, $1, $3);
  }
  ;
cmdlist:
  {
  $$ = NULL;
  }
  |
  cmd cmdlist {
  $$ = newCmdLista($1,$2);
  }
  ;
cmd:
  IF bool CA cmdlist CF{
  $$ = cif(IF, $2, $4);
  }
  |
  IF bool CA cmdlist CF ELSE CA cmdlist CF {
  $$ = cif_else(ELSE, $2, $4, $8);
  }
  |
  WHILE bool CA cmdlist CF {
  $$ = cwhile(WHILE, $2, $4);
  }
  |
  LET VAR IG INT ACAB {
  $$ = catrib(LET, $2, $4);
  }
  |
  READLINE PA EC VAR PF ACAB {
  $$ = cread(READLINE, $4);
  }
  |
  PRINTLN PA STRING PF ACAB {
  $$ = cprint1(PRINTLN, $3);
  }
  |
  PRINTLN PA STRING VIRG VAR PF ACAB {
  $$ = cprint2(PRINTLN,$3,$5);
  }
  ;  
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}


