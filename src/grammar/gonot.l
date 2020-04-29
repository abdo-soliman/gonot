%{
    #include <stdlib.h>
    #include <string.h>
    #include "grammar/gonot.h"
    #include "compiler/compiler.h"
    #include "grammar/y.tab.h"
%}

%%

'[a-z0-9!"#$%&()*+,.\/:;<=>?@\[\] ^_`{|}~-]?'      {
                                                        if (yyleng == 2)
                                                            yylval.char_val = 0;
                                                        else
                                                            yylval.char_val = yytext[1];

                                                        return CHAR_VAL;
                                                    }

\"[a-z0-9!#$%&'()*+,.\/:;<=>?@\[\] ^_`{|}~-]*\"    {
                                                        if (yyleng == 2)
                                                            yylval.str_val = 0;
                                                        else
                                                        {
                                                            yylval.str_val = (char *)malloc((yyleng-2) * sizeof(char));
                                                            strncpy(yylval.str_val, yytext+1, yyleng-2);
                                                        }

                                                        return STRING_VAL;
                                                    }

[0-9]+                                              {
                                                        yylval.int_val = atoi(yytext);
                                                        return INT_VAL;
                                                    }

([0-9]*)?\.[0-9]+                                   {
                                                        yylval.float_val = atof(yytext);
                                                        return FLOAT_VAL;
                                                    }

"int"               return INT;
"float"             return FLOAT;
"char"              return CHAR;
"string"            return STRING;

([a-zA-Z_])([a-zA-Z0-9_]*)                          {
                                                        yylval.str_val = (char *)malloc((yyleng) * sizeof(char));
                                                        strcpy(yylval.str_val, yytext);
                                                        if(strcmp(yylval.str_val, "interrupt") == 0)
                                                        {
                                                            yyerror("Error: illigal use of reserved word interrupt");
                                                            exit(-1);
                                                        }

                                                        if(strcmp(yylval.str_val, "stdout") == 0)
                                                        {
                                                            yyerror("Error: illigal use of reserved word stdout");
                                                            exit(-1);
                                                        }
                                                        return VARIABLE;
                                                    }

[-+=/*;]                                            { return *yytext; }
[\n]+                                               {
                                                        for (int i = 0; i < yyleng; i++)
                                                            Compiler::next_line();
                                                    }
[ \t]+                                              ;
.                                                   yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
