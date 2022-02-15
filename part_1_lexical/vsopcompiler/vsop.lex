%{
  /* definitions of token classes
     IF, THEN, ELSE, ID, NUMBER, RELOP
     and attributes LT, LE, EQ, NE, GT, GE */
  int installID(void);
  int installNum(void);
%}

/* regular definitions */
delim    [ \t\n]
ws       {delim}+
letter   [A-Za-z]
digit    [0-9]
id       {letter}({letter}|{digit})*
number   {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%
{ws}     {/* no action and no return */ }
"if"     {return IF;}
"then"   {return THEN;}
"else"   {return ELSE;}
{id}     {yylval = installID(); return ID;}
{number} {yylval = installNum(); return NUMBER;}
"<"      {yylval = LT; return RELOP;}
"<="     {yylval = LE; return RELOP;}
"="      {yylval = EQ; return RELOP;}
"<>"     {yylval = NE; return RELOP;}
">"      {yylval = GT; return RELOP;}
">="     {yylval = GE; return RELOP;}

%%
int installID(void)
{/* function to install the lexeme, whose
    first character is pointed to by yytext,
    and whose length is yyleng, into the
    symbol table and return a pointer thereto
 */
}

int installNum(void)
{/* similar to installID, but puts numerical
    constants into a separate table */
}
