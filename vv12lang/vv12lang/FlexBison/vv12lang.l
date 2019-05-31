%{
#include <stdio.h>
#include "vv12lang.tab.h"
#include "../vv12lang/proc.h"
#define YY_SKIP_YYWRAP 1
int gLine = 1;
int yywrap(void){ return 1; }
%}
%s COMMENT
%s LINE_COMMENT
%s STR_LITERAL_ST_D
%s STR_LITERAL_ST_S
%%
<INITIAL>{
    "*="    return MULASS;
    "/="    return DIVASS;
    "+="    return ADDASS;
    "-="    return SUBASS;
	"=="    return EQ;
	"!="    return NE;
    "<="    return LE;
    ">="    return GE;
    "<"     return LT;
    ">"     return GT;
    "+"     return ADD;
    "-"     return SUB;
    "*"     return MUL;
    "/"     return DIV;
    "="     return ASS;
	"("     return LP;
    ")"     return RP;
	"{"     return LC;
    "}"     return RC;
	";"     return SEMICOLON;
	"while"   return WHILE;
	"if"    return IF;
	"for"   return FOR;
    "ecn"    return PRINTN;
    "ec"     return PRINT;
    "#*"   { BEGIN(COMMENT);}
    [#]+ { BEGIN(LINE_COMMENT);}
	"\""    {
                vv12::Interpreter::getInp()->startStringLiteral();
                BEGIN(STR_LITERAL_ST_D);
            }
    "\'"    {
                vv12::Interpreter::getInp()->startStringLiteral();
                BEGIN(STR_LITERAL_ST_S);
            }
    [0-9][0-9]* {
         yylval.expression = vv12::Interpreter::getInp()->createIntLiteralExp(yytext);
         return INT_LITERAL;
        
    }
    [0-9]*\.[0-9]* {
        yylval.expression = vv12::Interpreter::getInp()->createDoubleLiteralExp(yytext);
        return DOUBLE_LITERAL;
    }
    "^".[A-Za-z_0-9]* {
        yylval.fixedString = vv12::Interpreter::getInp()->createFixedString(yytext);
        return IDENTIFIER;
    }
    "\n"    { gLine++;return CRLF;}
    [ \t]   ;
    .       { return 0; }
}
<COMMENT>{
    "\n"    { gLine++;}
    "*#"    { BEGIN(INITIAL); }
    .       ;
}
<LINE_COMMENT>{
    "\n"    { gLine++; BEGIN(INITIAL); }
    .       ;
}
<STR_LITERAL_ST_D>{
    "\n"    { gLine++; vv12::Interpreter::getInp()->addStringLiteral('\n'); }
    "\""    { BEGIN(INITIAL); return STR_LITERAL; }
    .       { vv12::Interpreter::getInp()->addStringLiteral(yytext[0]); }
}
<STR_LITERAL_ST_S>{
    "\n"    { gLine++; vv12::Interpreter::getInp()->addStringLiteral('\n'); }
    "\'"    { BEGIN(INITIAL); return STR_LITERAL; }
    .       { vv12::Interpreter::getInp()->addStringLiteral(yytext[0]); }
}
%%