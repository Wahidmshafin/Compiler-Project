
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 199 "project.y"

	int integer;
	double real;
	char* string;



/* Line 1676 of yacc.c  */
#line 121 "project.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


