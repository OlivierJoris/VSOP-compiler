%{
    #include <iostream>

    extern FILE *yyin;
    std::string fileName;

    int yylex();

    void yyerror(const std::string message);
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
%token INVALID_EOF_STRING
%token INVALID_EOF_COMMENT

%union{
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

void yyerror(const std::string message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": " << "lexical error: ";
    std::cerr << message << std::endl;
}

/* Converts a character to its hexadecimal value */
static std::string hexConvert(char character){
    std::string ret = "\\xhh";
    std::string ref = "0123456789abcdef";

    ret[2] = ref[character / 16];
    ret[3] = ref[character % 16];

    return ret;
}

/* Encode a string according to the statement */
static std::string encodeString(char *string){
    std::string ret = "\"";

    while(*string){
        if(*string != '\"' && *string != '\\'){
            if(*string >= 32 && *string <= 126)
                ret += *string;
            else 
                ret += hexConvert(*string);
        }
        else{
            if(*string == '\\'){
                ret += hexConvert(*string);
                break;
            }
        }

        ++string;
    }

    return ret + "\"";
}

int main(int argc, char** argv){
    if(argc != 3){
        std::cerr << "Program usage: ./vsopc -l <SOURCE-FILE>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string flag = argv[1];

    if(flag == "-l"){
        fileName = argv[2];

        yyin = fopen(argv[2], "r");
        if(!yyin){
            std::cerr << "Can't open file " << fileName << std::endl;
            return EXIT_FAILURE;
        }

        int token;

        while((token = yylex()) != 0){
            if(token == INVALID_HEX_NUMBER){
                yyerror(std::string("invalid hexadecimal number ") + std::string(yylval.stringValue));
                return EXIT_FAILURE;
            }
            if(token == INVALID_CHAR){            
                yyerror(std::string("invalid character ") + std::string(yylval.stringValue));
                return EXIT_FAILURE;
            }
            if(token == INVALID_EOF_STRING){
                yyerror(std::string("unexpected end-of-file without \" closing"));
                return EXIT_FAILURE;
            }
            if(token == INVALID_EOF_COMMENT){
                yyerror(std::string("unexpected end-of-file without *) closing"));
                return EXIT_FAILURE;
            }

            std::cout << yylloc.first_line << "," << yylloc.first_column << ",";
            switch(token){
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
			    case TYPE_IDENTIFIER:
                    std::cout << "type-identifier," << yylval.stringValue;
                    break;
			    case OBJECT_IDENTIFIER:
                    std::cout << "object-identifier," << yylval.stringValue;
                    break;
                case STRING_LITERAL:
                    std::cout << "string-literal," << encodeString(yylval.stringValue);
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
