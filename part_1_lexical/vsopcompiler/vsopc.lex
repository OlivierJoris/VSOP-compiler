%option noyywrap

%{
  #include <iostream>
  #include <fstream>
  #include <cstdlib>
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
int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cerr << "Program usage: ./vsopc -l <SOURCE-FILE>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string flag = argv[1];

    if(flag == "-l")
    {
        std::string fileName = argv[2];
        std::cout << "Lexer on " << fileName << std::endl;
        FILE *f = fopen(argv[2], "r");
         if(!f)
        {
            std::cerr << "Can't open file " << fileName << std::endl;
            return EXIT_FAILURE;
        }

        yyin = f;

        
    }

    return EXIT_SUCCESS;
}
