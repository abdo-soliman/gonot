%{
    #include <stdio.h>
    #include "grammar/gonot.h"
    int yylex(void);

    int int_sym[26];
    float float_sym[26];
%}

%union {
    int int_val;                /* integer value */
    float float_val;            /* float value */
    char st_index;              /* symbol table index */
    statement* stmt_ptr;        /* node pointer */
};

%token<int_val> INTEGER
%token<float_val> REAL
%token<st_index> VARIABLE
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
        INTEGER             { union dataType data; data.int_val = $1; $$ = parse_const(data, INT_TYPE); }
        | REAL              { union dataType data; data.float_val = $1; $$ = parse_const(data, FLOAT_TYPE); }
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
