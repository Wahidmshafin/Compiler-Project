
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
            for(int i = 0 ; i<varCount; i++)
            {
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
            printf("Enter Value of %s:\n ",varName);
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



/* Line 189 of yacc.c  */
#line 268 "project.tab.c"

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
#line 196 "project.y"

	int integer;
	double real;
	char* string;



/* Line 214 of yacc.c  */
#line 373 "project.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 385 "project.tab.c"

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
#define YYLAST   546

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNRULES -- Number of states.  */
#define YYNSTATES  192

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
      30,    34,    37,    40,    43,    47,    49,    53,    55,    57,
      63,    67,    69,    73,    75,    79,    81,    83,    89,    93,
      95,    99,   101,   105,   107,   109,   115,   119,   121,   125,
     132,   136,   140,   147,   150,   152,   154,   156,   161,   165,
     172,   174,   179,   184,   187,   189,   194,   197,   199,   205,
     207,   209,   211,   214,   217,   221,   225,   229,   233,   237,
     241,   245,   249,   253,   257,   261,   265,   269,   273,   277,
     280,   284,   289,   294,   299,   304,   309,   314,   317,   320
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      71,     0,    -1,     3,     5,    72,     4,    -1,    -1,    72,
      73,    -1,     8,    -1,    74,     8,    -1,    84,     8,    -1,
      17,     9,    85,     8,    -1,    18,    10,    86,     8,    -1,
      31,    87,    88,    -1,    14,    75,    -1,    15,    78,    -1,
      16,    81,    -1,    75,    63,    76,    -1,    76,    -1,     6,
      37,    92,    -1,     6,    -1,     7,    -1,     7,    37,    64,
      77,    65,    -1,    77,    63,    92,    -1,    92,    -1,    78,
      63,    79,    -1,    79,    -1,     6,    37,    92,    -1,     6,
      -1,     7,    -1,     7,    37,    64,    80,    65,    -1,    80,
      63,    92,    -1,    92,    -1,    81,    63,    82,    -1,    82,
      -1,     6,    37,    13,    -1,     6,    -1,     7,    -1,     7,
      37,    64,    83,    65,    -1,    83,    63,    13,    -1,    13,
      -1,     6,    37,    92,    -1,     7,    66,    11,    67,    37,
      92,    -1,    85,    63,    92,    -1,    85,    63,     7,    -1,
      85,    63,     7,    66,    11,    67,    -1,    85,    13,    -1,
      92,    -1,    13,    -1,     7,    -1,     7,    66,    92,    67,
      -1,    86,    63,     6,    -1,    86,    63,     7,    66,    11,
      67,    -1,     6,    -1,     7,    66,    11,    67,    -1,    92,
       5,    73,     4,    -1,    90,    89,    -1,    89,    -1,    33,
       5,    73,     4,    -1,    90,    91,    -1,    91,    -1,    32,
      92,     5,    73,     4,    -1,    11,    -1,    12,    -1,     6,
      -1,    57,    92,    -1,    56,    92,    -1,    92,    57,    92,
      -1,    92,    56,    92,    -1,    92,    60,    92,    -1,    92,
      59,    92,    -1,    92,    62,    92,    -1,    92,    58,    92,
      -1,    92,    54,    92,    -1,    92,    55,    92,    -1,    92,
      51,    92,    -1,    92,    50,    92,    -1,    92,    53,    92,
      -1,    92,    52,    92,    -1,    92,    19,    92,    -1,    92,
      20,    92,    -1,    92,    22,    92,    -1,    21,    92,    -1,
      68,    92,    69,    -1,    26,    68,    92,    69,    -1,    27,
      68,    92,    69,    -1,    28,    68,    92,    69,    -1,    23,
      68,    92,    69,    -1,    25,    68,    92,    69,    -1,    30,
      68,    92,    69,    -1,     6,    49,    -1,     6,    48,    -1,
      92,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   224,   224,   231,   232,   235,   236,   238,   239,   240,
     241,   246,   247,   248,   251,   252,   256,   270,   276,   281,
     291,   297,   306,   307,   311,   325,   331,   336,   346,   352,
     361,   362,   366,   380,   386,   391,   401,   407,   415,   432,
     457,   465,   467,   469,   471,   479,   483,   485,   491,   493,
     495,   497,   502,   516,   517,   521,   536,   537,   539,   567,
     569,   571,   581,   583,   585,   587,   589,   591,   593,   595,
     597,   599,   601,   603,   605,   607,   609,   611,   613,   615,
     617,   619,   621,   623,   625,   627,   629,   631,   646,   660
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
  "single_else", "elif_statement", "single_elif", "expr", 0
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
      73,    74,    74,    74,    75,    75,    76,    76,    76,    76,
      77,    77,    78,    78,    79,    79,    79,    79,    80,    80,
      81,    81,    82,    82,    82,    82,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    86,
      86,    86,    87,    88,    88,    89,    90,    90,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     2,     1,     2,     2,     4,     4,
       3,     2,     2,     2,     3,     1,     3,     1,     1,     5,
       3,     1,     3,     1,     3,     1,     1,     5,     3,     1,
       3,     1,     3,     1,     1,     5,     3,     1,     3,     6,
       3,     3,     6,     2,     1,     1,     1,     4,     3,     6,
       1,     4,     4,     2,     1,     4,     2,     1,     5,     1,
       1,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     4,     4,     4,     4,     4,     4,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,     2,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     4,     0,     0,     0,
       0,    17,    18,    11,    15,    25,    26,    12,    23,    33,
      34,    13,    31,     0,     0,    61,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     7,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    45,     0,    44,    50,     0,     0,
      88,    87,    79,     0,     0,     0,     0,     0,     0,    63,
      62,     0,     0,     0,    10,    54,     0,    57,     0,     0,
       0,     0,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    14,    24,
       0,    22,    32,     0,    30,     0,     8,    43,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,    80,     0,
       0,    53,    56,     0,    76,    77,    78,    73,    72,    75,
      74,    70,    71,    65,    64,    69,    67,    66,    68,     0,
       0,    21,     0,    29,    37,     0,     0,    41,    40,     0,
      48,     0,    84,    85,    81,    82,    83,    86,     0,     0,
      52,    39,     0,    19,     0,    27,     0,    35,    47,     0,
      51,     0,     0,    55,    20,    28,    36,     0,     0,    58,
      42,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    16,    17,    23,    24,   150,    27,    28,
     152,    31,    32,   155,    18,    65,    69,    48,    84,    85,
      86,    87,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -83
static const yytype_int16 yypact[] =
{
       9,    12,    21,   -83,   -83,   232,   -83,   -12,   -37,   -83,
      -5,     2,    17,    30,    33,   139,   -83,    45,    53,   139,
      36,    29,    31,     4,   -83,    32,    50,    10,   -83,    52,
      55,    27,   -83,    91,    39,     1,   -83,   -83,   139,    25,
      26,    37,    38,    40,    41,   139,   139,   139,    19,   158,
     -83,   -83,   471,    28,   139,    43,    -5,   139,    46,     2,
      87,    47,    17,    35,   -83,    -3,   471,   -83,    49,    -1,
     -83,   -83,   484,   139,   139,   139,   139,   139,   139,   -18,
     -18,   215,   139,   108,   -83,   -83,    19,   -83,   118,   139,
     139,   139,   -83,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,    83,   471,   139,   -83,   471,
     139,   -83,   -83,   125,   -83,   139,   -83,   -83,   116,   120,
     -83,    58,   235,   279,   299,   343,   363,   407,   -83,   171,
     118,   -83,   -83,   136,   484,   484,   484,   -26,   -26,   -26,
     -26,   -26,   -26,   -18,   -18,   -25,   -25,   -25,   -83,   139,
     -50,   471,   -47,   471,   -83,   -43,   427,    63,   471,    85,
     -83,    88,   -83,   -83,   -83,   -83,   -83,   -83,   118,   152,
     -83,   471,   139,   -83,   139,   -83,   144,   -83,   -83,   147,
     -83,   150,   164,   -83,   471,   471,   -83,   103,   104,   -83,
     -83,   -83
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -83,   -83,   -83,   -82,   -83,   -83,   119,   -83,   -83,   115,
     -83,   -83,   117,   -83,   -83,   -83,   -83,   -83,   -83,    95,
     -83,    96,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      52,    21,    22,    92,    92,   116,   133,   120,    25,    26,
     117,    92,     1,   172,    66,   173,   174,     3,   175,    72,
     176,     4,   177,    29,    30,    19,    79,    80,    81,    20,
      99,   100,   101,   102,   103,   106,   104,   104,   109,    33,
     101,   102,   103,    34,   104,    67,    68,    53,   169,    70,
      71,    82,    83,    50,   122,   123,   124,   125,   126,   127,
     118,    51,   121,   129,   160,   161,    54,    56,    55,    57,
     134,   135,   136,    59,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   182,    58,   151,    60,
      62,   153,    61,    73,    74,   105,   156,    35,    63,   158,
     112,   115,    36,    37,    64,    75,    76,   107,    77,    78,
     110,   113,    38,   130,    39,   119,    40,    41,    42,    43,
     149,    44,    35,   157,     7,     8,     9,    36,    37,   179,
     171,   159,    10,    11,    12,    13,    14,    38,   154,    39,
     170,    40,    41,    42,    43,    35,    44,    45,    46,    15,
      36,    37,   180,   184,   181,   185,   183,   186,   187,    47,
      38,   188,    39,    88,    40,    41,    42,    43,   189,    44,
     190,   191,    45,    46,   111,   108,   168,    89,    90,   114,
      91,   131,   132,     0,    47,     0,     0,    92,     0,     0,
      89,    90,     0,    91,     0,    45,    46,     0,     0,     0,
      92,     0,     0,     0,     0,     0,     0,    47,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     0,
     104,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,   104,    89,    90,     6,    91,     7,     8,
       9,     0,     0,     0,    92,     0,    10,    11,    12,    13,
      14,     0,     0,     0,    89,    90,     0,    91,     0,     0,
       0,     0,     0,    15,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     0,   104,     0,     0,
       0,     0,     0,     0,   128,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     0,   104,    89,    90,
       0,    91,     0,     0,   162,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    90,
       0,    91,     0,     0,     0,     0,     0,     0,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,   104,     0,     0,     0,     0,     0,     0,   163,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,   104,    89,    90,     0,    91,     0,     0,   164,     0,
       0,     0,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,    91,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,   104,     0,     0,     0,     0,
       0,     0,   165,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,   104,    89,    90,     0,    91,
       0,     0,   166,     0,     0,     0,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,     0,    91,
       0,     0,     0,     0,     0,     0,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,   104,
       0,     0,     0,     0,     0,     0,   167,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,   104,
      89,    90,     0,    91,   178,     0,     0,     0,     0,     0,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,   104,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,   104
};

static const yytype_int16 yycheck[] =
{
      19,     6,     7,    29,    29,     8,    88,     8,     6,     7,
      13,    29,     3,    63,    33,    65,    63,     5,    65,    38,
      63,     0,    65,     6,     7,    37,    45,    46,    47,    66,
      56,    57,    58,    59,    60,    54,    62,    62,    57,     9,
      58,    59,    60,    10,    62,     6,     7,    11,   130,    48,
      49,    32,    33,     8,    73,    74,    75,    76,    77,    78,
      63,     8,    63,    82,     6,     7,    37,    63,    37,    37,
      89,    90,    91,    63,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   168,    37,   107,    37,
      63,   110,    37,    68,    68,    67,   115,     6,     7,   118,
      13,    66,    11,    12,    13,    68,    68,    64,    68,    68,
      64,    64,    21,     5,    23,    66,    25,    26,    27,    28,
      37,    30,     6,     7,     6,     7,     8,    11,    12,    66,
     149,    11,    14,    15,    16,    17,    18,    21,    13,    23,
       4,    25,    26,    27,    28,     6,    30,    56,    57,    31,
      11,    12,    67,   172,    66,   174,     4,    13,    11,    68,
      21,    11,    23,     5,    25,    26,    27,    28,     4,    30,
      67,    67,    56,    57,    59,    56,     5,    19,    20,    62,
      22,    86,    86,    -1,    68,    -1,    -1,    29,    -1,    -1,
      19,    20,    -1,    22,    -1,    56,    57,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    68,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    19,    20,     4,    22,     6,     7,
       8,    -1,    -1,    -1,    29,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    19,    20,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    31,    29,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    19,    20,
      -1,    22,    -1,    -1,    69,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    69,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    19,    20,    -1,    22,    -1,    -1,    69,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    19,    20,    -1,    22,
      -1,    -1,    69,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      19,    20,    -1,    22,    67,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    71,     5,     0,    72,     4,     6,     7,     8,
      14,    15,    16,    17,    18,    31,    73,    74,    84,    37,
      66,     6,     7,    75,    76,     6,     7,    78,    79,     6,
       7,    81,    82,     9,    10,     6,    11,    12,    21,    23,
      25,    26,    27,    28,    30,    56,    57,    68,    87,    92,
       8,     8,    92,    11,    37,    37,    63,    37,    37,    63,
      37,    37,    63,     7,    13,    85,    92,     6,     7,    86,
      48,    49,    92,    68,    68,    68,    68,    68,    68,    92,
      92,    92,    32,    33,    88,    89,    90,    91,     5,    19,
      20,    22,    29,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    62,    67,    92,    64,    76,    92,
      64,    79,    13,    64,    82,    66,     8,    13,    63,    66,
       8,    63,    92,    92,    92,    92,    92,    92,    69,    92,
       5,    89,    91,    73,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    37,
      77,    92,    80,    92,    13,    83,    92,     7,    92,    11,
       6,     7,    69,    69,    69,    69,    69,    69,     5,    73,
       4,    92,    63,    65,    63,    65,    63,    65,    67,    66,
      67,    66,    73,     4,    92,    92,    13,    11,    11,     4,
      67,    67
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
#line 225 "project.y"
    {
                    printf("\n\n     -------Program Compiled Successfully-------\n\n\n");
                    exit(-1);
                ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 231 "project.y"
    {;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 232 "project.y"
    {;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 235 "project.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 236 "project.y"
    {;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 238 "project.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 239 "project.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 240 "project.y"
    {;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 241 "project.y"
    {;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 257 "project.y"
    {
                            int declared = getVariableIndex((yyvsp[(1) - (3)].string));
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

  case 17:

/* Line 1455 of yacc.c  */
#line 271 "project.y"
    {
                            int value = 0;
                            insertData((yyvsp[(1) - (1)].string), &value, 0, varCount, 1, 0);
                            varCount++;
                        ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 277 "project.y"
    {
                            insertData((yyvsp[(1) - (1)].string), tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 282 "project.y"
    {
                            insertData((yyvsp[(1) - (5)].string), tmpInteger, 0, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpInteger);
                        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 292 "project.y"
    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = (yyvsp[(3) - (3)].real);
                    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 298 "project.y"
    {
                        array_size++;
                        tmpInteger = realloc(tmpInteger, array_size*sizeof(int));
                        tmpInteger[array_size-1] = (yyvsp[(1) - (1)].real);
                    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 312 "project.y"
    {
                            int declared = getVariableIndex((yyvsp[(1) - (3)].string));
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

  case 25:

/* Line 1455 of yacc.c  */
#line 326 "project.y"
    {
                            double value = 0;
                            insertData((yyvsp[(1) - (1)].string), &value, 1, varCount, 1, 0);
                            varCount++;
                        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 332 "project.y"
    {
                            insertData((yyvsp[(1) - (1)].string), tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                        ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 337 "project.y"
    {
                            insertData((yyvsp[(1) - (5)].string), tmpDouble, 1, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpDouble);
                        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 347 "project.y"
    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (yyvsp[(3) - (3)].real);
                    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 353 "project.y"
    {
                        array_size++;
                        tmpDouble = realloc(tmpDouble, array_size*sizeof(double));
                        tmpDouble[array_size-1] = (double)(yyvsp[(1) - (1)].real);
                    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 367 "project.y"
    {
                            int declared = getVariableIndex((yyvsp[(1) - (3)].string));
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

  case 33:

/* Line 1455 of yacc.c  */
#line 381 "project.y"
    {
                            char *value;
                            insertData((yyvsp[(1) - (1)].string), &value, 2, varCount, 1, 0);
                            varCount++;
                        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 387 "project.y"
    {
                            insertData((yyvsp[(1) - (1)].string), tmpString, 2, varCount, array_size, 1);
                            varCount++;
                        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 392 "project.y"
    {
                            insertData((yyvsp[(1) - (5)].string), tmpString, 2, varCount, array_size, 1);
                            varCount++;
                            array_size=0;
                            free(tmpString);
                        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 402 "project.y"
    {
                        array_size++;
                        tmpString = realloc(tmpString, array_size*sizeof(char));
                        tmpString[array_size-1] = (yyvsp[(3) - (3)].string);
                    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 408 "project.y"
    {
                        array_size++;
                        tmpString = realloc(tmpString, array_size*sizeof(char));
                        tmpString[array_size-1] = (yyvsp[(1) - (1)].string);
                    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 416 "project.y"
    {
                    int index = getVariableIndex((yyvsp[(1) - (3)].string));
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", (yyvsp[(1) - (3)].string));
                    }
                    else
                    {
                        {
                            if (vptr[index].type == 1)
                                vptr[index].dval[0] = (yyvsp[(3) - (3)].real);
                            if (vptr[index].type == 0)
                                vptr[index].ival[0] = (yyvsp[(3) - (3)].real);
                        }
                    }
                ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 433 "project.y"
    {
                    int id = (yyvsp[(3) - (6)].integer);
                    int index = getVariableIndex((yyvsp[(1) - (6)].string));
                    if (index == -1)
                    {
                         printf("there is no variable named %s.\n", (yyvsp[(1) - (6)].string));
                    }
                    else
                    {
                        if(id>=vptr[index].size){
                             printf("Array out of range\n");
                        }
                        else
                        {
                            if (vptr[index].type == 1)
                                vptr[index].dval[id] = (yyvsp[(6) - (6)].real);
                            if (vptr[index].type == 0)
                                vptr[index].ival[id] =  (yyvsp[(6) - (6)].real);
                        }
                    }
                ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 458 "project.y"
    {
                if(floor((yyvsp[(3) - (3)].real))==ceil((yyvsp[(3) - (3)].real)))
                printf("Value: %d\n",(int)(yyvsp[(3) - (3)].real));
                else
                printf("Value: %lf\n",(yyvsp[(3) - (3)].real));
            ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 465 "project.y"
    {printVariable((yyvsp[(3) - (3)].string));;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 467 "project.y"
    {printArrayIndex((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].integer));;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 469 "project.y"
    {printf("%s\n",(yyvsp[(2) - (2)].string));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 472 "project.y"
    {
                if(floor((yyvsp[(1) - (1)].real))==ceil((yyvsp[(1) - (1)].real)))
                printf("Value: %d\n",(int)(yyvsp[(1) - (1)].real));
                else
                printf("Value: %lf\n",(yyvsp[(1) - (1)].real));
            ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 479 "project.y"
    {printf("%s\n",(yyvsp[(1) - (1)].string));;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 483 "project.y"
    {printVariable((yyvsp[(1) - (1)].string));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 485 "project.y"
    {printArrayIndex((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].real));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 491 "project.y"
    {takeInput((yyvsp[(3) - (3)].string),0);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 493 "project.y"
    {takeInput((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].integer));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 495 "project.y"
    {takeInput((yyvsp[(1) - (1)].string),0);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 497 "project.y"
    {takeInput((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].integer));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 503 "project.y"
    {
                    int isTrue = (fabs((yyvsp[(1) - (4)].real))>1e-9);
                    if(isTrue){
                        printf("IF block: TRUE.\n");
                        conditionMatched = 1;
                    }
                    else
                    {
                        printf("IF block: FALSE.\n");
                    }
                ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 522 "project.y"
    {
                    
                    if(conditionMatched==0)
                    {
                            printf("ELSE block: FALSE.\n");
                            conditionMatched = 1;
                    }
                    else
                    {
                            printf("ELSE block: TRUE.\n");
                    }
                      
                ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 540 "project.y"
    {
                    if(conditionMatched==0)
                    {
                        int isTrue = (fabs((yyvsp[(2) - (5)].real))>1e-9);
                        if(isTrue)
                        {
                            printf("ELIF block: TRUE.\n");
                            conditionMatched = 1;
                        }
                        else
                        {
                            printf("ELIF block: FALSE.\n");
                        }
                       
                    }
                    else
                    {
                        printf("ELIF block: TRUE.\n");
                    }
                    
                ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 567 "project.y"
    {(yyval.real)=(yyvsp[(1) - (1)].integer);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 569 "project.y"
    {(yyval.real)=(yyvsp[(1) - (1)].real);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 572 "project.y"
    {
                int id = getVariableIndex((yyvsp[(1) - (1)].string));
                if(id==-1) printf("Variable %s already doesn't exist\n",(yyvsp[(1) - (1)].string));
                else if(vptr[id].type==2){
                    printf("String: %s\n",vptr[id].sval[0]);
                }
                else if(vptr[id].type==0) (yyval.real) = vptr[id].ival[0];
                else (yyval.real) = vptr[id].dval[0];
            ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 581 "project.y"
    {(yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 583 "project.y"
    {(yyval.real) = -(yyvsp[(2) - (2)].real);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 585 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) + (yyvsp[(3) - (3)].real);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 587 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) - (yyvsp[(3) - (3)].real);;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 589 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) * (yyvsp[(3) - (3)].real);;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 591 "project.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) / (yyvsp[(3) - (3)].real);;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 593 "project.y"
    {(yyval.real) = pow((yyvsp[(1) - (3)].real),(yyvsp[(3) - (3)].real));;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 595 "project.y"
    {(yyval.real) = (int)(yyvsp[(1) - (3)].real) % (int)(yyvsp[(3) - (3)].real);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 597 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) < (yyvsp[(3) - (3)].real));;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 599 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) > (yyvsp[(3) - (3)].real));;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 601 "project.y"
    {{(yyval.real) = ((yyvsp[(1) - (3)].real) <= (yyvsp[(3) - (3)].real));};}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 603 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) >= (yyvsp[(3) - (3)].real));;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 605 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) == (yyvsp[(3) - (3)].real));;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 607 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) != (yyvsp[(3) - (3)].real));;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 609 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) && (yyvsp[(3) - (3)].real));;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 611 "project.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) || (yyvsp[(3) - (3)].real));;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 613 "project.y"
    {(yyval.real) = ((int)(yyvsp[(1) - (3)].real) ^ (int)(yyvsp[(3) - (3)].real));;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 615 "project.y"
    {(yyval.real) = !(yyvsp[(2) - (2)].real);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 617 "project.y"
    {(yyval.real) = (yyvsp[(2) - (3)].real);}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 619 "project.y"
    {(yyval.real) = sin((yyvsp[(3) - (4)].real));;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 621 "project.y"
    {(yyval.real) = cos((yyvsp[(3) - (4)].real));;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 623 "project.y"
    {(yyval.real) = tan((yyvsp[(3) - (4)].real));;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 625 "project.y"
    {(yyval.real) = log10((yyvsp[(3) - (4)].real));;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 627 "project.y"
    {(yyval.real) = log((yyvsp[(3) - (4)].real));;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 629 "project.y"
    {(yyval.real) = sqrt((yyvsp[(3) - (4)].real));;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 632 "project.y"
    {
                int id = getVariableIndex((yyvsp[(1) - (2)].string));
                if(id==-1) printf("Variable %s already exists",(yyvsp[(1) - (2)].string));
                else if(vptr[id].type==2) printf("Not Possible for String");
                else if(vptr[id].type==0){
                    vptr[id].ival[0]++;
                    (yyval.real) = vptr[id].ival[0];
                }
                else{
                    vptr[id].dval[0]+=1;
                    (yyval.real)=vptr[id].dval[0];
                }
            
            ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 647 "project.y"
    {
                int id = getVariableIndex((yyvsp[(1) - (2)].string));
                if(id==-1) printf("Variable %s already exists",(yyvsp[(1) - (2)].string));
                else if(vptr[id].type==2) printf("Not Possible for Strng");
                else if(vptr[id].type==0){
                    vptr[id].ival[0]++;
                    (yyval.real) = vptr[id].ival[0];
                }
                else{
                    vptr[id].dval[0]+=1;
                    (yyval.real)=vptr[id].dval[0];
                }
            ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 661 "project.y"
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
#line 2571 "project.tab.c"
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
#line 673 "project.y"



int main(int argc, char **argv)
{
//yydebug= 1;
    vptr = realloc(vptr,8*sizeof(var));
    varTaken=100;
    //yyin = fopen (argv[1],"r");
	yyin = freopen("myinput.txt","r",stdin);
	yyout = freopen("out.txt","w",stdout);
    printf("\n\n     -------Starting Program Execution-------\n\n\n");
	yyparse();
	return 0;
} 



