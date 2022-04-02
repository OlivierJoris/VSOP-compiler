/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_VSOPC_TAB_H_INCLUDED
# define YY_YY_VSOPC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 23 "vsopc.y"

    #include "AbstractSyntaxTree.hpp"

#line 53 "vsopc.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    AND = 258,                     /* "and"  */
    BOOL = 259,                    /* "bool"  */
    CLASS = 260,                   /* "class"  */
    DO = 261,                      /* "do"  */
    ELSE = 262,                    /* "else"  */
    EXTENDS = 263,                 /* "extends"  */
    FALSE = 264,                   /* "false"  */
    IF = 265,                      /* "if"  */
    IN = 266,                      /* "in"  */
    INT32 = 267,                   /* "int32"  */
    ISNULL = 268,                  /* "isnull"  */
    LET = 269,                     /* "let"  */
    NEW = 270,                     /* "new"  */
    NOT = 271,                     /* "not"  */
    SELF = 272,                    /* "self"  */
    STRING = 273,                  /* "string"  */
    THEN = 274,                    /* "then"  */
    TRUE = 275,                    /* "true"  */
    UNIT = 276,                    /* "unit"  */
    WHILE = 277,                   /* "while"  */
    LBRACE = 278,                  /* "{"  */
    RBRACE = 279,                  /* "}"  */
    LPAR = 280,                    /* "("  */
    RPAR = 281,                    /* ")"  */
    COLON = 282,                   /* ":"  */
    SEMICOLON = 283,               /* ";"  */
    COMMA = 284,                   /* ","  */
    PLUS = 285,                    /* "+"  */
    MINUS = 286,                   /* "-"  */
    TIMES = 287,                   /* "*"  */
    DIV = 288,                     /* "/"  */
    POW = 289,                     /* "^"  */
    DOT = 290,                     /* "."  */
    EQUAL = 291,                   /* "="  */
    LOWER = 292,                   /* "<"  */
    LOWER_EQUAL = 293,             /* "<="  */
    ASSIGN = 294,                  /* "<-"  */
    INVALID_HEX_NUMBER = 295,      /* INVALID_HEX_NUMBER  */
    INVALID_CHAR = 296,            /* INVALID_CHAR  */
    INVALID_EOF_STRING = 297,      /* INVALID_EOF_STRING  */
    INVALID_EOF_COMMENT = 298,     /* INVALID_EOF_COMMENT  */
    INVALID_INTEGER_LITERAL = 299, /* INVALID_INTEGER_LITERAL  */
    INTEGER_LITERAL = 300,         /* INTEGER_LITERAL  */
    TYPE_IDENTIFIER = 301,         /* TYPE_IDENTIFIER  */
    OBJECT_IDENTIFIER = 302,       /* OBJECT_IDENTIFIER  */
    STRING_LITERAL = 303,          /* STRING_LITERAL  */
    UNARYMINUS = 304,              /* UNARYMINUS  */
    EMBEDDED = 305                 /* EMBEDDED  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "vsopc.y"

    int intValue;
    char *stringValue;
    Expr *expression;
    Formal *formal;
    Formals *formals;
    Args *args;
    Class *cls;
    ClassBody *classBody;
    Field *field;
    Method *method;
    Program *program;

#line 134 "vsopc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_VSOPC_TAB_H_INCLUDED  */
