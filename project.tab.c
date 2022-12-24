
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "project.y"

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



/* Line 189 of yacc.c  */
#line 271 "project.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ROOT = 258,
     END = 259,
     START = 260,
     VARIABLE = 261,
     ARRAY = 262,
     EOL = 263,
     ARROW = 264,
     RARROW = 265,
     INTEGER = 266,
     REAL = 267,
     STRING = 268,
     INTEGER_TYPE = 269,
     REAL_TYPE = 270,
     STRING_TYPE = 271,
     DISPLAY = 272,
     TAKE = 273,
     AND = 274,
     OR = 275,
     NOT = 276,
     XOR = 277,
     LOG = 278,
     LOG2 = 279,
     LN = 280,
     SIN = 281,
     COS = 282,
     TAN = 283,
     FACTORIAL = 284,
     SQRT = 285,
     IF = 286,
     ELIF = 287,
     ELSE = 288,
     CHOICE = 289,
     DEFAULT = 290,
     OPTION = 291,
     ASSIGN = 292,
     FROM = 293,
     TO = 294,
     REPEAT = 295,
     UNTILL = 296,
     BY = 297,
     AS = 298,
     MODULE = 299,
     GOTO = 300,
     SORT = 301,
     COMMENT = 302,
     MMINUS = 303,
     PPLUS = 304,
     GOE = 305,
     LOE = 306,
     NOT_EQUAL = 307,
     EQUAL = 308,
     LESS = 309,
     GREATER = 310,
     MINUS = 311,
     PLUS = 312,
     MOD = 313,
     DIV = 314,
     MUL = 315,
     POWER = 316
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 199 "project.y"

	int integer;
	double real;
	char* string;



/* Line 214 of yacc.c  */
#line 376 "project.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 388 "project.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   760

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNRULES -- Number of states.  */
#define YYNSTATES  243

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      68,    69,     2,     2,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    67,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    65,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    62
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,     9,    12,    14,    17,    20,    25,
      30,    34,    36,    38,    41,    44,    47,    50,    54,    56,
      60,    62,    64,    70,    74,    76,    80,    82,    86,    88,
      90,    96,   100,   102,   106,   108,   112,   114,   116,   122,
     126,   128,   132,   136,   143,   147,   151,   158,   161,   163,
     165,   167,   172,   176,   183,   185,   190,   195,   198,   200,
     205,   208,   210,   216,   226,   235,   244,   253,   254,   259,
     262,   264,   266,   268,   274,   275,   278,   281,   283,   285,
     287,   290,   293,   297,   301,   305,   309,   313,   317,   321,
     325,   329,   333,   337,   341,   345,   349,   353,   356,   360,
     365,   370,   375,   380,   385,   390,   393,   396
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      71,     0,    -1,     3,     5,    72,     4,    -1,    -1,    72,
      73,    -1,     8,    -1,    74,     8,    -1,    84,     8,    -1,
      17,     9,    85,     8,    -1,    18,    10,    86,     8,    -1,
      31,    87,    88,    -1,    92,    -1,    93,    -1,    96,     8,
      -1,    14,    75,    -1,    15,    78,    -1,    16,    81,    -1,
      75,    63,    76,    -1,    76,    -1,     6,    37,    98,    -1,
       6,    -1,     7,    -1,     7,    37,    64,    77,    65,    -1,
      77,    63,    98,    -1,    98,    -1,    78,    63,    79,    -1,
      79,    -1,     6,    37,    98,    -1,     6,    -1,     7,    -1,
       7,    37,    64,    80,    65,    -1,    80,    63,    98,    -1,
      98,    -1,    81,    63,    82,    -1,    82,    -1,     6,    37,
      13,    -1,     6,    -1,     7,    -1,     7,    37,    64,    83,
      65,    -1,    83,    63,    13,    -1,    13,    -1,     6,    37,
      98,    -1,     6,    37,    13,    -1,     7,    66,    11,    67,
      37,    98,    -1,    85,    63,    98,    -1,    85,    63,     7,
      -1,    85,    63,     7,    66,    11,    67,    -1,    85,    13,
      -1,    98,    -1,    13,    -1,     7,    -1,     7,    66,    98,
      67,    -1,    86,    63,     6,    -1,    86,    63,     7,    66,
      11,    67,    -1,     6,    -1,     7,    66,    11,    67,    -1,
      98,     5,    73,     4,    -1,    90,    89,    -1,    89,    -1,
      33,     5,    73,     4,    -1,    90,    91,    -1,    91,    -1,
      32,    98,     5,    73,     4,    -1,    38,    98,    39,    98,
      42,    98,     5,    73,     4,    -1,    41,    98,    54,    98,
      40,     5,    73,     4,    -1,    41,    98,    55,    98,    40,
       5,    73,     4,    -1,    44,     6,    68,    94,    69,     5,
      73,     4,    -1,    -1,    94,    63,    95,     6,    -1,    95,
       6,    -1,    14,    -1,    15,    -1,    16,    -1,    45,     6,
      68,    97,    69,    -1,    -1,    97,     6,    -1,    97,    11,
      -1,    11,    -1,    12,    -1,     6,    -1,    57,    98,    -1,
      56,    98,    -1,    98,    57,    98,    -1,    98,    56,    98,
      -1,    98,    60,    98,    -1,    98,    59,    98,    -1,    98,
      62,    98,    -1,    98,    58,    98,    -1,    98,    54,    98,
      -1,    98,    55,    98,    -1,    98,    51,    98,    -1,    98,
      50,    98,    -1,    98,    53,    98,    -1,    98,    52,    98,
      -1,    98,    19,    98,    -1,    98,    20,    98,    -1,    98,
      22,    98,    -1,    21,    98,    -1,    68,    98,    69,    -1,
      26,    68,    98,    69,    -1,    27,    68,    98,    69,    -1,
      28,    68,    98,    69,    -1,    23,    68,    98,    69,    -1,
      25,    68,    98,    69,    -1,    30,    68,    98,    69,    -1,
       6,    49,    -1,     6,    48,    -1,    98,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   227,   227,   234,   235,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   249,   250,   251,   254,   255,   259,
     273,   279,   284,   294,   300,   309,   310,   314,   328,   334,
     339,   349,   355,   364,   365,   369,   383,   389,   394,   404,
     410,   418,   435,   444,   469,   477,   479,   481,   483,   491,
     495,   497,   503,   505,   507,   509,   514,   534,   535,   539,
     555,   556,   558,   583,   591,   599,   612,   631,   632,   636,
     641,   642,   643,   646,   652,   653,   665,   673,   675,   677,
     687,   689,   691,   693,   695,   697,   699,   701,   703,   705,
     707,   709,   711,   713,   715,   717,   719,   721,   723,   725,
     727,   729,   731,   733,   735,   737,   752,   766
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ROOT", "END", "START", "VARIABLE",
  "ARRAY", "EOL", "ARROW", "RARROW", "INTEGER", "REAL", "STRING",
  "INTEGER_TYPE", "REAL_TYPE", "STRING_TYPE", "DISPLAY", "TAKE", "AND",
  "OR", "NOT", "XOR", "LOG", "LOG2", "LN", "SIN", "COS", "TAN",
  "FACTORIAL", "SQRT", "IF", "ELIF", "ELSE", "CHOICE", "DEFAULT", "OPTION",
  "ASSIGN", "FROM", "TO", "REPEAT", "UNTILL", "BY", "AS", "MODULE", "GOTO",
  "SORT", "COMMENT", "MMINUS", "PPLUS", "GOE", "LOE", "NOT_EQUAL", "EQUAL",
  "LESS", "GREATER", "MINUS", "PLUS", "MOD", "DIV", "MUL", "'^'", "POWER",
  "','", "'{'", "'}'", "'['", "']'", "'('", "')'", "$accept", "project",
  "statements", "statement", "declaration", "integer_variable",
  "integer_statements", "integer_values", "real_variable",
  "real_statements", "real_values", "string_variable", "string_statements",
  "string_values", "assign", "print", "scan", "if_block", "else_statement",
  "single_else", "elif_statement", "single_elif", "loop_block",
  "module_declare", "module_type", "types", "module_call", "parameters",
  "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,    94,   316,    44,   123,   125,    91,    93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    74,    74,    74,    75,    75,    76,
      76,    76,    76,    77,    77,    78,    78,    79,    79,    79,
      79,    80,    80,    81,    81,    82,    82,    82,    82,    83,
      83,    84,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    86,    86,    86,    86,    87,    88,    88,    89,
      90,    90,    91,    92,    92,    92,    93,    94,    94,    94,
      95,    95,    95,    96,    97,    97,    97,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     2,     1,     2,     2,     4,     4,
       3,     1,     1,     2,     2,     2,     2,     3,     1,     3,
       1,     1,     5,     3,     1,     3,     1,     3,     1,     1,
       5,     3,     1,     3,     1,     3,     1,     1,     5,     3,
       1,     3,     3,     6,     3,     3,     6,     2,     1,     1,
       1,     4,     3,     6,     1,     4,     4,     2,     1,     4,
       2,     1,     5,     9,     8,     8,     8,     0,     4,     2,
       1,     1,     1,     5,     0,     2,     2,     1,     1,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     4,
       4,     4,     4,     4,     4,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,     2,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,    11,    12,     0,     0,     0,    20,    21,
      14,    18,    28,    29,    15,    26,    36,    37,    16,    34,
       0,     0,    79,    77,    78,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     7,    13,    42,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    49,     0,    48,
      54,     0,     0,   106,   105,    97,     0,     0,     0,     0,
       0,     0,    81,    80,     0,     0,     0,    10,    58,     0,
      61,     0,     0,     0,     0,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    67,    74,     0,    19,     0,    17,    27,     0,    25,
      35,     0,    33,     0,     8,    47,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,    98,     0,     0,    57,
      60,     0,    94,    95,    96,    91,    90,    93,    92,    88,
      89,    83,    82,    87,    85,    84,    86,     0,    88,    89,
      70,    71,    72,     0,     0,     0,     0,     0,    24,     0,
      32,    40,     0,     0,    45,    44,     0,    52,     0,   102,
     103,    99,   100,   101,   104,     0,     0,    56,     0,     0,
       0,     0,     0,    69,    75,    76,    73,    43,     0,    22,
       0,    30,     0,    38,    51,     0,    55,     0,     0,    59,
       0,     0,     0,     0,     0,    23,    31,    39,     0,     0,
      62,     0,     0,     0,    68,     0,    46,    53,     0,    64,
      65,    66,    63
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    20,    21,    30,    31,   177,    34,    35,
     179,    38,    39,   182,    22,    78,    82,    55,    97,    98,
      99,   100,    23,    24,   173,   174,    25,   175,    56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -91
static const yytype_int16 yypact[] =
{
      50,    -1,    22,   -91,   -91,   582,   -91,    20,    -7,   -91,
      19,    21,    24,    57,    54,   215,   215,   215,    61,    62,
     -91,    68,    70,   -91,   -91,    72,   151,    58,    44,    45,
      51,   -91,    46,    47,    52,   -91,    74,    76,    59,   -91,
     112,    26,   -14,   -91,   -91,   215,    17,    53,    60,    80,
      82,    83,   215,   215,   215,    23,   234,   596,   654,    84,
      85,   -91,   -91,   -91,   -91,   698,    63,   215,    25,    19,
     215,    65,    21,   113,    90,    24,    89,   -91,     0,   698,
     -91,    92,    -3,   -91,   -91,   -10,   215,   215,   215,   215,
     215,   215,    48,    48,   316,   215,   131,   -91,   -91,    23,
     -91,   626,   215,   215,   215,   -91,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,     1,   -91,   122,   698,   215,   -91,   698,   215,   -91,
     -91,   148,   -91,   215,   -91,   -91,   190,   154,   -91,    55,
     360,   380,   424,   444,   488,   508,   -91,   247,   626,   -91,
     -91,   162,   -10,   -10,   -10,   175,   175,   175,   175,   175,
     175,    48,    48,   -23,   -23,   -23,   -91,   640,    87,   127,
     -91,   -91,   -91,   -60,   164,    -4,   215,   -51,   698,   -45,
     698,   -91,   -42,   552,   105,   698,   106,   -91,   109,   -91,
     -91,   -91,   -91,   -91,   -91,   626,   184,   -91,   215,   185,
     186,     1,   188,   -91,   -91,   -91,   -91,   698,   215,   -91,
     215,   -91,   182,   -91,   -91,   187,   -91,   189,   195,   -91,
     303,   626,   626,   197,   626,   698,   698,   -91,   138,   139,
     -91,   626,   205,   206,   -91,   208,   -91,   -91,   210,   -91,
     -91,   -91,   -91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   -91,   -90,   -91,   -91,   153,   -91,   -91,   152,
     -91,   -91,   150,   -91,   -91,   -91,   -91,   -91,   -91,   124,
     -91,   129,   -91,   -91,   -91,    28,   -91,   -91,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      57,    58,   204,   201,     3,   138,   105,   205,   134,   202,
      65,   151,   208,   135,   209,   170,   171,   172,   210,   105,
     211,   212,     4,   213,    79,    28,    29,    32,    33,    85,
      36,    37,    80,    81,    83,    84,    92,    93,    94,   117,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   124,   117,     1,   127,    95,    96,    26,   196,    27,
     139,   187,   188,   136,    41,   206,    40,    59,    60,    66,
     140,   141,   142,   143,   144,   145,    61,   105,    62,   147,
      63,    67,    68,    70,    71,    86,   152,   153,   154,   125,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   218,   114,   115,   116,   178,
     117,    73,   180,    74,    69,    72,   105,   183,    42,    76,
     185,    87,    75,    43,    44,    77,   130,   199,    88,   128,
     123,   232,   233,    45,   235,    46,   148,    47,    48,    49,
      50,   238,    51,   112,   113,   114,   115,   116,    89,   117,
      90,    91,   121,   122,   131,   133,   105,    42,   137,   176,
     207,   181,    43,    44,    64,   186,   197,   200,    52,    53,
     203,   215,    45,   216,    46,   217,    47,    48,    49,    50,
      54,    51,   220,   112,   113,   114,   115,   116,   219,   117,
     221,   222,   225,   224,   226,   227,    42,   184,   228,   230,
     229,    43,    44,   234,   105,   236,   237,    52,    53,   239,
     240,    45,   241,    46,   242,    47,    48,    49,    50,    54,
      51,    42,   126,   149,   129,   132,    43,    44,   150,   223,
       0,   112,   113,   114,   115,   116,    45,   117,    46,   101,
      47,    48,    49,    50,     0,    51,    52,    53,     0,     0,
       0,     0,   195,   102,   103,     0,   104,     0,    54,     0,
       0,     0,     0,   105,     0,     0,   102,   103,     0,   104,
       0,    52,    53,     0,     0,     0,   105,     0,     0,     0,
       0,     0,     0,    54,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   117,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   231,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   103,     0,   104,     0,     0,     0,     0,
       0,     0,   105,     0,     0,   102,   103,     0,   104,     0,
       0,     0,     0,     0,     0,   105,     0,     0,     0,     0,
       0,     0,     0,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,   117,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,   117,   102,
     103,     0,   104,     0,     0,   146,     0,     0,     0,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   102,
     103,     0,   104,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,   117,     0,     0,     0,     0,     0,     0,   189,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,   117,   102,   103,     0,   104,     0,     0,   190,
       0,     0,     0,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   102,   103,     0,   104,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   117,     0,     0,     0,
       0,     0,     0,   191,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   117,   102,   103,     0,
     104,     0,     0,   192,     0,     0,     0,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,     0,
     104,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
     117,     0,     0,     0,     0,     0,     0,   193,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
     117,   102,   103,     0,   104,     0,     0,   194,     0,     0,
       0,   105,     0,     0,     0,     0,     6,     0,     7,     8,
       9,     0,     0,     0,     0,     0,    10,    11,    12,    13,
      14,     0,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,    15,   117,   102,   103,     0,   104,   214,
      16,     0,     0,    17,     0,   105,    18,    19,     0,     0,
       0,     0,     7,     8,     9,   118,     0,     0,     0,     0,
      10,    11,    12,    13,    14,     0,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    15,   117,   102,
     103,     0,   104,     0,    16,     0,     0,    17,     0,   105,
      18,    19,     0,   102,   103,     0,   104,     0,     0,     0,
       0,     0,   198,   105,     0,     0,     0,     0,     0,     0,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,   117,     0,   106,   107,   108,   109,   119,   120,
     112,   113,   114,   115,   116,     0,   117,   102,   103,     0,
     104,     0,     0,     0,     0,     0,     0,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
     117
};

static const yytype_int16 yycheck[] =
{
      16,    17,     6,    63,     5,     8,    29,    11,     8,    69,
      26,   101,    63,    13,    65,    14,    15,    16,    63,    29,
      65,    63,     0,    65,    40,     6,     7,     6,     7,    45,
       6,     7,     6,     7,    48,    49,    52,    53,    54,    62,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    67,    62,     3,    70,    32,    33,    37,   148,    66,
      63,     6,     7,    63,    10,    69,     9,     6,     6,    11,
      86,    87,    88,    89,    90,    91,     8,    29,     8,    95,
       8,    37,    37,    37,    37,    68,   102,   103,   104,    64,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   195,    58,    59,    60,   125,
      62,    37,   128,    37,    63,    63,    29,   133,     6,     7,
     136,    68,    63,    11,    12,    13,    13,    40,    68,    64,
      67,   221,   222,    21,   224,    23,     5,    25,    26,    27,
      28,   231,    30,    56,    57,    58,    59,    60,    68,    62,
      68,    68,    68,    68,    64,    66,    29,     6,    66,    37,
     176,    13,    11,    12,    13,    11,     4,    40,    56,    57,
       6,    66,    21,    67,    23,    66,    25,    26,    27,    28,
      68,    30,   198,    56,    57,    58,    59,    60,     4,    62,
       5,     5,   208,     5,   210,    13,     6,     7,    11,     4,
      11,    11,    12,     6,    29,    67,    67,    56,    57,     4,
       4,    21,     4,    23,     4,    25,    26,    27,    28,    68,
      30,     6,    69,    99,    72,    75,    11,    12,    99,   201,
      -1,    56,    57,    58,    59,    60,    21,    62,    23,     5,
      25,    26,    27,    28,    -1,    30,    56,    57,    -1,    -1,
      -1,    -1,     5,    19,    20,    -1,    22,    -1,    68,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    19,    20,    -1,    22,
      -1,    56,    57,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     5,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    19,    20,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    19,
      20,    -1,    22,    -1,    -1,    69,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    19,    20,    -1,    22,    -1,    -1,    69,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    19,    20,    -1,
      22,    -1,    -1,    69,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    69,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    19,    20,    -1,    22,    -1,    -1,    69,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,     4,    -1,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    31,    62,    19,    20,    -1,    22,    67,
      38,    -1,    -1,    41,    -1,    29,    44,    45,    -1,    -1,
      -1,    -1,     6,     7,     8,    39,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    31,    62,    19,
      20,    -1,    22,    -1,    38,    -1,    -1,    41,    -1,    29,
      44,    45,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    42,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    19,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    71,     5,     0,    72,     4,     6,     7,     8,
      14,    15,    16,    17,    18,    31,    38,    41,    44,    45,
      73,    74,    84,    92,    93,    96,    37,    66,     6,     7,
      75,    76,     6,     7,    78,    79,     6,     7,    81,    82,
       9,    10,     6,    11,    12,    21,    23,    25,    26,    27,
      28,    30,    56,    57,    68,    87,    98,    98,    98,     6,
       6,     8,     8,     8,    13,    98,    11,    37,    37,    63,
      37,    37,    63,    37,    37,    63,     7,    13,    85,    98,
       6,     7,    86,    48,    49,    98,    68,    68,    68,    68,
      68,    68,    98,    98,    98,    32,    33,    88,    89,    90,
      91,     5,    19,    20,    22,    29,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    62,    39,    54,
      55,    68,    68,    67,    98,    64,    76,    98,    64,    79,
      13,    64,    82,    66,     8,    13,    63,    66,     8,    63,
      98,    98,    98,    98,    98,    98,    69,    98,     5,    89,
      91,    73,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      14,    15,    16,    94,    95,    97,    37,    77,    98,    80,
      98,    13,    83,    98,     7,    98,    11,     6,     7,    69,
      69,    69,    69,    69,    69,     5,    73,     4,    42,    40,
      40,    63,    69,     6,     6,    11,    69,    98,    63,    65,
      63,    65,    63,    65,    67,    66,    67,    66,    73,     4,
      98,     5,     5,    95,     5,    98,    98,    13,    11,    11,
       4,     5,    73,    73,     6,    73,    67,    67,    73,     4,
       4,     4,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 228 "project.y"
    {
                    printf("\n\n     -------Program Compiled Successfully-------\n\n\n");
                    return 0;
                ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 234 "project.y"
    {;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 235 "project.y"
    {;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 238 "project.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 239 "project.y"
    {;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 240 "project.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 241 "project.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 242 "project.y"
    {;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 243 "project.y"
    {;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 244 "project.y"
    {;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 245 "project.y"
    {;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 246 "project.y"
    {;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 260 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (3)].string));
                            if(declared==-1)
                            {
                                int value = (yyvsp[(3) - (3)].real);
                                insertData((yyvsp[(1) - (3)].string), &value, 0, varCount, 1, 0);
                                varCount++;
                            }
                            else
                            {
                                printf("Variable %s already exists\n",(yyvsp[(1) - (3)].string));
                            }
                        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 274 "project.y"
    {
                            int value = 0;
                            insertData((yyvsp[(1) - (1)].string), &value, 0, varCount, 1, 0);
                            varCount++;
                        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 280 "project.y"
    {
                            insertData((yyvsp[(1) - (1)].string), tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 285 "project.y"
    {
                            insertData((yyvsp[(1) - (5)].string), tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpInteger);
                        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 295 "project.y"
    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = (yyvsp[(3) - (3)].real);
                    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 301 "project.y"
    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = (yyvsp[(1) - (1)].real);
                    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 315 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (3)].string));
                            if(declared==-1)
                            {
                                double value = (yyvsp[(3) - (3)].real);
                                insertData((yyvsp[(1) - (3)].string), &value, 1, varCount, 1, 0);
                                varCount++;
                            }
                            else
                            {
                                printf("Variable %s already exists\n",(yyvsp[(1) - (3)].string));
                            }
                        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 329 "project.y"
    {
                            double value = 0;
                            insertData((yyvsp[(1) - (1)].string), &value, 1, varCount, 1, 0);
                            varCount++;
                        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 335 "project.y"
    {
                            insertData((yyvsp[(1) - (1)].string), tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                        ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 340 "project.y"
    {
                            insertData((yyvsp[(1) - (5)].string), tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpDouble);
                        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 350 "project.y"
    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (yyvsp[(3) - (3)].real);
                    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 356 "project.y"
    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (double)(yyvsp[(1) - (1)].real);
                    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 370 "project.y"
    {
                            int declared = getIndex((yyvsp[(1) - (3)].string));
                            if(declared==-1)
                            {
                                char *value = (yyvsp[(3) - (3)].string);
                                insertData((yyvsp[(1) - (3)].string), &value, 2, varCount, 1, 0);
                                varCount++;
                            }
                            else
                            {
                                printf("Variable %s already exists\n",(yyvsp[(1) - (3)].string));
                            }
                        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 384 "project.y"
    {
                            char *value;
                            insertData((yyvsp[(1) - (1)].string), &value, 2, varCount, 1, 0);
                            varCount++;
                        ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 390 "project.y"
    {
                            insertData((yyvsp[(1) - (1)].string), tmpString, 2, varCount, array_size, 1);
                            varCount++;
                        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 395 "project.y"
    {
                            insertData((yyvsp[(1) - (5)].string), tmpString, 2, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpString);
                        ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 405 "project.y"
    {
                        array_size++;
                        tmpString = realloc(tmpString, array_size*sizeof(char));
                        tmpString[array_size-1] = (yyvsp[(3) - (3)].string);
                    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 411 "project.y"
    {
                        array_size++;
                        tmpString = realloc(tmpString, array_size*sizeof(char));
                        tmpString[array_size-1] = (yyvsp[(1) - (1)].string);
                    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 419 "project.y"
    {
                    int index = getIndex((yyvsp[(1) - (3)].string));
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", (yyvsp[(1) - (3)].string));
                    }
                    else
                    {
                        {
                            if (varObject[index].type == 1)
                                varObject[index].dval[0] = (yyvsp[(3) - (3)].real);
                            if (varObject[index].type == 0)
                                varObject[index].ival[0] = (yyvsp[(3) - (3)].real);
                        }
                    }
                ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 436 "project.y"
    {
                    int index = getIndex((yyvsp[(1) - (3)].string));
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", (yyvsp[(1) - (3)].string));
                    }
                    strcpy(varObject[index].sval[0],(yyvsp[(3) - (3)].string) )
                ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 445 "project.y"
    {
                    int id = (yyvsp[(3) - (6)].integer);
                    int index = getIndex((yyvsp[(1) - (6)].string));
                    if (index == -1)
                    {
                         printf("there is no variable named %s.\n", (yyvsp[(1) - (6)].string));
                    }
                    else
                    {
                        if(id>=varObject[index].size){
                             printf("Array out of range\n");
                        }
                        else
                        {
                            if (varObject[index].type == 1)
                                varObject[index].dval[id] = (yyvsp[(6) - (6)].real);
                            if (varObject[index].type == 0)
                                varObject[index].ival[id] =  (yyvsp[(6) - (6)].real);
                        }
                    }
                ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 470 "project.y"
    {
                if(floor((yyvsp[(3) - (3)].real))==ceil((yyvsp[(3) - (3)].real)))
                printf("Value: %d\n",(int)(yyvsp[(3) - (3)].real));
                else
                printf("Value: %lf\n",(yyvsp[(3) - (3)].real));
            ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 477 "project.y"
    {printVariable((yyvsp[(3) - (3)].string));;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 479 "project.y"
    {printArrayIndex((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].integer));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 481 "project.y"
    {printf("%s\n",(yyvsp[(2) - (2)].string));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 484 "project.y"
    {
                if(floor((yyvsp[(1) - (1)].real))==ceil((yyvsp[(1) - (1)].real)))
                printf("Value: %d\n",(int)(yyvsp[(1) - (1)].real));
                else
                printf("Value: %lf\n",(yyvsp[(1) - (1)].real));
            ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 491 "project.y"
    {printf("%s\n",(yyvsp[(1) - (1)].string));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 495 "project.y"
    {printVariable((yyvsp[(1) - (1)].string));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 497 "project.y"
    {printArrayIndex((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].real));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 503 "project.y"
    {takeInput((yyvsp[(3) - (3)].string),0);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 505 "project.y"
    {takeInput((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].integer));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 507 "project.y"
    {takeInput((yyvsp[(1) - (1)].string),0);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 509 "project.y"
    {takeInput((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].integer));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 515 "project.y"
    {
                    conditionMatched[0]=1;
                    conPtr++;
                    conditionMatched[conPtr]=0;
                    
                        int isTrue = (fabs((yyvsp[(1) - (4)].real))>1e-9);
                        if(isTrue)
                        {
                            printf("IF block %d: TRUE.\n",conPtr);
                            conditionMatched[conPtr] = 1;
                        }
                        else
                        {
                            printf("IF block %d: FALSE.\n",conPtr);
                        }
                    
                ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 540 "project.y"
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
                ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 559 "project.y"
    {
                    
                    if(conditionMatched[conPtr]==0)
                    {
                        int isTrue = (fabs((yyvsp[(2) - (5)].real))>1e-9);
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
                    
                ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 584 "project.y"
    {
                    printf("FOR LOOP: \n");
                    for(double i=(yyvsp[(2) - (9)].real);i<(yyvsp[(4) - (9)].real);i=i+(yyvsp[(6) - (9)].real))
                    {
                        printf("Loop %d\n",(int)i);
                    }
                ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 592 "project.y"
    {
                    printf("WHILE LOOP: \n");
                    for(double i=(yyvsp[(2) - (8)].real);i<(yyvsp[(4) - (8)].real);i++ )
                    {
                        printf("Loop %d\n",(int)i);
                    }
                ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 600 "project.y"
    {
                    printf("WHILE LOOP: \n");
                    for(double i=(yyvsp[(2) - (8)].real);i>(yyvsp[(4) - (8)].real);i-- )
                    {
                        printf("Loop %d\n",(int)i);
                    }
                ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 613 "project.y"
    {
                        int id = getIndex((yyvsp[(2) - (8)].string));
                        int val=0;
                        if(id==-1)
                        {
                            insertData((yyvsp[(2) - (8)].string), &val, 0, varCount, 1, 0);
                            varCount++;
                            printf("Functions %s declared with this Parameters\n",(yyvsp[(2) - (8)].string));
                        }
                        else
                        {
                            printf("Function name already exist\n");
                        }
                        
                  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 633 "project.y"
    {
                        printf("Parameter: %s\n",(yyvsp[(4) - (4)].string));
                    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 637 "project.y"
    {
                        printf("Parameter: %s\n",(yyvsp[(2) - (2)].string));
                    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 647 "project.y"
    {
                    printf("Functions called\n");
                ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 654 "project.y"
    {
                    int id = getIndex((yyvsp[(2) - (2)].string));
                    if(id==-1)printf("Variable %s doesn't exist\n",(yyvsp[(2) - (2)].string));
                    if(varObject[id].type==0)
                    printf("Calling parameter: %s  Value: %d\n",(yyvsp[(2) - (2)].string), varObject[id].ival[0]);
                    else if(varObject[id].type==1)
                    printf("Calling parameter: %s Value: %lf\n",(yyvsp[(2) - (2)].string), varObject[id].dval[0]);
                    else
                    printf("Calling parameter: %s Value: %s\n",(yyvsp[(2) - (2)].string), varObject[id].sval[0]);
                ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 666 "project.y"
    {
                    printf("Calling Parameter Value: %d\n",(yyvsp[(2) - (2)].integer));
                ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 673 "project.y"
    {(yyval.real)=(yyvsp[(1) - (1)].integer);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 675 "project.y"
    {(yyval.real)=(yyvsp[(1) - (1)].real);;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 678 "project.y"
    {
                int id = getIndex((yyvsp[(1) - (1)].string));
                if(id==-1) printf("Variable %s already doesn't exist\n",(yyvsp[(1) - (1)].string));
                else if(varObject[id].type==2){
                    printf("String: %s\n",varObject[id].sval[0]);
                }
                else if(varObject[id].type==0) (yyval.real) = varObject[id].ival[0];
                else (yyval.real) = varObject[id].dval[0];
            ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 687 "project.y"
    {(yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 689 "project.y"
    {(yyval.real) = -(yyvsp[(2) - (2)].real);;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 691 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) + (yyvsp[(3) - (3)].real);;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 693 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) - (yyvsp[(3) - (3)].real);;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 695 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) * (yyvsp[(3) - (3)].real);;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 697 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) / (yyvsp[(3) - (3)].real);;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 699 "project.y"
    {(yyval.real) = pow((yyvsp[(1) - (3)].real),(yyvsp[(3) - (3)].real));;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 701 "project.y"
    {(yyval.real) = (int)(yyvsp[(1) - (3)].real) % (int)(yyvsp[(3) - (3)].real);;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 703 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) < (yyvsp[(3) - (3)].real));;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 705 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) > (yyvsp[(3) - (3)].real));;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 707 "project.y"
    {{(yyval.real) = ((yyvsp[(1) - (3)].real) <= (yyvsp[(3) - (3)].real));};}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 709 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) >= (yyvsp[(3) - (3)].real));;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 711 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) == (yyvsp[(3) - (3)].real));;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 713 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) != (yyvsp[(3) - (3)].real));;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 715 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) && (yyvsp[(3) - (3)].real));;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 717 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) || (yyvsp[(3) - (3)].real));;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 719 "project.y"
    {(yyval.real) = ((int)(yyvsp[(1) - (3)].real) ^ (int)(yyvsp[(3) - (3)].real));;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 721 "project.y"
    {(yyval.real) = !(yyvsp[(2) - (2)].real);;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 723 "project.y"
    {(yyval.real) = (yyvsp[(2) - (3)].real);}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 725 "project.y"
    {(yyval.real) = sin((yyvsp[(3) - (4)].real));;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 727 "project.y"
    {(yyval.real) = cos((yyvsp[(3) - (4)].real));;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 729 "project.y"
    {(yyval.real) = tan((yyvsp[(3) - (4)].real));;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 731 "project.y"
    {(yyval.real) = log10((yyvsp[(3) - (4)].real));;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 733 "project.y"
    {(yyval.real) = log((yyvsp[(3) - (4)].real));;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 735 "project.y"
    {(yyval.real) = sqrt((yyvsp[(3) - (4)].real));;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 738 "project.y"
    {
                int id = getIndex((yyvsp[(1) - (2)].string));
                if(id==-1) printf("Variable %s already exists",(yyvsp[(1) - (2)].string));
                else if(varObject[id].type==2) printf("Not Possible for String");
                else if(varObject[id].type==0){
                    varObject[id].ival[0]++;
                    (yyval.real) = varObject[id].ival[0];
                }
                else{
                    varObject[id].dval[0]+=1;
                    (yyval.real)=varObject[id].dval[0];
                }
            
            ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 753 "project.y"
    {
                int id = getIndex((yyvsp[(1) - (2)].string));
                if(id==-1) printf("Variable %s already exists",(yyvsp[(1) - (2)].string));
                else if(varObject[id].type==2) printf("Not Possible for Strng");
                else if(varObject[id].type==0){
                    varObject[id].ival[0]++;
                    (yyval.real) = varObject[id].ival[0];
                }
                else{
                    varObject[id].dval[0]+=1;
                    (yyval.real)=varObject[id].dval[0];
                }
            ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 767 "project.y"
    {
                int cl = ceil((yyvsp[(1) - (2)].real));int fl = floor((yyvsp[(1) - (2)].real));
                if(cl!=fl) printf("can't find FACTORIAL of real number\n");
                else {
                    long long x = 1;
                    for(long long i=1;i<=(yyvsp[(1) - (2)].real);i++) x*=i;
                    (yyval.real) = x;
                }
            ;}
    break;



/* Line 1455 of yacc.c  */
#line 2804 "project.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 779 "project.y"



int main(int argc, char **argv)
{
//yydebug= 1;
    free(varObject);
    varObject = realloc(varObject,10*sizeof(varpointer));
    varTaken=100;
    //yyin = fopen (argv[1],"r");
	yyin = freopen("input.txt","r",stdin);
	//yyout = freopen("myoutput.txt","w",stdout);
	yyout = freopen("out.txt","w",stdout);
    
    printf("\n\n     -------Starting Program Execution-------\n\n\n");
	yyparse();
	return 0;
} 



