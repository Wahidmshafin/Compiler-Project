%{
#include <stdio.h>
#include "project.tab.h"
#include<string.h>
#include<math.h>
extern int yydebug;
extern FILE *yyin;
extern FILE *yyout;

int yyparse();	

%}


%%
"root"									 {return ROOT;}
":"										 {return START;}
";"                                      {return EOL;}
"end"									 {return END;}


"int"									 {return INTEGER_TYPE;}
"real" 									 {return REAL_TYPE;}
"string"								 {return STRING_TYPE;}


"%"										 {return MODULE;}
"**"									 {return POWER;}
"+"										 {return PLUS;}
"-"										 {return MINUS;}
"*"										 {return MUL;}
"/"										 {return DIV;}
"=>"									 {return ASSIGN;}
"++"									 {return PPLUS;}
"--"									 {return MMINUS;}


"=="									 {return EQUAL;}
"!="									 {return NOT_EQUAL;}
"<="									 {return LOE;}
"<"										 {return LESS;}
">="									 {return GOE;}
">"										 {return GREATER;}


"display"[ ]*"->"						 {return DISPLAY;}
"take"[ ]*"<-"							 {return TAKE;}


"^"										 {return XOR;}
"&"										 {return AND;}
"|"										 {return OR;}
"~"										 {return NOT;}


"SIN" 									 {return SIN;}
"COS" 									 {return COS;}
"TAN" 									 {return TAN;}
"SQR" 									 {return SQRT;}
"log" 									 {return LOG;}
"ln"  									 {return LN;}


"if"									 {return IF;}
"elif"									 {return ELIF;}
"else"									 {return ELSE;}

"repeat"								 {return REPEAT;}
"until"									 {return UNTILL;}
"from"									 {return FROM;}
"to"									 {return TO;}
"by"									 {return BY;}


"module"								 {return MODULE;}
"goto"									 {return GOTO;}
"sort"									 {return SORT;}
"add"									 {printf("insert ");}
"remove"								 {printf("remove ");}
 "."									 {printf(".");}


[#][^#]+[#]								 {printf("\nComment\n");}
[0-9]+  								 {yylval.integer = atoi(yytext);return INTEGER;}
[0-9]*[.][0-9]+([eE][+-]?[0-9]+)?		 {yylval.real=atof(yytext); return REAL;}

[@][A-Za-z0-9]+ 						 {yylval.string = strdup(yytext); return ARRAY;}
\"(\\|[^"\\])*\"						 {
												char* tmp = strdup(yytext);
												int n = strlen(tmp);
												yylval.string = malloc(n*sizeof(char));
  												memcpy(yylval.string,&tmp[1],n-2);
												yylval.string[n-2]='\0';
												return STRING;
										}
[,.(){}\]\[]	 						 {return yytext[0];}
[ \t\n]									 {}
.										 {printf("\nUnknown character%s\n", yytext);}
%%
int yywrap()
{
	return 1;
}
int yyerror(char *s){
	fprintf(stderr,"error: %s\n", s);
}
