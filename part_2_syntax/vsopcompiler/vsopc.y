%{
    #include <iostream>

    const std::string PROGRAM_USAGE = "Program usage: ./vsopc -l <SOURCE-FILE> or ./vsopc -p <SOURCE-FILE>";

    extern FILE *yyin;
    std::string fileName;

    int yylex();

    void yyerror(const std::string message);
%}

%union{
    int intValue;
    char *stringValue;
}

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
%token LOWER_EQUAL "<="
%token ASSIGN "<-"

%token INVALID_HEX_NUMBER
%token INVALID_CHAR
%token INVALID_EOF_STRING
%token INVALID_EOF_COMMENT
%token INVALID_INTEGER_LITERAL
%token <intValue> INTEGER_LITERAL
%token <stringValue> TYPE_IDENTIFIER
%token <stringValue> OBJECT_IDENTIFIER
%token <stringValue> STRING_LITERAL

%right ASSIGN
%left AND
%right NOT
%nonassoc LOWER LOWER_EQUAL EQUAL
%left PLUS MINUS
%left TIMES DIV
%right UNARYMINUS ISNULL
%right POW
%left DOT

%locations

%start Program

%%

Program: Class

Class:  /* */
        | Class CLASS TYPE_IDENTIFIER ClassBody {std::cout << "Class named " << $3 << std::endl;}
        | Class CLASS TYPE_IDENTIFIER EXTENDS TYPE_IDENTIFIER ClassBody {std::cout << "Extended class named " << $3 << std::endl;}
        ;

ClassBody: LBRACE ClassBodyFieldMethod RBRACE {std::cout << "Class body" << std::endl;};
ClassBodyFieldMethod: /* */
        | ClassBodyFieldMethod Field
        | ClassBodyFieldMethod Method
        ;

Field: OBJECT_IDENTIFIER COLON Type SEMICOLON {std::cout << "Class field " << $1 << std::endl;}
        | OBJECT_IDENTIFIER COLON Type ASSIGN Expr SEMICOLON {std::cout << "Class field (with value) " << $1 << std::endl;}
        ;

Method: OBJECT_IDENTIFIER LPAR Formals RPAR COLON Type Block{std::cout << "Method " << $1 << std::endl;};

Type: TYPE_IDENTIFIER
        | INT32
        | BOOL
        | STRING
        | UNIT
        ;

Formals: /* */
        | Formal
        | Formals COMMA Formal
        ;

Formal: OBJECT_IDENTIFIER COLON Type {std::cout << "Formal " << $1 << std::endl;};

Block: LBRACE Expr BlockExpr RBRACE {std::cout << "Found block" << std::endl;};
BlockExpr: /* */
        | SEMICOLON Expr BlockExpr
        ;

Expr: WHILE Expr DO Expr
        | OBJECT_IDENTIFIER ASSIGN Expr
        | NOT Expr
        | Expr AND Expr
        | Expr LOWER_EQUAL Expr
        | Expr LOWER Expr
        | Expr EQUAL Expr
        | Expr MINUS Expr
        | Expr PLUS Expr
        | Expr DIV Expr
        | Expr TIMES Expr
        | Expr POW Expr
        | MINUS Expr %prec UNARYMINUS
        | ISNULL Expr
        | OBJECT_IDENTIFIER LPAR Args RPAR
        | Expr DOT OBJECT_IDENTIFIER LPAR Args RPAR
        | NEW TYPE_IDENTIFIER
        | OBJECT_IDENTIFIER
        | SELF
        | Literal
        | LPAR RPAR
        | LPAR Expr RPAR
        | Block
        ;

Args: /* */
        | Expr ArgsExprList
        ;
ArgsExprList: /* */
        | COMMA Expr ArgsExprList
        ;

Literal: INTEGER_LITERAL
        | STRING_LITERAL
        | BooleanLiteral
        ;

BooleanLiteral: TRUE
        | FALSE
        ;

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
        else
            ret += hexConvert(*string);
        
        ++string;
    }

    return ret + "\"";
}

int main(int argc, char** argv){
    /* Check arguments */
    if(argc != 3){
        std::cerr << PROGRAM_USAGE << std::endl;
        return EXIT_FAILURE;
    }

    /* Check if expected option */
    std::string flag = argv[1];
    if (flag != "-l" && flag != "-p") {
        std::cerr << PROGRAM_USAGE << std::endl;
        return EXIT_FAILURE;
    }

    /* Open vsop source file */
    fileName = argv[2];
    yyin = fopen(argv[2], "r");
    if(!yyin){
        std::cerr << "Can't open file " << fileName << std::endl;
        return EXIT_FAILURE;
    }

    /* Start lexer */
    if(flag == "-l"){
        int token;

        while((token = yylex()) != 0){
            switch(token)
            {
                case INVALID_HEX_NUMBER:
                    yyerror(std::string("invalid hexadecimal number ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                case INVALID_CHAR:
                    yyerror(std::string("invalid character ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                case INVALID_EOF_STRING:
                    yyerror(std::string("unexpected end-of-file without \" closing"));
                    return EXIT_FAILURE;
                case INVALID_EOF_COMMENT:
                    yyerror(std::string("unexpected end-of-file without *) closing"));
                    return EXIT_FAILURE;
                case INVALID_INTEGER_LITERAL:
                    yyerror(std::string("invalid literal value ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                default:
                    break;
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
                case LOWER_EQUAL:
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
    }

    /* Start parser */
    if(flag == "-p") {
        std::cout << "* ENTERING PARSING MODE *" << std::endl;
        if(yyparse()) {
            std::cerr << "! Error while parsing !" << std::endl;
            return EXIT_FAILURE;
        }else{
            std::cout << "* Parsing done *" << std::endl;
        }
    }

    fclose(yyin);
    return EXIT_SUCCESS;
}
