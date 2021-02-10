// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
//valor de x = 1 + 2
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct {
      int operator; // PLUS, MINUS, etc
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

typedef struct _Expr Expr; // Convenience typedef

// 2 > 3
struct _BoolExpr {
  enum {
    EB_CONSTANT,
    EB_OPERATION
  } kind;
  union {
    int bvalue;
    struct {
      int operator; 
      struct _Expr* bleft;
      struct _Expr* bright;
    } op;
  } attr;
};

typedef struct _BoolExpr BoolExpr;


//retorn um estado

struct _Cmd {
  enum {
    E_IF,
    E_IF_ELSE,
    E_WHILE,
    E_ATRIB,
    E_PRINT1,
    E_PRINT2,
    E_READ
  } kind;
  union {
    struct {
      int operator;
      struct _BoolExpr* condition;
      struct _CmdLista* lista1;
    } if1;

    struct{
      int operator;
      struct _BoolExpr* condition;
      struct _CmdLista* lista1;
      struct _CmdLista* lista2;
    } if_else;

    struct {
      int operator;
      struct _BoolExpr* condition;
      struct _CmdLista* lista1;
    } while1;

    struct {
      int operator;
      char* var;
      int num;
    } atrib;

    struct {
      int operator;
      char* string;
    } print1;

    struct {
      int operator;
      char* string;
      char* var;
    } print2;

    struct {
      int operator;
      char* var;
    } read;
  } attr;
};


typedef struct _Cmd Cmd;

struct _CmdLista {
  Cmd* node;
  struct _CmdLista* next;
};

typedef struct _CmdLista CmdLista;

// Constructor functions (see implementation in ast.c)
CmdLista* newCmdLista(Cmd* head, CmdLista* tail);
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* expression_integer(int v);
BoolExpr* expression_operation(int operator, Expr* left, Expr* right);
Cmd* cif(int operator, BoolExpr* condition, CmdLista* list);
Cmd* cif_else(int operator, BoolExpr* condition, CmdLista* list1, CmdLista* list2);
Cmd* cwhile(int operator, BoolExpr* condition, CmdLista* list);
Cmd* catrib(int operator, char* var, int v);
Cmd* cprint1(int operator, char* string);
Cmd* cprint2(int operator, char* string, char* var);
Cmd* cread(int operator, char* var);
#endif