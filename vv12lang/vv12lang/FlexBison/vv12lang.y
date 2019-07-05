%{
#include <stdio.h>
#include <stdlib.h>
#include "../vv12lang/proc.h"
#define YYDEBUG 1
extern int yylex(void);
int yyerror(char const *str){
    extern char *yytext;
    extern int gLine;
    vv12::Interpreter::getInp()->syntaxExit(1003, gLine, yytext);
    return 0;
}
%}
%code requires {
#include "../vv12lang/proc.h"
}
%union {
    const char* fixedString;
    vv12::Expression* expression;
    vv12::Statement* statement;
    vv12::StatementList* statementList;
	vv12::ParameterList* parameterList;
	vv12::ArgumentList* argumentList;
	vv12::ArrKeyValueList* arraykeyvalueList;
    vv12::ArrKeytList* arraykeyList;
    vv12::Root* root;
}
%token <fixedString> IDENTIFIER LOCAL_IDENTIFIER
%token <expression>  INT_LITERAL DOUBLE_LITERAL STR_LITERAL
%token CRLF ADD SUB MUL DIV EQ NE LT GT LE GE SEMICOLON COMMA COLON
%token MULASS DIVASS  ADDASS SUBASS ASS PRINTN PRINT WHILE IF ELSE FOR BREAK CONTINUE RETURN FUNCTION ARRAY
%token LC RC LP RP LB RB
%right ASS 
%right ADDASS SUBASS
%right MULASS DIVASS
%left ADD SUB 
%left MUL DIV
%type <expression> constart_expression identifier_expression identifier_array_expression
%type <expression> primary_expression mul_expression add_expression internal_expression
%type <expression> assign_expression expression equality_expression relational_expression postfix_expression
%type <statement> expression_statement internal_statement statement compound_statement iteration_statement selection_statement jump_statement
%type <statement> function_define_statement
%type <statementList> statement_list
%type <arraykeyvalueList> initialize_array_key_value_list
%type <arraykeyList> arraykey_list
%type <argumentList> argument_list
%type <parameterList> parameter_list
%type <root> root
%%
root
    : statement_list
    {
        $$ = vv12::Interpreter::getInp()->createRoot($1);
    }
    ;
statement_list
    : statement
    {
        $$ = vv12::Interpreter::getInp()->createStatementList($1);
    }
    | statement_list statement
    {
        $$ = vv12::Interpreter::getInp()->createStatementList($1,$2);
    }
    ;
statement
    : expression_statement
	| compound_statement
	| selection_statement
	| iteration_statement
	| jump_statement
    | internal_statement
	| function_define_statement
    ;
expression_statement
    : CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::ExpressionStm>();
    }
    | expression CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::ExpressionStm>($1);
    }
	|  LP expression SEMICOLON
	{
		$$ = vv12::Interpreter::getInp()->createStatement<vv12::ExpressionStm>($2);
	}
    ;
compound_statement
    : LC RC
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::BlockStm>();
    }
    | LC statement_list RC
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::BlockStm>($2);
    }
    ;
selection_statement
    : IF LP expression RP statement ELSE statement
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::IfElsStm>($3,$5,$7);
    }
	|IF LP expression RP statement
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::IfStm>($3,$5);
    }
	;
iteration_statement
    : WHILE LP expression RP statement
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::WhileStm>($3,$5);
    }
	| FOR statement expression SEMICOLON expression RP statement
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::ForStm>($2,$3,$5,$7);
    }
	;
jump_statement
    : CONTINUE CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::ContinueStm>();
    }
	| BREAK CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::BreakStm>();
    }
	| RETURN CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::ReturnStm>();
    }
	| RETURN  expression CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::ReturnStm>($2);
    }
    ;
internal_statement
    : PRINTN expression CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::PrintStm>($2,true);
    }
    | PRINT expression CRLF
    {
        $$ = vv12::Interpreter::getInp()->createStatement<vv12::PrintStm>($2,false);
    }
    ;
function_define_statement
    : FUNCTION IDENTIFIER LP parameter_list RP compound_statement
    {
        $$ = vv12::Interpreter::getInp()->createFunctionDefineStm($2,$4,$6);
    }
    ;
parameter_list
    : /*empty*/
    {
        $$ = vv12::Interpreter::getInp()->createParameterList();
    }
    | LOCAL_IDENTIFIER
    {
        $$ = vv12::Interpreter::getInp()->createParameterList($1);
    }
    | parameter_list COMMA LOCAL_IDENTIFIER
    {
        $$ = vv12::Interpreter::getInp()->createParameterList($1,$3);
    }
    ;
expression
    : assign_expression
    ;
assign_expression
    : equality_expression
    | identifier_expression ASS assign_expression
    {
        $$ = vv12::Interpreter::getInp()->createAssExp($1,$3);
    }
	| identifier_array_expression ASS assign_expression
    {
        $$ = vv12::Interpreter::getInp()->createAssignArrExp($1,$3);
    }
    | identifier_expression ADDASS assign_expression
    {
        $$ = vv12::Interpreter::getInp()->createToAssExp($1,$3, vv12::ExpressionType::addAssExp);
    }
    | identifier_expression SUBASS assign_expression
    {
        $$ = vv12::Interpreter::getInp()->createToAssExp($1,$3, vv12::ExpressionType::subAssExp);
    }
    | identifier_expression MULASS assign_expression
    {
        $$ = vv12::Interpreter::getInp()->createToAssExp($1,$3, vv12::ExpressionType::mulAssExp);
    }
    | identifier_expression DIVASS assign_expression
    {
        $$ = vv12::Interpreter::getInp()->createToAssExp($1,$3, vv12::ExpressionType::divAssExp);
    }
    ;
equality_expression
    : relational_expression
    | equality_expression EQ relational_expression
    {
        $$ = vv12::Interpreter::getInp()->createRelationalExp($1,$3,vv12::ExpressionType::eqExp);
    }
	| equality_expression NE relational_expression
    {
        $$ = vv12::Interpreter::getInp()->createRelationalExp($1,$3,vv12::ExpressionType::neExp);
    }
	;
relational_expression
    : add_expression
    | relational_expression LT add_expression
    {
        $$ = vv12::Interpreter::getInp()->createRelationalExp($1,$3,vv12::ExpressionType::ltExp);
    }
    | relational_expression GT add_expression
    {
        $$ = vv12::Interpreter::getInp()->createRelationalExp($1,$3,vv12::ExpressionType::gtExp);
    }
    | relational_expression LE add_expression
    {
        $$ = vv12::Interpreter::getInp()->createRelationalExp($1,$3,vv12::ExpressionType::leExp);
    }
    | relational_expression GE add_expression
    {
        $$ = vv12::Interpreter::getInp()->createRelationalExp($1,$3,vv12::ExpressionType::geExp);
    }
    ;
add_expression
    : mul_expression
    | add_expression ADD mul_expression
    {
        $$ = vv12::Interpreter::getInp()->createBinaryExp($1,$3,vv12::ExpressionType::addExp);
    }
    | add_expression SUB mul_expression
    {
        $$ = vv12::Interpreter::getInp()->createBinaryExp($1,$3,vv12::ExpressionType::subExp);
    }
    ;
mul_expression
    : postfix_expression
    | mul_expression MUL primary_expression
    {
        $$ = vv12::Interpreter::getInp()->createBinaryExp($1,$3,vv12::ExpressionType::mulExp);
    }
    | mul_expression DIV primary_expression
    {
        $$ = vv12::Interpreter::getInp()->createBinaryExp($1,$3,vv12::ExpressionType::divExp);
    }
    ;
postfix_expression
    : primary_expression
    | IDENTIFIER LP argument_list RP
    {
        $$ = vv12::Interpreter::getInp()->createFunctionCallExp($1,$3);
    }
	;
primary_expression
    : identifier_array_expression
    | internal_expression
    | identifier_expression
	| constart_expression
	| STR_LITERAL
    {
        $$ = vv12::Interpreter::getInp()->createStringLiteralExp();
    }
    ;
internal_expression
    : ARRAY LP argument_list RP
    {
        $$ = vv12::Interpreter::getInp()->createArrayInitValueExp($3);
    }
    | ARRAY LP initialize_array_key_value_list RP
    {
        $$ = vv12::Interpreter::getInp()->createArrayInitKeyValueExp($3);
    }
    ;
argument_list
    : /*empty*/
    {
        $$ = vv12::Interpreter::getInp()->createArgumentList();
    }
    | expression
    {
        $$ = vv12::Interpreter::getInp()->createArgumentList($1);
    }
    | argument_list COMMA expression
    {
        $$ = vv12::Interpreter::getInp()->createArgumentList($1,$3);
    }
    ;
initialize_array_key_value_list
    : expression COLON expression
    {
        $$ = vv12::Interpreter::getInp()->createArrKeyValueList($1,$3);
    }
    | initialize_array_key_value_list COMMA expression COLON expression
    {
        $$ = vv12::Interpreter::getInp()->createArrKeyValueList($1,$3,$5);
    }
    ;
identifier_array_expression
    : IDENTIFIER arraykey_list
    {
        $$ = vv12::Interpreter::getInp()->createArrayExp($1,$2,false);
    }
    | LOCAL_IDENTIFIER arraykey_list
    {
        $$ = vv12::Interpreter::getInp()->createArrayExp($1,$2,true);
    }
    ;
arraykey_list
    : LB RB
    {
        $$ = vv12::Interpreter::getInp()->createArrKeytList();
    }
    | LB expression RB
    {
        $$ = vv12::Interpreter::getInp()->createArrKeytList($2);
    }
    | arraykey_list LB expression RB
    {
        $$ = vv12::Interpreter::getInp()->createArrKeytList($1,$3);
    }
    ;
identifier_expression
    : IDENTIFIER
    {
        $$ = vv12::Interpreter::getInp()->createVariableExp($1,false);
    }
	| LOCAL_IDENTIFIER
    {
        $$ = vv12::Interpreter::getInp()->createVariableExp($1,true);
    }
    ;
constart_expression
    : DOUBLE_LITERAL
    {
        $$ = $1;
    }
	| INT_LITERAL
    {
        $$ = $1;
    }
    ;
%%