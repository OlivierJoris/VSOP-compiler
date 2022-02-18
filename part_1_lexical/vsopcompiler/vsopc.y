%{
    #include <iostream>
    #include <algorithm>

    extern FILE *yyin;

    int yylex();

    void yyerror (char const *s)
    {
        std::cerr << s << std::endl;
    }
%}

%token AND "and"
%token BOOL "bool"
%token CLASS "class"
%token DO "do"
%token ELSE "else"
%token EXTENDS "extends"
%token FALSE "false"
%token IF "if"
%token IN "in"
%token INT32 "int32"
%token ISNULL "isnull"
%token LET "let"
%token NEW "new"
%token NOT "not"
%token SELF "self"
%token STRING "string"
%token THEN "then"
%token TRUE "true"
%token UNIT "unit"
%token WHILE "while"
%token LBRACE "{"
%token RBRACE "}"
%token LPAR "("
%token RPAR ")"
%token COLON ":"
%token SEMICOLON ";"
%token COMMA ","
%token PLUS "+"
%token MINUS "-"
%token TIMES "*"
%token DIV "/"
%token POW "^"
%token DOT "."
%token EQUAL "="
%token LOWER "<"
%token LOWER-EQUAL "<="
%token ASSIGN "<-"
%token INVALID_HEX_NUMBER
%token INVALID_CHAR

%union
{
    int intValue;
    char *stringValue;
}

%token <intValue> INTEGER_LITERAL
%token <stringValue> TYPE_IDENTIFIER
%token <stringValue> OBJECT_IDENTIFIER
%token <stringValue> STRING_LITERAL

%locations

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
        std::string fileNameUppercase = argv[2];
        std::transform(fileNameUppercase.begin(), fileNameUppercase.end(), fileNameUppercase.begin(), ::toupper);

        yyin = fopen(argv[2], "r");
        if(!yyin)
        {
            std::cerr << "Can't open file " << fileName << std::endl;
            return EXIT_FAILURE;
        }

        int token;

        while((token = yylex()) != 0)
        {
            if(token == INVALID_HEX_NUMBER) {
                std::cerr << fileNameUppercase << ":" << yylloc.first_line << ":";
                std::cerr << yylloc.first_column << ": " << "lexical error: invalid hex number ";
                std::cerr << yylval.stringValue << std::endl;
                return -1;
            }
            if(token == INVALID_CHAR) {
                std::cerr << fileNameUppercase << ":" << yylloc.first_line << ":";
                std::cerr << yylloc.first_column << ": " << "lexical error: invalid character ";
                std::cerr << yylval.stringValue << std::endl;
                return -1;
            }

            std::cout << yylloc.first_line << "," << yylloc.first_column << ",";
            switch(token)
            {
                case AND:
                    std::cout << "and";
                    break;
                case BOOL:	
                    std::cout << "bool";								
                    break;
                case CLASS:	
                    std::cout << "class";								
                    break;
                case DO:
                    std::cout << "do";									
                    break;
                case ELSE:
                    std::cout << "else";
                    break;
                case EXTENDS:
                    std::cout << "extends";
                    break;
                case FALSE:
                    std::cout << "false";
                    break;
                case IF:
                    std::cout << "if";
                    break;
                case IN:
                    std::cout << "in";
                    break;
                case INT32:				
                    std::cout << "int32";
                    break;
                case ISNULL:
                    std::cout << "isnull";
                    break;
                case LET:
                    std::cout << "let";
                    break;
                case NEW:
                    std::cout << "new";
                    break;
                case NOT:
                    std::cout << "not";
                    break;
                case SELF:	
                    std::cout << "self";    
                    break;
                case STRING:
                    std::cout << "string";
                    break;
                case THEN:
                    std::cout << "then";						
                    break;
                case TRUE:
                    std::cout << "true";
                    break;
                case UNIT:
                    std::cout << "unit";			
                    break;
                case WHILE:
                    std::cout << "while";
                    break;
                case LBRACE:
                    std::cout << "lbrace";			
                    break;
                case RBRACE:
                    std::cout << "rbrace";
                    break;
                case LPAR:
                    std::cout << "lpar";
                    break;
                case RPAR:		
                    std::cout << "rpar";
                    break;
                case COLON:
                    std::cout << "colon";
                    break;
                case SEMICOLON:
                    std::cout << "semicolon";
                    break;
                case COMMA:
                    std::cout << "comma";
                    break;
                case PLUS:
                    std::cout << "plus";
                    break;
                case MINUS:
                    std::cout << "minus";
                    break;
                case TIMES:
                    std::cout << "times";
                    break;
                case DIV:
                    std::cout << "div";
                    break;
                case POW:
                    std::cout << "pow";
                    break;
                case DOT:
                    std::cout << "dot";
                    break;
                case EQUAL:
                    std::cout << "equal";
                    break;
                case LOWER:
                    std::cout << "lower";
                    break;
                case LOWER-EQUAL:
                    std::cout << "lower-equal";
                    break;
                case ASSIGN:
                    std::cout << "assign";
                    break;
                case INTEGER_LITERAL:
                    std::cout << "integer-literal," << yylval.intValue;		
                    break;
			    case STRING_LITERAL:
                    std::cout << "string-literal," << yylval.stringValue;
                    break;
			    case TYPE_IDENTIFIER:
                    std::cout << "type-identifier," << yylval.stringValue;
                    break;
			    case OBJECT_IDENTIFIER:
                    std::cout << "object-identifier," << yylval.stringValue;
                    break;
                default:
                    break;
            }

            std::cout << std::endl;
        }

        fclose(yyin);
    }

    return EXIT_SUCCESS;
}