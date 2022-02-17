%option noyywrap

%{
  #include "vsopc.tab.h"
%}

/* REGULAR DEFINITIONS */

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


%%

