#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "printAbsTree.h"

void printSpace(int n){
	for(int i=0; i<n; i++){
		printf(" ");
	}
}

void printExpr(Expr* exp, int space){
	switch(exp -> kind) {
		case E_INTEGER:
			printSpace(space);
			printf("%d\n", exp -> attr.value);
			break;
		case E_OPERATION:
			switch(exp->attr.op.operator) {
				case PLUS:
					printSpace(space);
					printf("+\n");
					break;
				case MINUS:
					printSpace(space);
					printf("-\n");
					break;
				case TIMES:
					printSpace(space);
					printf("*\n");
					break;
				case DIV:
					printSpace(space);
					printf("/\n");
					break;
				case REST:
					printSpace(space);
					printf("%%\n");
					break;
				default:
					break;
			}
			printExpr(exp->attr.op.left, space+2);
			printExpr(exp->attr.op.right, space+2);
			break;
		default:
			break;
	}
}

void printBool(BoolExpr* boolexpr, int space) {
	switch(boolexpr -> kind) {
		case EB_CONSTANT:
			printSpace(space);
			printf("%d\n", boolexpr -> attr.bvalue);
			break;
		case EB_OPERATION:
			switch(boolexpr->attr.op.operator) {
				case GT:
					printSpace(space);
					printf(">\n");
					break;
				case LT:
					printSpace(space);
					printf("<\n");
					break;
				case GET:
					printSpace(space);
					printf(">=\n");
					break;
				case LLET:
					printSpace(space);
					printf("<=\n");
					break;
				case IG:
					printSpace(space);
					printf("=\n");
					break;
				case EQ:
					printSpace(space);
					printf("==\n");
					break;
				case DIF:
					printSpace(space);
					printf("!=\n");
					break;
				default:
					break;
			}
			printExpr(boolexpr->attr.op.bleft, space+2);
			printExpr(boolexpr->attr.op.bright, space+2);
			break;
		default:
			break;
	}
}

void printCmd (Cmd* cmd, int space) {
	switch(cmd -> kind){
		case E_IF:
			printSpace(space);
			printf("if\n");
			printBool(cmd -> attr.if1.condition, space+2);
			printCmdList(cmd -> attr.if1.lista1, space+2);
			break;

		case E_IF_ELSE:
			printSpace(space);
			printf("if\n");
			printBool(cmd -> attr.if_else.condition, space+2);
			printCmdList(cmd -> attr.if_else.lista1, space+2);
			printSpace(space);
			printf("else\n");
			printCmdList(cmd -> attr.if_else.lista2, space+2);
			break;

		case E_WHILE:
	  	printSpace(space);
			printf("while\n");
			printBool(cmd -> attr.while1.condition, space+2);
			printCmdList(cmd -> attr.while1.lista1, space+2);
			break;

		case E_ATRIB:
			printSpace(space);
			printf("let\n");
			printSpace(space+2);
			printf("%s\n", cmd -> attr.atrib.var);
			printSpace(space+2);
			printf("=\n");
			printSpace(space+2);
			printf("%d\n",cmd -> attr.atrib.num);
			break;

		case E_PRINT1:
			printSpace(space);
			printf("println!()\n");
			printSpace(space+2);
			printf("%s\n", cmd -> attr.print1.string);
			break;

		case E_PRINT2:
		  printSpace(space);
			printf("println!()\n");
			printSpace(space+2);
			printf("%s\n",cmd -> attr.print2.string);
			printSpace(space+2);
			printf("%s\n",cmd -> attr.print2.var);

		case E_READ:
			printSpace(space);
			printf("read_line()\n");
			printSpace(space+2);
			printf("%s\n", cmd -> attr.read.var);
			break;

		default:
			break;
	}

}

void printCmdList(CmdLista* lista, int space) {
	if(lista != NULL) {
		printCmd(lista -> node, space);
		printCmdList(lista -> next, space);
	}
}
