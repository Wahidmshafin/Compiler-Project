%{
    #include<stdio.h>
	#include<stdlib.h>
	#include<conio.h>
	#include<string.h>
	#include<math.h>
    #include <windows.h>
    #include <io.h>
    #include <direct.h>
    #define YYDEBUG 1
  

   

    /*---Flex handling---*/
    extern FILE *yyin;
    extern FILE *yyout;
	int yylex();
	int yyparse();
    int yyerror(char *s);


    /* structure for storing variables.*/
    typedef struct VAR
    {
        char *name;
        int type; /* indicates data type- 0:int,1:double,2:char* */
        int *ival;
        double *dval;
        char** sval;
        int size;
        int isArray;
    }varpointer;

    varpointer *varObject; // Pointer for variables

    int varCount=0;
    int varTaken=0;
    int conditionMatched[10];
    int conPtr=0;
    int loopPtr=0;

//  For Array
    int *tmpInteger;
    double *tmpDouble;
    char **tmpString;
    int array_size=0;


    /* Get the index of variable that is called. If not found return -1. */
        int getIndex(char *varName)
        {
            for(int i = 0 ; i<varCount; i++)
            {
                if(strcmp(varObject[i].name,varName)==0){
                    return i;
                }
            }
            return -1;
        }

    /*---------Insert Object---------*/
    void insertData(char *vname,void* value,int type,int index,int size,int isArray)
    {
            varObject[index].name = vname;
            varObject[index].size = size;
            
            varObject[index].isArray = isArray;
            if(type==0){
                int *x = ((int*)value);
                varObject[index].ival = malloc(size*sizeof(int));
                for(int i=0;i<size;i++){
                    varObject[index].ival[i] = x[i];
                }
                varObject[index].type = 0;
                
            }
            else if(type==1){
                double* x = ((double*)value);
                varObject[index].dval = malloc(size*sizeof(double));
                for(int i=0;i<size;i++){
                    varObject[index].dval[i] = x[i];
                }
                varObject[index].type = 1;
                
            }
            else if(type==2){
                char **s =((char**)value);
                varObject[index].sval = malloc(size*sizeof(char**));
                for(int i=0;i<size;i++){
                    varObject[index].sval[i] = s[i];
                }
                varObject[index].type = 2;
            }
        }


        /* Printing a variable (including array)*/
        void printVariable(char *varName)
        {
            int index = getIndex(varName);
            if (index == -1)
            {
                printf("Variable %s doesn't exist\n",varName);
            }
            else
            {
                if (varObject[index].isArray)
                {
                    // printf("%s is an array with %d elements.Elements are:\n", varName, varObject[index].size);
                    printf("ArrayName: %s\nSize: %d\nElements are: \n",varName, varObject[index].size);
                    for (int i = 0; i < varObject[index].size; i++)
                    {
                        if (varObject[index].type == 1)
                            printf("%lf ", varObject[index].dval[i]);
                        if (varObject[index].type == 0)
                            printf("%d ", varObject[index].ival[i]);
                        if (varObject[index].type == 2)
                            printf("%s ", varObject[index].sval[i]);
                        if (i % 10 == 9)
                            printf("\n");
                    }
                    printf("\n");
                }
                else
                {
                    printf("Value of %s is:",varName);
                    if (varObject[index].type == 1)
                        printf("%lf\n", varObject[index].dval[0]);
                    if (varObject[index].type == 0)
                        printf("%d\n", varObject[index].ival[0]);
                    if (varObject[index].type == 2)
                        printf("%s\n", varObject[index].sval[0]);
                }
            }
        }


        /* Printing an Array Index */
        int printArrayIndex(char *varName, int position)
        {
            int index = getIndex(varName);
            if (index == -1)
            {
               printf("Variable %s doesn't exist\n",varName);
            }
            else if (varObject[index].isArray == 0)
            {
                printf("%s is not an Array\n",varName);
            }
            else if (position >= varObject[index].size)
            {
                printf("Index out of range\n");
            }
            else
            {
                printf("%s[%d] = ", varName, position);
                if (varObject[index].type == 1)
                    printf("%lf\n", varObject[index].dval[position]);
                if (varObject[index].type == 0)
                    printf("%d\n", varObject[index].ival[position]);
                if (varObject[index].type == 2)
                    printf("%s\n", varObject[index].sval[position]);
            }
        }

        /* Taking Input From User */
         int takeInput(char *varName, int id ){
            printf("Enter Value of %s:\n ",varName);
            int index = getIndex(varName);
            if (index == -1)
            {
                printf("Variable %s doesn't exist\n", varName);
            }
            else
            {
                if(id>=varObject[index].size){
                    printf("Out of range\n");
                }
                else
                {
                    if (varObject[index].type == 1)
                        scanf("%lf", &varObject[index].dval[id]);
                    if (varObject[index].type == 0)
                        scanf("%d", &varObject[index].ival[id]);
                    if (varObject[index].type == 2){
                        char str [100000];
                        scanf("%s",str);
                        varObject[index].sval[id]=str;
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
%type <string> VARIABLE INTEGER_TYPE REAL_TYPE STRING_TYPE STRING ARRAY COMMENT types
%type <real> expr REAL statements statement 
%nonassoc ELIF 
%nonassoc ELSE


%left PPLUS MMINUS
%left AND OR XOR NOT
%left LOG LOG2 LN SQRT 
%left GREATER LESS EQUAL NOT_EQUAL LOE GOE
%left  PLUS MINUS
%left  MUL DIV MOD
%right  '^' FACTORIAL

%left POWER SIN COS TAN

%%
project:    ROOT START statements END
                {
                    printf("\n\n     -------Program Compiled Successfully-------\n\n\n");
                    return 0;
                }
;

statements:     {}
                |statements statement   {}
;

statement:      EOL     {}
                |declaration    EOL     {}                
                |assign EOL        {}
                |DISPLAY ARROW print EOL    {}
                |TAKE RARROW scan EOL   {}
                |IF if_block else_statement   {}
                |loop_block     {}
                |module_declare   {}
                |module_call EOL    {}         
;

declaration:    INTEGER_TYPE integer_variable
                |REAL_TYPE real_variable
                |STRING_TYPE string_variable
;

integer_variable:   integer_variable ',' integer_statements
                    |integer_statements
;


integer_statements:     VARIABLE ASSIGN expr
                        {
                            int declared = getIndex($1);
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

integer_values:     integer_values ',' expr
                    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = $3;
                    }
                    |expr
                    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = $1;
                    }
;


real_variable:      real_variable ',' real_statements
                    |real_statements
;


real_statements:        VARIABLE ASSIGN expr
                        {
                            int declared = getIndex($1);
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

real_values:        real_values ',' expr
                    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = $3;
                    }
                    |expr
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
                            int declared = getIndex($1);
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
                    int index = getIndex($1);
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", $1);
                    }
                    else
                    {
                        {
                            if (varObject[index].type == 1)
                                varObject[index].dval[0] = $3;
                            if (varObject[index].type == 0)
                                varObject[index].ival[0] = $3;
                        }
                    }
                }
                |VARIABLE ASSIGN STRING
                {
                    int index = getIndex($1);
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", $1);
                    }
                    strcpy(varObject[index].sval[0],$3 )
                }
                |ARRAY '[' INTEGER ']' ASSIGN expr
                {
                    int id = $3;
                    int index = getIndex($1);
                    if (index == -1)
                    {
                         printf("there is no variable named %s.\n", $1);
                    }
                    else
                    {
                        if(id>=varObject[index].size){
                             printf("Array out of range\n");
                        }
                        else
                        {
                            if (varObject[index].type == 1)
                                varObject[index].dval[id] = $6;
                            if (varObject[index].type == 0)
                                varObject[index].ival[id] =  $6;
                        }
                    }
                }
;

print:      //print ',' VARIABLE                  {printVariable($3);}             
            print ',' expr                      
            {
                if(floor($3)==ceil($3))
                printf("Value: %d\n",(int)$3);
                else
                printf("Value: %lf\n",$3);
            }    
            
            |print ',' ARRAY                    {printVariable($3);}        
                
            |print ',' ARRAY '[' INTEGER ']'    {printArrayIndex($3,$5);}

            |print STRING                       {printf("%s\n",$2);}
            
            |expr
            {
                if(floor($1)==ceil($1))
                printf("Value: %d\n",(int)$1);
                else
                printf("Value: %lf\n",$1);
            }

            |STRING                             {printf("%s\n",$1);}

            //|VARIABLE                           {printVariable($1);}   
            
            |ARRAY                              {printVariable($1);}
                
            |ARRAY'[' expr ']'                  {printArrayIndex($1,$3);}
            
            
                
;

scan:       scan ',' VARIABLE                   {takeInput($3,0);} 
                
            |scan ',' ARRAY '[' INTEGER ']'     {takeInput($3,$5);} 
                
            |VARIABLE                           {takeInput($1,0);}
                
            |ARRAY '[' INTEGER ']'              {takeInput($1,$3);} 
                
;


if_block:       expr START statement END 
                {
                    conditionMatched[0]=1;
                    conPtr++;
                    conditionMatched[conPtr]=0;
                    
                        int isTrue = (fabs($1)>1e-9);
                        if(isTrue)
                        {
                            printf("IF block %d: TRUE.\n",conPtr);
                            conditionMatched[conPtr] = 1;
                        }
                        else
                        {
                            printf("IF block %d: FALSE.\n",conPtr);
                        }
                    
                }
;

else_statement: elif_statement   single_else
                |single_else
;


single_else: ELSE START statement END
                {       
                    if(conditionMatched[conPtr]==0)
                    {
                        printf("ELSE block %d: TRUE.\n",conPtr);
                        conditionMatched[conPtr] = 1;
                    }
                    else
                    {
                        printf("ELSE block %d: IGNORE.\n",conPtr);
                    }
                
                    conditionMatched[conPtr]=0;
                    conPtr--;                          
                }
    ;
elif_statement: elif_statement  single_elif
                |single_elif 
    ;
single_elif:    ELIF expr START statement END
                {
                    
                    if(conditionMatched[conPtr]==0)
                    {
                        int isTrue = (fabs($2)>1e-9);
                        if(isTrue)
                        {
                            printf("ELIF block %d: TRUE.\n",conPtr);
                            conditionMatched[conPtr] = 1;
                        }
                        else
                        {
                            printf("ELIF block %d: FALSE.\n",conPtr);
                        }
                    }
                    else
                    {
                        printf("ELIF block %d: IGNORE.\n",conPtr);
                    }
                    
                }
;


loop_block:     FROM expr TO expr BY expr START statement END
                {
                    printf("FOR LOOP: \n");
                    for(double i=$2;i<$4;i=i+$6)
                    {
                        printf("Loop %d\n",(int)i);
                    }
                }
                |UNTILL expr LESS expr REPEAT START statement END
                {
                    printf("WHILE LOOP: \n");
                    for(double i=$2;i<$4;i++ )
                    {
                        printf("Loop %d\n",(int)i);
                    }
                }
                |UNTILL expr GREATER expr REPEAT START statement END
                {
                    printf("WHILE LOOP: \n");
                    for(double i=$2;i>$4;i-- )
                    {
                        printf("Loop %d\n",(int)i);
                    }
                }
                
                
                
;

module_declare:   MODULE VARIABLE '(' module_type ')' START statement END
                  {
                        int id = getIndex($2);
                        int val=0;
                        if(id==-1)
                        {
                            insertData($2, &val, 0, varCount, 1, 0);
                            varCount++;
                            printf("Functions %s declared with this Parameters\n",$2);
                        }
                        else
                        {
                            printf("Function name already exist\n");
                        }
                        
                  }
                  
;

module_type:        
                    |module_type ',' types VARIABLE
                    {
                        printf("Parameter: %s\n",$4);
                    }
                    |types VARIABLE
                    {
                        printf("Parameter: %s\n",$2);
                    }
;
types:      INTEGER_TYPE  
            |REAL_TYPE    
            |STRING_TYPE  
;
                
module_call:    GOTO VARIABLE '(' parameters ')'
                {
                    printf("Functions called\n");
                }
;

parameters:     
                |parameters VARIABLE
                {
                    int id = getIndex($2);
                    if(id==-1)printf("Variable %s doesn't exist\n",$2);
                    if(varObject[id].type==0)
                    printf("Calling parameter: %s  Value: %d\n",$2, varObject[id].ival[0]);
                    else if(varObject[id].type==1)
                    printf("Calling parameter: %s Value: %lf\n",$2, varObject[id].dval[0]);
                    else
                    printf("Calling parameter: %s Value: %s\n",$2, varObject[id].sval[0]);
                }
                
                |parameters INTEGER
                {
                    printf("Calling Parameter Value: %d\n",$2);
                }
                



expr:       INTEGER {$$=$1;}                 
                                         
            |REAL {$$=$1;}       
               
            |VARIABLE             
            {
                int id = getIndex($1);
                if(id==-1) printf("Variable %s already doesn't exist\n",$1);
                else if(varObject[id].type==2){
                    printf("String: %s\n",varObject[id].sval[0]);
                }
                else if(varObject[id].type==0) $$ = varObject[id].ival[0];
                else $$ = varObject[id].dval[0];
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
                int id = getIndex($1);
                if(id==-1) printf("Variable %s already exists",$1);
                else if(varObject[id].type==2) printf("Not Possible for String");
                else if(varObject[id].type==0){
                    varObject[id].ival[0]++;
                    $$ = varObject[id].ival[0];
                }
                else{
                    varObject[id].dval[0]+=1;
                    $$=varObject[id].dval[0];
                }
            
            }
            |VARIABLE MMINUS       
            {
                int id = getIndex($1);
                if(id==-1) printf("Variable %s already exists",$1);
                else if(varObject[id].type==2) printf("Not Possible for Strng");
                else if(varObject[id].type==0){
                    varObject[id].ival[0]++;
                    $$ = varObject[id].ival[0];
                }
                else{
                    varObject[id].dval[0]+=1;
                    $$=varObject[id].dval[0];
                }
            }
            |expr FACTORIAL   
            {
                int cl = ceil($1);int fl = floor($1);
                if(cl!=fl) printf("can't find FACTORIAL of real number\n");
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
    free(varObject);
    varObject = realloc(varObject,10*sizeof(varpointer));
    varTaken=100;
    //yyin = fopen (argv[1],"r");
	yyin = freopen("input.txt","r",stdin);
	//yyout = freopen("myoutput.txt","w",stdout);
	yyout = freopen("output.txt","w",stdout);
    
    printf("\n\n     -------Starting Program Execution-------\n\n\n");
	yyparse();
	return 0;
} 


