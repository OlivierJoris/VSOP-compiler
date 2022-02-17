%{
    #include <iostream>

    extern FILE *yyin;

    int yylex();

    void yyerror (char const *s)
    {
        std::cerr << s << std::endl;
    }
%}

%%

exp:

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