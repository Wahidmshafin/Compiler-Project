%{
    #include<stdio.h>
	#include<stdlib.h>
	#include<conio.h>
	#include<string.h>
	#include<math.h>
    #include <windows.h>
    #include <io.h>
    #include <direct.h>

   

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

    var *vptr; // Pointer for variables

    int varCount=0;
    int varTaken=0;
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
                printf("Variable %s doesn't exist\n",varName);
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
               printf("Variable %s doesn't exist\n",varName);
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
            printf("Enter Value of %s: ",varName);
            int index = getVariableIndex(varName);
            if (index == -1)
            {
                printf("Variable %s doesn't exist\n", varName);
            }
            else
            {
                if(id>=vptr[index].size){
                    printf("Out of range\n");
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


%token ROOT END START VARIABLE ARRAY EOL ARROW RARROW INTEGER REAL STRING INTEGER_TYPE REAL_TYPE STRING_TYPE DISPLAY TAKE AND OR NOT XOR LOG LOG2 LN SIN COS TAN FACTORIAL SQRT IF ELIF ELSE CHOICE DEFAULT OPTION ASSIGN FROM TO REPEAT UNTILL BY AS MODULE GOTO SORT COMMENT


%type <integer> INTEGER ROOT END START project 
%type <string> VARIABLE INTEGER_TYPE REAL_TYPE STRING_TYPE STRING ARRAY COMMENT
%type <real> expr REAL statements statement 
%nonassoc ELIF 
%nonassoc ELSE


%left EQUAL NOT_EQUAL LOE GOE LESS GREATER PLUS MINUS MUL DIV POWER MOD PPLUS MMINUS AND OR XOR NOT LOG LOG2 LN SQRT SIN COS TAN
%right  '^' FACTORIAL

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
                |expr       EOL
                {
                    printf("Expression: %.2lf\n",$1);
                    $$=$1;
                }
                |assign EOL        {}
                |DISPLAY ARROW print EOL    {}
                |TAKE RARROW scan EOL   {}
                
                
;

declaration:    INTEGER_TYPE integer_variable
                |REAL_TYPE real_variable
                |STRING_TYPE string_variable
;

integer_variable:   integer_variable ',' integer_statements
                    |integer_statements
;


integer_statements:     VARIABLE ASSIGN INTEGER
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
                                printf("Variable %s already exists\n",$1);
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
                            insertData($1, tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                        }
                        |ARRAY ASSIGN '{' integer_values '}'
                        {
                            insertData($1, tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpInteger);
                        }

;

integer_values:     integer_values ',' INTEGER
                    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = $3;
                    }
                    |INTEGER
                    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = $1;
                    }
;


real_variable:      real_variable ',' real_statements
                    |real_statements
;


real_statements:        VARIABLE ASSIGN REAL
                        {
                            int declared = getVariableIndex($1);
                            if(declared==-1)
                            {
                                double value = $3;
                                insertData($1, &value, 1, varCount, 1, 0);
                                varCount++;
                            }
                            else
                            {
                                printf("Variable %s already exists\n",$1);
                            }
                        }
                        |VARIABLE
                        {
                            double value = 0;
                            insertData($1, &value, 1, varCount, 1, 0);
                            varCount++;
                        }
                        |ARRAY
                        {
                            insertData($1, tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                        }
                        |ARRAY ASSIGN '{' real_values '}'
                        {
                            insertData($1, tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpDouble);
                        }

;

real_values:        real_values ',' REAL
                    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = $3;
                    }
                    |REAL
                    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (double)$1;
                    }
;


string_variable:    string_variable ',' string_statements
                    |string_statements
;


string_statements:      VARIABLE ASSIGN STRING
                        {
                            int declared = getVariableIndex($1);
                            if(declared==-1)
                            {
                                char *value = $3;
                                insertData($1, &value, 2, varCount, 1, 0);
                                varCount++;
                            }
                            else
                            {
                                printf("Variable %s already exists\n",$1);
                            }
                        }
                        |VARIABLE
                        {
                            char *value;
                            insertData($1, &value, 2, varCount, 1, 0);
                            varCount++;
                        }
                        |ARRAY
                        {
                            insertData($1, tmpString, 2, varCount, array_size, 1);
                            varCount++;
                        }
                        |ARRAY ASSIGN '{' string_values '}'
                        {
                            insertData($1, tmpString, 2, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpString);
                        }

;

string_values:      string_values ',' STRING
                    {
                        array_size++;
                        tmpString = realloc(tmpString, array_size*sizeof(char));
                        tmpString[array_size-1] = $3;
                    }
                    |STRING
                    {
                        array_size++;
                        tmpString = realloc(tmpString, array_size*sizeof(char));
                        tmpString[array_size-1] = $1;
                    }
;

assign:         VARIABLE ASSIGN expr
                {
                    int index = getVariableIndex($1);
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", $1);
                    }
                    else
                    {
                        {
                            if (vptr[index].type == 1)
                                vptr[index].dval[0] = $3;
                            if (vptr[index].type == 0)
                                vptr[index].ival[0] = $3;
                        }
                    }
                }
                |ARRAY '[' INTEGER ']' ASSIGN expr
                {
                    int id = $3;
                    int index = getVariableIndex($1);
                    if (index == -1)
                    {
                         printf("there is no variable named %s.\n", $1);
                    }
                    else
                    {
                        if(id>=vptr[index].size){
                             printf("Array out of range\n");
                        }
                        else
                        {
                            if (vptr[index].type == 1)
                                vptr[index].dval[id] = $6;
                            if (vptr[index].type == 0)
                                vptr[index].ival[id] =  $6;
                        }
                    }
                }
;

print:      print ',' VARIABLE                  {printVariable($3);}             
                
            |print ',' ARRAY                    {printVariable($3);}        
                
            |print ',' ARRAY '[' INTEGER ']'    {printArrayIndex($3,$5);}
                
            |VARIABLE                           {printVariable($1);}   
            
            |ARRAY                              {printVariable($1);}
                
            |ARRAY'[' expr ']'                  {printArrayIndex($1,$3);}
                
;

scan:       scan ',' VARIABLE                   {takeInput($3,0);} 
                
            |scan ',' ARRAY '[' INTEGER ']'     {takeInput($3,$5);} 
                
            |VARIABLE                           {takeInput($1,0);}
                
            |ARRAY '[' INTEGER ']'              {takeInput($1,$3);} 
                
;


expr:       INTEGER {$$=$1;}                 
                                         
            |REAL {$$=$1;}       
               
            |VARIABLE             
            {
                int id = getVariableIndex($1);
                if(id==-1) printf("Variable %s already exists",$1);
                else if(vptr[id].type==2){
                   printf("Not a number");
                }
                else if(vptr[id].type==0) $$ = vptr[id].ival[0];
                else $$ = vptr[id].dval[0];
            }
            |PLUS expr          {$$ = $2;}
             
            |MINUS expr         {$$ = -$2;}
            
            |expr PLUS expr     {$$ = $1 + $3;}         
                
            |expr MINUS expr    {$$ = $1 - $3;}      
                
            |expr MUL expr      {$$ = $1 * $3;}
                 
            |expr DIV expr      {$$ = $1 / $3;}        
                
            |expr POWER expr    {$$ = pow($1,$3);}        
                
            |expr MOD expr      {$$ = (int)$1 % (int)$3;}         
                
            |expr LESS expr     {$$ = ($1 < $3);}         
                
            |expr GREATER expr  {$$ = ($1 > $3);}        
                
            |expr LOE expr      {{$$ = ($1 <= $3);}}        
                
            |expr GOE expr      {$$ = ($1 >= $3);}       
                
            |expr EQUAL expr    {$$ = ($1 == $3);}       
                
            |expr NOT_EQUAL expr {$$ = ($1 != $3);}        
                
            |expr AND expr      {$$ = ($1 && $3);}       
                
            |expr OR expr       {$$ = ($1 || $3);}         
                
            |expr XOR expr      {$$ = ((int)$1 ^ (int)$3);}         
                
            |NOT expr           {$$ = !$2;}              
                
            |'(' expr ')'      {$$ = $2}       
              
            |SIN '(' expr ')'  {$$ = sin($3);}   
              
            |COS '(' expr ')'  {$$ = cos($3);}    
              
            |TAN '(' expr ')'  {$$ = tan($3);}      
              
            |LOG '(' expr ')'  {$$ = log10($3);}      
                
            |LN '(' expr ')'   {$$ = log($3);}       
              
            |SQRT '(' expr ')' {$$ = sqrt($3);}     
                
            |VARIABLE PPLUS        
            {
                int id = getVariableIndex($1);
                if(id==-1) printf("Variable %s already exists",$1);
                else if(vptr[id].type==2) printf("Not Possible for String");
                else if(vptr[id].type==0){
                    vptr[id].ival[0]++;
                    $$ = vptr[id].ival[0];
                }
                else{
                    vptr[id].dval[0]+=1;
                    $$=vptr[id].dval[0];
                }
            
            }
            |VARIABLE MMINUS       
            {
                int id = getVariableIndex($1);
                if(id==-1) printf("Variable %s already exists",$1);
                else if(vptr[id].type==2) printf("Not Possible for Strng");
                else if(vptr[id].type==0){
                    vptr[id].ival[0]++;
                    $$ = vptr[id].ival[0];
                }
                else{
                    vptr[id].dval[0]+=1;
                    $$=vptr[id].dval[0];
                }
            }
            |expr FACTORIAL   
            {
                int cl = ceil($1);int fl = floor($1);
                if(cl!=fl) printf("can't find FACTORIAL of real number.");
                else {
                    long long x = 1;
                    for(long long i=1;i<=$1;i++) x*=i;
                    $$ = x;
                }
            }
    ; 
                        

%%


int main(int argc, char **argv)
{
//yydebug= 1;
    vptr = realloc(vptr,8*sizeof(var));
    varTaken=100;
	yyin = fopen (argv[1],"r");
    printf("\n\n     -------Starting Program Execution-------\n\n\n");
	yyparse();
	return 0;
} 


