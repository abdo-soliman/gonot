%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "grammar/gonot.h"
    #include "symbol_table/symbol_table.h"
    #include "compiler/compiler.h"
    int yylex(void);
    extern "C" FILE *yyin;
%}

%union {
    int int_val;
    float float_val;
    char char_val;
    char* str_val;
    statement* stmt_ptr;
};

%token<int_val> INT_VAL
%token<float_val> FLOAT_VAL
%token<char_val> CHAR_VAL
%token<str_val> STRING_VAL
%token<str_val> VARIABLE
%token INT FLOAT CHAR STRING

%type<stmt_ptr> stmt declare_stmt expr const_expr

%left '+' '-'
%left '*' '/'
%%

program:
        program stmt    { Compiler::compile($2); free_statement($2); }
        | /* NULL */
        ;

stmt:
        ';'                             { $$ = NULL; }
        | expr ';'                      { $$ = $1; }
        | declare_stmt ';'              { $$ = $1; }
        | declare_stmt '=' expr ';'     { Compiler::compile($1); $$ = assign($1->var.identifier, $3); }
        | VARIABLE '=' expr ';'         { $$ = assign($1, $3); }
        ;

declare_stmt:
        INT VARIABLE        { $$ = declare_variable(INT_TYPE, $2); }
        | FLOAT VARIABLE    { $$ = declare_variable(FLOAT_TYPE, $2); }
        | CHAR VARIABLE     { $$ = declare_variable(CHAR_TYPE, $2); }
        | STRING VARIABLE   { $$ = declare_variable(STRING_TYPE, $2); }
        ;

expr:
        const_expr
        | VARIABLE                  { $$ = retrieve_variable($1); }

        | VARIABLE '+' VARIABLE     { $$ = parse_operation(ADD, retrieve_variable($1), retrieve_variable($3)); }
        | VARIABLE '-' VARIABLE     { $$ = parse_operation(MINUS, retrieve_variable($1), retrieve_variable($3)); }
        | VARIABLE '*' VARIABLE     { $$ = parse_operation(MULTIPLY, retrieve_variable($1), retrieve_variable($3)); }
        | VARIABLE '/' VARIABLE     { $$ = parse_operation(DIVIDE, retrieve_variable($1), retrieve_variable($3)); }

        | const_expr '+' VARIABLE   { $$ = parse_operation(ADD, $1, retrieve_variable($3)); }
        | const_expr '-' VARIABLE   { $$ = parse_operation(MINUS, $1, retrieve_variable($3)); }
        | const_expr '*' VARIABLE   { $$ = parse_operation(MULTIPLY, $1, retrieve_variable($3)); }
        | const_expr '/' VARIABLE   { $$ = parse_operation(DIVIDE, $1, retrieve_variable($3)); }

        | VARIABLE '+' const_expr   { $$ = parse_operation(ADD, retrieve_variable($1), $3); }
        | VARIABLE '-' const_expr   { $$ = parse_operation(MINUS, retrieve_variable($1), $3); }
        | VARIABLE '*' const_expr   { $$ = parse_operation(MULTIPLY, retrieve_variable($1), $3); }
        | VARIABLE '/' const_expr   { $$ = parse_operation(DIVIDE, retrieve_variable($1), $3); }

        | const_expr '+' const_expr { $$ = parse_operation(ADD, $1, $3); }
        | const_expr '-' const_expr { $$ = parse_operation(MINUS, $1, $3); }
        | const_expr '*' const_expr { $$ = parse_operation(MULTIPLY, $1, $3); }
        | const_expr '/' const_expr { $$ = parse_operation(DIVIDE, $1, $3); }
        ;

const_expr:
        INT_VAL         {
                            union dataType data;
                            data.int_val = $1;
                            $$ = parse_const(data, INT_TYPE);
                        }
        | FLOAT_VAL     {
                            union dataType data;
                            data.float_val = $1;
                            $$ = parse_const(data, FLOAT_TYPE);
                        }
        | CHAR_VAL      {
                            union dataType data;
                            data.char_val = $1;
                            $$ = parse_const(data, CHAR_TYPE);
                        }
        | STRING_VAL    {
                            union dataType data;
                            if ($1 == 0)
                                data.str_val = 0;
                            else
                            {
                                data.str_val = (char *)malloc(strlen(yylval.str_val) * sizeof(char));
                                strcpy(data.str_val, $1);
                            }
                            $$ = parse_const(data, STRING_TYPE);
                        }
        ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        yyerror("No input file passed");
        return -1;
    }

    yyin = fopen(argv[1], "r");
    do
    {
        yyparse();
    } while (!feof(yyin));  

    if (Compiler::has_errors())
    {
        Compiler::log_errors();
        return -1;
    }
    SymbolTable::write();
    Compiler::write();

    fclose(yyin);
    return 0;
}
