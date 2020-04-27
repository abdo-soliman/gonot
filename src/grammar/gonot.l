%{
    #include <stdlib.h>
    #include "grammar/gonot.h"
    #include "grammar/y.tab.h"
%}

%%

[a-z]               {
                        yylval.st_index = *yytext - 'a';
                        return VARIABLE;
                    }

[0-9]+              {
                        yylval.int_val = atoi(yytext);
                        return INTEGER;
                    }

([0-9]*)?\.[0-9]+   {
                        yylval.float_val = atof(yytext);
                        return REAL;
                    }

[-+()=/*\n]         { return *yytext; }

"int"               return INT;
"float"             return FLOAT;
"char"              return CHAR;
"string"            return STRING;

[ \t]+              ;

.                   yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
