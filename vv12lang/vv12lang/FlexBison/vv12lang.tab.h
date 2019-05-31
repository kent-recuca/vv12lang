/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

#ifndef YY_YY_VV12LANG_TAB_H_INCLUDED
# define YY_YY_VV12LANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "vv12lang.y" /* yacc.c:1913  */

#include "../vv12lang/proc.h"

#line 48 "vv12lang.tab.h" /* yacc.c:1913  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    INT_LITERAL = 259,
    DOUBLE_LITERAL = 260,
    STR_LITERAL = 261,
    CRLF = 262,
    ADD = 263,
    SUB = 264,
    MUL = 265,
    DIV = 266,
    EQ = 267,
    NE = 268,
    LT = 269,
    GT = 270,
    LE = 271,
    GE = 272,
    SEMICOLON = 273,
    MULASS = 274,
    DIVASS = 275,
    ADDASS = 276,
    SUBASS = 277,
    ASS = 278,
    PRINTN = 279,
    PRINT = 280,
    WHILE = 281,
    IF = 282,
    FOR = 283,
    LC = 284,
    RC = 285,
    LP = 286,
    RP = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "vv12lang.y" /* yacc.c:1913  */

    const char* fixedString;
    vv12::Expression* expression;
    vv12::Statement* statement;
    vv12::StatementList* statementList;
    vv12::Root* root;

#line 101 "vv12lang.tab.h" /* yacc.c:1913  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_VV12LANG_TAB_H_INCLUDED  */
