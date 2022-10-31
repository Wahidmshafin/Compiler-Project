%{
#include <stdio.h>
extern FILE *yyin;
extern FILE *yyout;
// yylineno=1;

%}

number 			[0-9]+
variable 		[A-Za-z0-9]+

%%
"root"									 {printf("ROOT\n");}
":"										 {printf("\nStart of block\n");}
";"                                      {printf(";\n");}
"end"									 {printf("End of block\n");}
"int"									 {printf(" Integer_type ");}
"real" 									 {printf(" Real_type ");}
"string"								 {printf(" String_type ");}
"%"										 {printf(" Modulus ");}
"**"									 {printf(" Power ");}
"=>"									 {printf(" = ");}
"=="									 {printf(" Equal ");}
"++"									 {printf("++ ");}
"+"										 {printf(" + ");}
"--"									 {printf("-- ");}
"-"										 {printf(" - ");}
"*"										 {printf(" * ");}
"/"										 {printf(" / ");}
"!="									 {printf(" Not_Equal");}	
"<="									 {printf(" Less_than_or_equal ");}
"<"										 {printf(" Less_than ");}
">="									 {printf(" Greater_than_or_equal ");}
">"										 {printf(" Greater_than ");}
"display"[ ]*"->"						 {printf(" Print ");}
"take"[ ]*"<-"							 {printf(" Read ");}
"^"										 {printf(" XOR ");}
"&"										 {printf(" AND ");}
"|"										 {printf(" OR ");}
"~"										 {printf(" NOT ");}
"SIN"[(][ ]*({number}|{variable})[ ]*[)] {printf(" sin");}
"COS"[(][ ]*({number}|{variable})[ ]*[)] {printf(" cos");}
"TAN"[(][ ]*({number}|{variable})[ ]*[)] {printf(" tan");}
"SQR"[(][ ]*({number}|{variable})[ ]*[)] {printf(" Square root ");}
"log"[(][ ]*({number}|{variable})[ ]*[)] {printf(" log ");}
"ln"[(][ ]*({number}|{variable})[ ]*[)]	 {printf(" ln ");}
({number}|{variable})"!"				 {printf(" factorial ");}
"if"									 {printf(" if ");}
"elif"									 {printf(" elif ");}
"else"									 {printf(" else ");}
"repeat"								 {printf(" Do ");}
"until"									 {printf(" While");}
"from"									 {printf(" for ");}
"to"									 {printf(" to ");}
"by"									 {printf(" by ");}
"module"								 {printf("declare function\n");}
"goto"									 {printf("call function");}
"sort"									 {printf("sort array\n");}
"add"									 {printf("insert ");}
"remove"								 {printf("remove ");}
 "."									 {printf(".");}
 
[#][^#]+[#]								{printf("\nComment\n");}
{number}  								{printf(" Integer");}
[0-9]*[.][0-9]+([eE][+-]?[0-9]+)?		{printf(" Double");}
"module"[ ]+{variable} 					{printf(" declare_Function");}
"goto"[ ]+{variable} 					{printf(" call_Function");}
{variable}								{printf(" Variable");}
[@]{variable} 							{printf(" Array ");}
\"(\\|[^"\\])*\"						{printf(" String ");}
[,.()%{}\]\[]	 						{printf("%s ",yytext);}
[ \t\n]									{}
.										{printf("\nUnknown character%s\n", yytext);}
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
