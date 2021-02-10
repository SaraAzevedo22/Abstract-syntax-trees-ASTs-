%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }



"+" { return PLUS;  }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIV;   }
"%" { return REST;  }
">" { return GT;    }
"<" { return LT;    }
">=" { return GET;   }
"<=" { return LLET;  }
"="  { return IG;    }
"==" { return EQ;    }
"!=" { return DIF;   }
"(" { return PA;    }
")" { return PF;    }
"{" { return CA;    }
"}" { return CF;    }
";" { return ACAB;  }
"," { return VIRG;  }
"&"  { return EC;    }
"fn" { return FN;    }
"main" { return MAIN;}
"if" { return IF;    }
"else" {return ELSE;}
"while" { return WHILE;}
"println!" { return PRINTLN;}
"read_line" { return READLINE;}
"let" { return LET;}




\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

[a-z][A-Za-z]* {
	yylval.charValue = strdup(yytext);
	return VAR;
}

\".*\" {
	yylval.charValue = strdup(yytext);
	return STRING;
}
.  { yyerror("unexpected character"); }
%%
