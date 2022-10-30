%{
#include <stdio.h>
extern FILE *yyin;
extern FILE *yyout;
// yylineno=1;

%}

%%
"root"									{printf("ROOT\n");}
":"										{printf("Start of code\n");}
";"                                     {printf(" End Of Line\n");}
"end"									{printf("\nEnd of block\n");}
"int"									{printf(" Integer_type ");}
"real" 									{printf(" Real_type ");}
"string"								{printf(" String_type ");}
"%"										{printf(" Modulus ");}
"**"									{printf(" Power ");}
"=>"									{printf(" Assign ");}
"=="									{printf(" Equal ");}
"++"									{printf("++ ");}
"+"										{printf(" + ");}
"--"									{printf("-- ");}
"-"										{printf(" - ");}
"*"										{printf(" * ");}
"/"										{printf(" / ");}
"!="									{printf(" Not Equal");}	
"<="									{printf(" Less than or equal ");}
"<"										{printf(" Less than ");}
">="									{printf(" Greater than or equal ");}
">"										{printf(" Greater than ");}
"->"									{printf(" Helper");}
"<-"									{printf(" Helper");}
"display"								{printf(" Print ");}
"take"									{printf(" Read ");}
"^"										{printf(" XOR ");}
"&"										{printf(" AND ");}
"|"										{printf(" OR ");}
"~"										{printf(" NOT ");}
"SIN"									{printf(" sin of ");}
"COS"									{printf(" cos of ");}
"TAN"									{printf(" tan of ");}
"SQRT"									{printf(" Square root ");}
"log"									{printf(" log ");}
"ln"									{printf(" ln ");}
"!"										{printf(" factorial ");}
"if"									{printf(" if ");}
"elif"									{printf(" elif ");}
"else"									{printf(" else ");}
"repeat"								{printf(" Do ");}
"until"									{printf(" While");}
"from"									{printf(" for ");}
"to"									{printf(" to ");}
"by"									{printf(" by ");}
"module"								{printf("declare function\n");}
"goto"									{printf("call function");}
"sort"									{printf("sort array\n");}
"add"									{printf(" insert ");}
"remove"								{printf(" remove ");}



[0-9]+  								{printf(" Integer");}
[0-9]*[.][0-9]+([eE][+-]?[0-9]+)?		{printf(" Double");}
[A-Za-z0-9]+ 							{printf(" Variable");}
[@][A-Za-z0-9]+ 						{printf(" Array ");}
\"(\\.|[^"\\])*\"						{printf(" String ");}
[,()%{}\]\[]	 					{printf(" %s ",yytext);}
[ \t\n]									{}
.										{printf("\nUnknown character\n");}
%%
int yywrap()
{
	return 1;
}
int main()
{
	
	yyin = freopen("in.txt","r",stdin);
	yyout = freopen("out.txt","w",stdout);
	yylex();
	return 0;
}
