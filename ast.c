// AST constructor functions
#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* a = (Expr*) malloc(sizeof(Expr));
  a -> kind = E_INTEGER;
  a -> attr.value = v;
  return a;
}

Expr* ast_operation (int operator, Expr* left, Expr* right) {
  Expr* a = (Expr*) malloc(sizeof(Expr));
  a -> kind = E_OPERATION;
  a -> attr.op.operator = operator;
  a -> attr.op.left = left;
  a -> attr.op.right = right;
  return a;
}

BoolExpr* expression_integer(int v) {
  BoolExpr* a = (BoolExpr*) malloc(sizeof(BoolExpr));
  a -> kind = EB_CONSTANT;
  a -> attr.bvalue = v;
  return a;
}

BoolExpr* expression_operation(int operator, Expr* bleft, Expr* bright){
  BoolExpr* a = (BoolExpr*) malloc(sizeof(BoolExpr));
  a -> kind = EB_OPERATION;
  a -> attr.op.operator = operator;
  a -> attr.op.bleft = bleft;
  a -> attr.op.bright = bright;
  return a;
}


Cmd* cif(int operator, BoolExpr* condition, CmdLista* list){
  Cmd* no = (Cmd*) malloc(sizeof(Cmd));
  no -> kind = E_IF;
  no -> attr.if1.operator = operator;
  no -> attr.if1.condition = condition;
  no -> attr.if1.lista1 = list;
  return no;
}

Cmd* cif_else(int operator, BoolExpr* condition, CmdLista* list1, CmdLista* list2){
  Cmd* no = (Cmd*) malloc(sizeof(Cmd));
  no -> kind = E_IF_ELSE;
  no -> attr.if_else.operator = operator;
  no -> attr.if_else.condition = condition;
  no -> attr.if_else.lista1 = list1;
  no -> attr.if_else.lista2 = list2;
  return no;
}

Cmd* cwhile(int operator, BoolExpr* condition, CmdLista* list){
  Cmd* no = (Cmd*) malloc(sizeof(Cmd));
  no -> kind = E_WHILE;
  no -> attr.while1.operator = operator;
  no -> attr.while1.condition = condition;
  no -> attr.while1.lista1 = list;
  return no;
}

Cmd* catrib(int operator, char* var, int v) {
  Cmd* no = (Cmd*) malloc(sizeof(Cmd));
  no -> kind = E_ATRIB;
  no -> attr.atrib.operator = operator;
  no -> attr.atrib.var = var;
  no -> attr.atrib.num = v;
  return no;
}

Cmd* cprint1(int operator, char* string) {
  Cmd* no = (Cmd*) malloc(sizeof(Cmd));
  no -> kind = E_PRINT1;
  no -> attr.print1.operator = operator;
  no -> attr.print1.string = string;
  return no;
}

Cmd* cprint2(int operator, char* string, char* var) {
  Cmd* no = (Cmd*) malloc(sizeof(Cmd));
  no -> kind = E_PRINT2;
  no -> attr.print2.operator = operator;
  no -> attr.print2.string = string;
  no -> attr.print2.var = var;
  return no;
}

Cmd* cread(int operator, char* var) {
  Cmd* no = (Cmd*) malloc(sizeof(Cmd));
  no -> kind = E_READ;
  no -> attr.read.operator = operator;
  no -> attr.read.var = var;
  return no;
}

CmdLista* newCmdLista(Cmd* head, CmdLista* tail) {
  CmdLista* list = (CmdLista*) malloc(sizeof(CmdLista));
  list -> node = head;
  list -> next = tail;
  return list;
}