%option noyywrap

%{
  #include "vsopc.tab.h"
  #include <iostream>
  #include <string>
  #include <cstdlib>
  #include <stack>

  /* 
     Update yylloc
     source : https://stackoverflow.com/questions/656703/how-does-flex-support-bison-location-exactly 
  */
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

    unsigned int open_comments_nb = 0;
    std::stack<YYLTYPE> location_stack;
    std::string string_buf;

    /* Call on (* */
    void start_comment(){
        ++open_comments_nb;
        location_stack.push(yylloc);
    }

    /* Call on *) */
    void end_comment(){
        --open_comments_nb;
        location_stack.pop();
    }

    /* Call when a string is started with " */
    void start_string(){
        string_buf = "";
        location_stack.push(yylloc);
    }

    /* Call when a string is ended with " */
    YYLTYPE end_string(){
        yylval.stringValue = &string_buf[0];
        YYLTYPE ret = location_stack.top();
        location_stack.pop();

		ret.last_line = yylloc.last_line;
		ret.last_column = yylloc.last_column;

		return ret;
    }

    extern int yylex();
%}

/* Base */
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
comment1Line "//"[^\n\0]*

/* Integer literals */
integer-literal-decimal {digit}+
integer-literal-hexadecimal "0x"{hex-digit}+
error-hex-integer-literal "0x"{wrong-hex-digit}+
error-integer-literal {integer-literal-decimal}({wrong-hex-digit}|_)

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

"and" {return AND;}
"bool" {return BOOL;}
"class" {return CLASS;}
"do" {return DO;}
"else" {return ELSE;}
"extends" {return EXTENDS;}
"false" {return FALSE;}
"if" {return IF;}
"in" {return IN;}
"int32" {return INT32;}
"isnull" {return ISNULL;}  
"let" {return LET;}
"new" {return NEW;}
"not" {return NOT;}
"self" {return SELF;}
"string" {return STRING;}
"then" {return THEN;}
"true" {return TRUE;}
"unit" {return UNIT;}
"while" {return WHILE;}
"{" {return LBRACE;}
"}" {return RBRACE;}
"(" {return LPAR;}
")" {return RPAR;}
":" {return COLON;}
";" {return SEMICOLON;}
"," {return COMMA;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return DIV;}
"^" {return POW;}
"." {return DOT;}
"=" {return EQUAL;}
"<=" {return LOWER-EQUAL;}
"<-" {return ASSIGN;}
"<" {return LOWER;}

{whitespace} {/* No action and no return */}
{comment1Line} {/* No action and no return */}

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

{error-integer-literal} {
    yylval.stringValue = yytext;
    return INVALID_INTEGER_LITERAL;
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
    if(open_comments_nb == 0)
        BEGIN(INITIAL);
}

<comment_multi>[^\0] {/* No action and no return */}

<comment_multi><<EOF>> {
    YYLTYPE ret = location_stack.top();
    location_stack.pop();

	ret.last_line = yylloc.last_line;
	ret.last_column = yylloc.last_column;

    yylloc = ret;

    return INVALID_EOF_COMMENT;
}

\" {
    start_string();
    BEGIN(string);
}

<string>\" {
    yylloc = end_string();
    BEGIN(INITIAL);
    return STRING_LITERAL;
}

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
            yytext[0] = '0';
            string_buf += std::strtol(&yytext[0], NULL, 16);
            break;
        case '\n':
            break;
        default:
            string_buf += yytext[1];
            break;
    }
}

<string>{regular-char}+ {string_buf += yytext;}

<string><<EOF>> {
    YYLTYPE ret = location_stack.top();
    location_stack.pop();

	ret.last_line = yylloc.last_line;
	ret.last_column = yylloc.last_column;

    yylloc = ret;

    return INVALID_EOF_STRING;
}

<*>(.|\n|\r) {
    yylval.stringValue = yytext;
    return INVALID_CHAR;
}

<<EOF>> {return 0;}

%%
