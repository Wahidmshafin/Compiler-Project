%{
    #include<stdio.h>
	#include<stdlib.h>
	#include<conio.h>
	#include<string.h>
	#include<math.h>
    #include <windows.h>
    #include <io.h>
    #include <direct.h>


    /*---------Set Color---------*/
    void SetColor(int ForgC)
    {
        WORD wColor;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
            //We use csbi for the wAttributes word.
        if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            //Mask out all but the background attribute, and add in the forgournd color
            wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
        return;
    }


    /*---Flex handling---*/
    extern FILE *yyin;
	int yylex();
	int yyparse();
    int yyerror(char *s);


    /* structure for storing variables.*/
    typedef struct variable
    {
        char *name;
        int type; /* indicates data type- 0:int,1:double,2:char* */
        int *ival;
        double *dval;
        char** sval;
        int size;
        int isArray;
    }var;

    /*structure for storing user-defined modules(functions).*/
    typedef struct function{
        char *fname;
        var *fptr;
        int varCount;
    }stack;


    var *vptr; // Pointer for variables
    stack *fptr; // Pointer for functions

    int varCount=0, funCount=0;
    int varTaken=0, funTaken=0;
    int conditionMatched=0;

//  For Array
    int *tmpInteger;
    double *tmpDouble;
    char **tmpString;
    int array_size=0;


    /* Get the index of variable that is called. If not found return -1. */
        int getVariableIndex(char *varName)
        {
            for(int i = 0 ; i<varCount; i++){
                if(strcmp(vptr[i].name,varName)==0){
                    return i;
                }
            }
            return -1;
        }

    /* Error Handling for object not Declared */
        void doesNotExist(char *varName)
        {
            SetColor(4);
            printf("There is No Such Object: %s\n",varName);
            SetColor(2);
        } 

    /* Error Handling for object already Declared. */
        void alreadyExist(char *varName)
        {
            SetColor(4);
            printf("%s is already Declared.\n",varName);
            SetColor(2);
        }

     /* Error Handling for out of bound */ 
        void outOfRange()
        {
            SetColor(4);
            printf("Trying to Access index out of Range.\n");
            SetColor(2);
        }

    /* Error Handling for error on applying arithmetic on string. */
        void notNumeric()
        {
             SetColor(4);
             printf("String literals not applicable.\n");
             SetColor(2);
        }

    /*---------Insert Object---------*/
    void insertData(char *vname,void* value,int type,int index,int size,int isArray)
    {
            vptr[index].name = vname;
            vptr[index].size = size;
            
            vptr[index].isArray = isArray;
            if(type==0){
                int *x = ((int*)value);
                vptr[index].ival = malloc(size*sizeof(int));
                for(int i=0;i<size;i++){
                    vptr[index].ival[i] = x[i];
                }
                vptr[index].type = 0;
                
            }
            else if(type==1){
                double* x = ((double*)value);
                vptr[index].dval = malloc(size*sizeof(double));
                for(int i=0;i<size;i++){
                    vptr[index].dval[i] = x[i];
                }
                vptr[index].type = 1;
                
            }
            else if(type==2){
                char **s =((char**)value);
                vptr[index].sval = malloc(size*sizeof(char**));
                for(int i=0;i<size;i++){
                    vptr[index].sval[i] = s[i];
                }
                vptr[index].type = 2;
            }
        }


        /* Printing a variable (including array)*/
        void printVariable(char *varName)
        {
            int index = getVariableIndex(varName);
            if (index == -1)
            {
                doesNotExist(varName);
            }
            else
            {
                if (vptr[index].isArray)
                {
                    // printf("%s is an array with %d elements.Elements are:\n", varName, vptr[index].size);
                    printf("ArrayName: %s\nSize: %d\nElements are: \n",varName, vptr[index].size);
                    for (int i = 0; i < vptr[index].size; i++)
                    {
                        if (vptr[index].type == 1)
                            printf("%lf ", vptr[index].dval[i]);
                        if (vptr[index].type == 0)
                            printf("%d ", vptr[index].ival[i]);
                        if (vptr[index].type == 2)
                            printf("%s ", vptr[index].sval[i]);
                        if (i % 10 == 9)
                            printf("\n");
                    }
                    printf("\n");
                }
                else
                {
                    printf("Value of %s is:",varName);
                    if (vptr[index].type == 1)
                        printf("%lf\n", vptr[index].dval[0]);
                    if (vptr[index].type == 0)
                        printf("%d\n", vptr[index].ival[0]);
                    if (vptr[index].type == 2)
                        printf("%s\n", vptr[index].sval[0]);
                }
            }
        }


        /* Printing an Array Index */
        int printArrayIndex(char *varName, int position)
        {
            int index = getVariableIndex(varName);
            if (index == -1)
            {
               doesNotExist(varName);
            }
            else if (vptr[index].isArray == 0)
            {
                printf("%s is not an Array\n",varName);
            }
            else if (position >= vptr[index].size)
            {
                printf("Index out of range\n");
            }
            else
            {
                printf("%s[%d] = ", varName, position);
                if (vptr[index].type == 1)
                    printf("%lf\n", vptr[index].dval[position]);
                if (vptr[index].type == 0)
                    printf("%d\n", vptr[index].ival[position]);
                if (vptr[index].type == 2)
                    printf("%s\n", vptr[index].sval[position]);
            }
        }

        /* Taking Input From User */
         int takeInput(char *varName, int id ){
            SetColor(8);
            printf("Enter Value of %s: ",varName);
            SetColor(2);
            int index = getVariableIndex(varName);
            if (index == -1)
            {
                doesNotExist(varName);
            }
            else
            {
                if(id>=vptr[index].size){
                    outOfRange();
                }
                else
                {
                    if (vptr[index].type == 1)
                        scanf("%lf", &vptr[index].dval[id]);
                    if (vptr[index].type == 0)
                        scanf("%d", &vptr[index].ival[id]);
                    if (vptr[index].type == 2){
                        char str [100000];
                        scanf("%s",str);
                        vptr[index].sval[id]=str;
                    }
                       
                }
            }
        }

%}


%union{
	int integer;
	double real;
	char* string;
}


%token ROOT END START VARIABLE ARRAY EOL ARROW RARROW 
%token INTEGER REAL STRING INTEGER_TYPE REAL_TYPE STRING_TYPE
%token DISPLAY TAKE
%token AND OR NOT XOR LOG LOG2 LN SIN COS TAN FACTORIAL SQRT
%token IF ELIF ELSE CHOICE DEFAULT OPTION ASSIGN
%token FROM TO REPEAT UNTILL BY AS
%token MODULE GOTO SORT COMMENT



%type <integer> INTEGER ROOT END START project while_conditions
%type <string> VARIABLE INTEGER_TYPE REAL_TYPE STRING_TYPE STRING ARRAY COMMENT
%type <real> expr REAL statements statement 
%nonassoc ELIF 
%nonassoc ELSE


%left EQUAL NOT_EQUAL LOE GOE LESS GREATER
%left PLUS MINUS MUL DIV POWER MOD
%left PPLUS MMINUS
%left AND OR XOR NOT
%left LOG LOG2 LN SQRT 
%right  '^' FACTORIAL
%left SIN COS TAN

%%
project:    ROOT START statements END 
                {
                    printf("\n\n     -------Program Compiled Successfully-------\n\n\n");
                }
;

statements:     {}
                |statements statement   {}
;

statement:      EOL     {}
                |declaration    EOL     {}
                |assigns    EOL     {}
                |display    EOL     {}
                |take       EOL     {}
                |expr       EOL
                {
                    SetColor(8);
                    printf("Expression: %.2lf\n",$1);
                    $$=$1;
                    SetColor(2);
                }
                |if_statements  {conditionMatched=0}
                |array_statements   {}
                |loop_statements    {}
                |goto_module    {}
                |module_statements
                {
                    SetColor(8);
                    printf("Module Name: %s\n",fptr[funCount].fname);
                    printf("Paremerters: \n");
                    char *c;
                    for(int i=0;i<fptr[funCount].varCount;i++)
                    {
                            if (stk[funCount].fptr[i].type == 1)
                                c="Real";
                            if (stk[funCount].fptr[i].type == 0)
                                c="Int";
                            if (stk[funCount].fptr[i].type == 2)
                                c="String";
                            
                            printf("Parameter Name:%s Data Type: %s",stk[funCount].fptr[i].name,c);
                    }

                    funCount++;
                    SetColor(2);
                }
;

declaration:    INTEGER_TYPE integer_variable
                |REAL_TYPE real_variable
                |STRING_TYPE string_variable
;

integer_variable:   integer_variable "," integer_statements
                    |integer_statements
;


integer_statements:     VARIABLE ASSIGN expr
                        {
                            int declared = getVariableIndex($1);
                            if(declared==-1)
                            {
                                int value = $3;
                                insertData($1, &value, 0, varCount, 1, 0);
                                varCount++;
                            }
                            else
                            {
                                alreadyExist($1);
                            }
                        }
                        |VARIABLE
                        {
                            int value = 0;
                            insertData($1, &value, 0, varCount, 1, 0);
                            varCount++;
                        }
                        |ARRAY
                        {
                            insertData($1, &tmpInteger, 0, varCount, array_size, 0);
                            varCount++;
                        }
                        |

;


                        

%%


int main(int argc, char **argv)
{
//yydebug= 1;
    vptr = realloc(vptr,8*sizeof(var));
    varTaken=100;
	yyin = fopen (argv[1],"r");
    SetColor(2);
    printf("\n\n     -------Starting Program Execution-------\n\n\n");
	yyparse();
	return 0;
} 


