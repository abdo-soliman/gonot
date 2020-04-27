%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "grammar/gonot.h"
    int yylex(void);

    int int_sym[26];
    float float_sym[26];
%}

%union {
    int int_val;
    float float_val;
    char char_val;
    char* str_val;
    statement* stmt_ptr;        /* node pointer */
};

%token<int_val> INT_VAL
%token<float_val> FLOAT_VAL
%token<char_val> CHAR_VAL
%token<str_val> STRING_VAL
%token<str_val> VARIABLE
%token INT FLOAT CHAR STRING

%type<stmt_ptr> stmt expr

%left '+' '-'
%left '*' '/'
%%

program:
        program stmt '\n'         { compile($2); free_statement($2); }
        | /* NULL */
        ;

stmt:
        expr                    { $$ = $1; }
        | INT VARIABLE          { $$ = declare_variable(INT_TYPE, $2); }
        | FLOAT VARIABLE        { $$ = declare_variable(FLOAT_TYPE, $2); }
        | CHAR VARIABLE         { $$ = declare_variable(CHAR_TYPE, $2); }
        | STRING VARIABLE       { $$ = declare_variable(STRING_TYPE, $2); }
        | VARIABLE '=' expr     { $$ = assign($1, $3); }
        ;

expr:
        INT_VAL             {
                                union dataType data;
                                data.int_val = $1;
                                $$ = parse_const(data, INT_TYPE);
                            }
        | FLOAT_VAL         {
                                union dataType data;
                                data.float_val = $1;
                                $$ = parse_const(data, FLOAT_TYPE);
                            }
        | CHAR_VAL          {
                                union dataType data;
                                data.char_val = $1;
                                $$ = parse_const(data, CHAR_TYPE);
                            }
        | STRING_VAL        {
                                union dataType data;
                                if ($1 == 0)
                                    data.str_val = 0;
                                else
                                {
                                    size_t length = sizeof($1) / sizeof(char); 
                                    data.str_val = (char *)malloc(length * sizeof(char));
                                    strcpy(data.str_val, $1);
                                }
                                $$ = parse_const(data, STRING_TYPE);
                            }
        | VARIABLE          { $$ = retrieve_variable($1); }
        | expr '+' expr     { $$ = parse_operation(ADD, $1, $3); }
        | expr '-' expr     { $$ = parse_operation(MINUS, $1, $3); }
        | expr '*' expr     { $$ = parse_operation(MULTIPLY, $1, $3); }
        | expr '/' expr     { $$ = parse_operation(DIVIDE, $1, $3); }
        | '(' expr ')'      { $$ = $2; }
        ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}

int main()
{
    yyparse();
    return 0;
}
