%option noyywrap

%{
  #include "vsopc.tab.h"

  /* source : https://stackoverflow.com/questions/656703/how-does-flex-support-bison-location-exactly */
  #define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line; \
    yylloc.first_column = yylloc.last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc.last_line++; \
            yylloc.last_column = 0; \
        } \
        else { \
            yylloc.last_column++; \
        } \
    }

    extern int yylex();
%}

lowercase_letter    [a-z]
uppercase_letter    [A-Z]
letter              {lowercase_letter}|{uppercase_letter}
bin-digit           [0-1]
digit               [0-9]
hex-digit           {digit}|[a-f]|[A-F]
whitespace          [ \t\n\f\r]+
single_line_comment "//"[^\n]*
integer-litteral    {digit}+|"0x"{hex-digit}+
type-identifier     {uppercase_letter}({letter}|{digit}|_)*
object-identifier   lowercase_letter({letter}|{digit}|_)*
escape-sequence     [btnr\"\\]|(x{hex-digit}{hex-digit})|(\n[ |\t])
escaped-char        \\{escape-sequence}
regular-char        [^{escaped-char}] 

%%

"and"       {return AND;}
"bool"      {return BOOL;}
"class"     {return CLASS;}
"do"        {return DO;}
"else"      {return ELSE;}
"extends"   {return EXTENDS;}
"false"     {return FALSE;}
"if"        {return IF;}
"in"        {return IN;}
"int32"     {return INT32;}
"isnull"    {return ISNULL;}  
"let"       {return LET;}
"new"       {return NEW;}
"not"       {return NOT;}
"self"      {return SELF;}
"string"    {return STRING;}
"then"      {return THEN;}
"true"      {return TRUE;}
"unit"      {return UNIT;}
"while"     {return WHILE;}
"{"		    {return LBRACE;}
"}"			{return RBRACE;}
"("			{return LPAR;}
")"			{return RPAR;}
":"			{return COLON;}
";"			{return SEMICOLON;}
","			{return COMMA;}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return TIMES;}
"/"			{return DIV;}
"^"		    {return POW;}
"."			{return DOT;}
"="			{return EQUAL;}
"<="		{return LOWER-EQUAL;}
"<-"		{return ASSIGN;}
"<"			{return LOWER;}

{whitespace} {/* No action and no return */}

%%

