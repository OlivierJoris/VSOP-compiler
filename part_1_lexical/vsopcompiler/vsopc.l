%option noyywrap

%{
  #include "vsopc.tab.h"
  #include <iostream>
  #include <string>
  #include <cstdlib>

  /* source : https://stackoverflow.com/questions/656703/how-does-flex-support-bison-location-exactly */
  #define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line; \
    yylloc.first_column = yylloc.last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc.last_line++; \
            yylloc.last_column = 1; \
        } \
        else { \
            yylloc.last_column++; \
        } \
    }

    extern int yylex();
%}

lowercase-letter [a-z]
uppercase-letter [A-Z]
letter {lowercase-letter}|{uppercase-letter}
digit [0-9]
hex-digit {digit}|[a-f]|[A-F]
wrong-hex-digit {digit}|{lowercase-letter}|{uppercase-letter}
bin-digit [0-1]

/* Whitespace */
whitespace [ \t\n\f\r]+

/* Comments */
comment1Line "//"[^\n]*\n

/* Integer literals */
integer-literal-decimal {digit}+
integer-literal-hexadecimal "0x"{hex-digit}+
error-hex-integer-literal "0x"{wrong-hex-digit}+

/* Type identifiers */
type-identifier {uppercase-letter}({letter}|{digit}|_)*

/* Object Identifiers */
object-identifier {lowercase-letter}({letter}|{digit}|_)*

/* String literals */
escape-sequence [btnr\"\\]|(x{hex-digit}{hex-digit})|(\n[ \t]*)
escaped-char \\{escape-sequence}
regular-char [^\"\\]
string-literal \"({regular-char}|{escaped-char})*\"

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

{whitespace}          {/* No action and no return */}
{comment1Line}        {/* No action and no return */}

{integer-literal-decimal}     {
    yylval.intValue = atoi(yytext);
    return INTEGER_LITERAL;
}

{integer-literal-hexadecimal} {
    std::string integer;
    integer = yytext;
    yylval.intValue = stoi(integer, 0, 16);
    return INTEGER_LITERAL;
}

{error-hex-integer-literal} /* invalid hex integer literal */ {
    yylval.stringValue = yytext;
    return INVALID_HEX_NUMBER;
}

{type-identifier} {
    yylval.stringValue = yytext;
    return TYPE_IDENTIFIER;
}

{object-identifier} {
    yylval.stringValue = yytext;
    return OBJECT_IDENTIFIER;
}

. {
    yylval.stringValue = yytext;
    return INVALID_CHAR;
}

%%

