%option noyywrap

%{
  #include "vsopc.tab.h"
  #include <iostream>
  #include <string>
  #include <cstdlib>
  #include <stack>

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

    std::stack<int> comment_stack;
    std::string string_buf;
    std::stack<YYLTYPE> location_stack;

    void start_comment()
    {
        comment_stack.push(0);
    }

    void end_comment()
    {
        comment_stack.pop();
    }

    void start_string()
    {
        string_buf = "";
        location_stack.push(yylloc);
    }

    void end_string()
    {
        yylval.stringValue = &string_buf[0];
        yylloc = location_stack.top();
        location_stack.pop();
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
escaped-sequence [btnr\"\\]|(x{hex-digit}{hex-digit})|(\n[ \t]*)
escaped-char \\{escaped-sequence}
regular-char [^\"\\\0\n]

%x comment_multi
%x string
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

{integer-literal-decimal} {
    yylval.intValue = atoi(yytext);
    return INTEGER_LITERAL;
}

{integer-literal-hexadecimal} {
    char* integer;
    integer = yytext;
    yylval.intValue = std::stoi(integer, 0, 16);
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

"(*" {
    start_comment();
    BEGIN(comment_multi);
}

<comment_multi>"(*" {
    start_comment();
}

<comment_multi>"*)" {
    end_comment();
    if(comment_stack.empty())
        BEGIN(INITIAL);
}

<comment_multi>[^\0] {/* No action and no return */}

\" {
    start_string();
    BEGIN(string);
}

<string>\" {
    end_string();
    BEGIN(INITIAL);
    return STRING_LITERAL;
}

<string>{regular-char}+ {string_buf += yytext;}

<string>{escaped-char} {
    switch(yytext[1])
    {
        case 'b':
            string_buf += '\b';
            break;
        case 't':
            string_buf += '\t';
            break;
        case 'n':
            string_buf += '\n';
            break;
        case 'r':
            string_buf += '\r';
            break;
        case 'x':
            string_buf += std::strtol(&yytext[0], NULL, 16);
            break;
        default:
            break;
    }
}

. {
    yylval.stringValue = yytext;
    return INVALID_CHAR;
}

%%