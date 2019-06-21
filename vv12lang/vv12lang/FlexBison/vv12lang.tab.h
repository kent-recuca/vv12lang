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
    LOCAL_IDENTIFIER = 259,
    INT_LITERAL = 260,
    DOUBLE_LITERAL = 261,
    STR_LITERAL = 262,
    CRLF = 263,
    ADD = 264,
    SUB = 265,
    MUL = 266,
    DIV = 267,
    EQ = 268,
    NE = 269,
    LT = 270,
    GT = 271,
    LE = 272,
    GE = 273,
    SEMICOLON = 274,
    COMMA = 275,
    MULASS = 276,
    DIVASS = 277,
    ADDASS = 278,
    SUBASS = 279,
    ASS = 280,
    PRINTN = 281,
    PRINT = 282,
    WHILE = 283,
    IF = 284,
    ELSE = 285,
    FOR = 286,
    BREAK = 287,
    CONTINUE = 288,
    RETURN = 289,
    FUNCTION = 290,
    LC = 291,
    RC = 292,
    LP = 293,
    RP = 294
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
	vv12::ParameterList* parameterList;
	vv12::ArgumentList* argumentList;
    vv12::Root* root;

#line 110 "vv12lang.tab.h" /* yacc.c:1913  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_VV12LANG_TAB_H_INCLUDED  */
