%{
    #include <iostream>
    #include <vector>
    #include <set>
    #include <cstring>

    #include "AbstractSyntaxTree.hpp"

    #define YYERROR_VERBOSE 1

    const std::string PROGRAM_USAGE = "Program usage: ./vsopc -l <SOURCE-FILE> or ./vsopc -p <SOURCE-FILE>";

    extern FILE *yyin;
    std::string fileName;
    Program *abstractSyntaxTree;

    int yylex();

    void yyerror(const std::string message);
    void lexicalError(const std::string& message);
    void syntaxError(const std::string& message);
%}

%code requires{
    #include "AbstractSyntaxTree.hpp"
}

%define parse.trace
%define parse.lac full
%define parse.error detailed

%union{
    int intValue;
    char *stringValue;
    Expr *expression;
    Formal *formal;
    Formals *formals;
    Args *args;
    Class *cls;
    ClassBody *classBody;
    Field *field;
    Method *method;
    Program *program;
}

%token AND "and"
%token <stringValue> BOOL "bool"
%token CLASS "class"
%token DO "do"
%token ELSE "else"
%token EXTENDS "extends"
%token FALSE "false"
%token IF "if"
%token IN "in"
%token <stringValue> INT32 "int32"
%token ISNULL "isnull"
%token LET "let"
%token NEW "new"
%token NOT "not"
%token SELF "self"
%token <stringValue> STRING "string"
%token THEN "then"
%token TRUE "true"
%token <stringValue> UNIT "unit"
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

%token <stringValue> INVALID_HEX_NUMBER
%token <stringValue> INVALID_CHAR
%token INVALID_EOF_STRING
%token INVALID_EOF_COMMENT
%token <stringValue> INVALID_INTEGER_LITERAL
%token <intValue> INTEGER_LITERAL
%token <stringValue> TYPE_IDENTIFIER 
%token <stringValue> OBJECT_IDENTIFIER
%token <stringValue> STRING_LITERAL

%precedence IF THEN WHILE LET DO IN
%precedence ELSE

%right ASSIGN
%left AND
%right NOT
%nonassoc LOWER LOWER_EQUAL EQUAL
%left PLUS MINUS
%left TIMES DIV
%right UNARYMINUS ISNULL
%right POW
%left DOT
%right EMBEDDED

%nterm <stringValue> Type 
%nterm <expression> Expr Let While If Literal InvalidToken
%nterm <program> Program ProgramContinued
%nterm <cls> Class 
%nterm <classBody> ClassBody 
%nterm <field> Field
%nterm <method> Method
%nterm <args> Block BlockExpr Args ArgsExprList
%nterm <formals> Formals FormalsContinued
%nterm <formal> Formal 

%locations

%start Program

%%

Program: Class ProgramContinued {$2->addClass($1); 
                                 $$ = $2; 
                                 abstractSyntaxTree = $$;};

ProgramContinued:	/* */ { $$ = new Program(); }
				| Class ProgramContinued {$2->addClass($1); 
                                          $$ = $2;};

Class: CLASS TYPE_IDENTIFIER LBRACE ClassBody RBRACE {std::vector<Field*> fields = $4->getFields();
                                                               std::vector<Method*> methods = $4->getMethods();
                                                               $$ = new Class($2, "Object", fields, methods);}
        | CLASS TYPE_IDENTIFIER EXTENDS TYPE_IDENTIFIER LBRACE ClassBody RBRACE {std::vector<Field*> fields = $6->getFields();
                                                                                       std::vector<Method*> methods = $6->getMethods();
                                                                                       $$ = new Class($2, $4, fields, methods);}
        ;

ClassBody: /* */ {$$ = new ClassBody();}
        | Field ClassBody {$2->addField($1);
                                      $$ = $2;}
        | Method ClassBody {$2->addMethod($1);
                                       $$ = $2;}
        ;

Field: OBJECT_IDENTIFIER COLON Type SEMICOLON {$$ = new Field($1, $3, NULL);}
        | OBJECT_IDENTIFIER COLON Type ASSIGN Expr SEMICOLON {$$ = new Field($1, $3, $5);}
        ;

Method: OBJECT_IDENTIFIER LPAR Formals RPAR COLON Type Block{$$ = new Method($1, $3, $6, new Block($7));}
        ;

Type: TYPE_IDENTIFIER {$$ = $1;}
        | INT32       {$$ = (char *) "int32";}
        | BOOL        {$$ = (char *) "bool";} 
        | STRING      {$$ = (char *) "string";}
        | UNIT        {$$ = (char *) "unit";}
        ;

Formals: /* */ {$$ = new Formals();}
        | Formal FormalsContinued {$2->addFormal($1);
                                   $$ = $2;}
        ;
        
FormalsContinued: /* */ {$$ = new Formals();}
                 | COMMA Formal FormalsContinued {$3->addFormal($2);
                                                  $$ = $3;}
                 ;

Formal: OBJECT_IDENTIFIER COLON Type {$$ = new Formal($1, $3);}
        ;

Block: LBRACE Expr BlockExpr RBRACE {$3->addExpr($2);
                                     $$ = $3;}
       ;

BlockExpr: /* */ {$$ = new Args();}
        | SEMICOLON Expr BlockExpr {$3->addExpr($2);
                                    $$ = $3;}
        ;

Expr:     If
        | While
        | Let 
        | OBJECT_IDENTIFIER ASSIGN Expr {$$ = new Assign($1, $3);}
        | NOT Expr {$$ = new Not($2);}
        | Expr AND Expr {$$ = new And($1, $3);}
        | Expr LOWER_EQUAL Expr {$$ = new LowerEqual($1, $3);}
        | Expr LOWER Expr {$$ = new Lower($1, $3);}
        | Expr EQUAL Expr {$$ = new Equal($1, $3);}
        | Expr MINUS Expr {$$ = new Minus($1, $3);}
        | Expr PLUS Expr {$$ = new Plus($1, $3);}
        | Expr DIV Expr {$$ = new Div($1, $3);}
        | Expr TIMES Expr {$$ = new Times($1, $3);}
        | Expr POW Expr {$$ = new Pow($1, $3);}
        | MINUS Expr %prec UNARYMINUS {$$ = new UnaryMinus($2);}
        | ISNULL Expr {$$ = new IsNull($2);}
        | OBJECT_IDENTIFIER LPAR Args RPAR {$$ = new Call(NULL, $1, $3);}
        | Expr DOT OBJECT_IDENTIFIER LPAR Args RPAR {$$ = new Call($1, $3, $5);}
        | NEW TYPE_IDENTIFIER {$$ = new New($2);}
        | OBJECT_IDENTIFIER {$$ = new ObjectIdentifier($1);}
        | SELF {$$ = new Self();}
        | Literal
        | LPAR RPAR {$$ = new Unit();}
        | LPAR Expr RPAR {$$ = $2;}
        | Block {$$ = new Block($1);}
        | InvalidToken
        ;

If: IF Expr THEN Expr {$$ = new If($2, $4, NULL);}
        | IF Expr THEN Expr ELSE Expr {$$ = new If($2, $4, $6);}
        ;

While: WHILE Expr DO Expr {$$ = new While($2, $4);}
        ;

Let: LET OBJECT_IDENTIFIER COLON Type IN Expr {$$ = new Let($2, $4, $6, NULL);}
        | LET OBJECT_IDENTIFIER COLON Type ASSIGN Expr IN Expr {$$ = new Let($2, $4, $8, $6);}
        ;

Args: /* */ {$$ = new Args();}
        | Expr ArgsExprList {$2->addExpr($1); 
                             $$ = $2;}
        ;
ArgsExprList: /* */ {$$ = new Args();}
        | COMMA Expr ArgsExprList {$3->addExpr($2);
                                   $$ = $3;}
        ;

Literal: INTEGER_LITERAL {$$ = new IntegerLiteral($1);}
        | STRING_LITERAL {$$ = new StringLiteral($1);}
        | TRUE {$$ = new BooleanLiteral(true);}
        | FALSE {$$ = new BooleanLiteral(false);} 
        ;

InvalidToken: INVALID_CHAR {lexicalError(std::string("invalid character ") + std::string($1));
                        YYERROR;}
        | INVALID_HEX_NUMBER {lexicalError(std::string("invalid hexadecimal number ") + std::string($1));
                        YYERROR;}
        | INVALID_INTEGER_LITERAL {lexicalError(std::string("invalid literal value ") + std::string($1));
                        YYERROR;}
        | INVALID_EOF_STRING {lexicalError(std::string("unexpected end-of-file without \" closing "));
                        YYERROR;}
        | INVALID_EOF_COMMENT {lexicalError(std::string("unexpected end-of-file without *) closing"));
                        YYERROR;}

%%

void yyerror(const std::string message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": ";
    std::cerr << message << std::endl;
}

void lexicalError(const std::string& message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": " << "lexical error: ";
    std::cerr << message << std::endl;
}

void syntaxError(const std::string& message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": " << "syntax error: ";
    std::cerr << message << std::endl;
}

void semanticError(const std::string& message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": " << "semantic error: ";
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
    if (flag != "-l" && flag != "-p" && flag != "-c") {
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
                    lexicalError(std::string("invalid hexadecimal number ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                case INVALID_CHAR:
                    lexicalError(std::string("invalid character ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                case INVALID_EOF_STRING:
                    lexicalError(std::string("unexpected end-of-file without \" closing"));
                    return EXIT_FAILURE;
                case INVALID_EOF_COMMENT:
                    lexicalError(std::string("unexpected end-of-file without *) closing"));
                    return EXIT_FAILURE;
                case INVALID_INTEGER_LITERAL:
                    lexicalError(std::string("invalid literal value ") + std::string(yylval.stringValue));
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
        abstractSyntaxTree = new Program();
        if(yyparse()) {
            return EXIT_FAILURE;
        }else{
            std::cout << abstractSyntaxTree->eval() << std::endl;
        }
    }

    /* Start semantic analyzer */
    if(flag == "-c") {
        abstractSyntaxTree = new Program();
        if(yyparse()) {
            return EXIT_FAILURE;
        }else{
            
            /* Check for class, field, method, and formal redefinitions */
            for(Class *cls: abstractSyntaxTree->getClasses())
            {
                std::string className = cls->getName();
                if(abstractSyntaxTree->classesMap.find(className) != abstractSyntaxTree->classesMap.end())
                    semanticError("redefinition of class " + className);
                else 
                    abstractSyntaxTree->classesMap[className] = cls;

                for(Field *field: cls->getFields())
                {
                    std::string fieldName = field->getName();
                    if(cls->fieldsMap.find(fieldName) != cls->fieldsMap.end())
                        semanticError("redefinition of field " + fieldName);
                    else
                        cls->fieldsMap[fieldName] = field;
                }

                for(Method *method: cls->getMethods())
                {
                    std::string methodName = method->getName();
                    if(cls->methodsMap.find(methodName) != cls->methodsMap.end())
                        semanticError("redefinition of method " + methodName);
                    else
                        cls->methodsMap[methodName] = method;
                    

                    for(Formal *formal: method->getFormals())
                    {
                        std::string formalName = formal->getName();
                        if(method->formalsMap.find(formalName) != method->formalsMap.end())
                            semanticError("redefinition of the formal " + formalName);
                        else 
                            method->formalsMap[formalName] = formal;
                    }
                }
            }

            /* Check for cycles in inheritance */
            std::set<std::string> parentSet;

            for(Class *cls: abstractSyntaxTree->getClasses())
            {
                std::string parent = cls->getParent();
                while(parent != "Object")
                {
                    if(parentSet.find(parent) != parentSet.end())
                        semanticError("class " + cls->getName() + " cannot extends child class " + parent);
                    
                }
            }
        }
    }

    fclose(yyin);

    return EXIT_SUCCESS;
}
