#ifndef GONOT_H_
#define GONOT_H_

typedef enum { ADD, MINUS, MULTIPLY, DIVIDE } operatorType;
typedef enum { INT_TYPE, FLOAT_TYPE, CHAR_TYPE, STRING_TYPE } constDataType;
typedef enum { CONST, DECLARE, ASSIGN, RETRIEVE, OPERATION } statementType;

union dataType {
    int int_val;
    float float_val;
    char char_val;
    char* str_val;
};

/* constants */
typedef struct {
    constDataType type;
    union dataType data;
} constStatementType;

/* identifiers */
typedef struct {
    char* identifier;
    constDataType type;
} varStatementType;

/* operators */
typedef struct {
    operatorType type;
    struct statementTag *op1;
    struct statementTag *op2;
} operationStatementType;

typedef struct {
    char* identifier;
    struct statementTag *expr;
} assignStatementType;

typedef struct statementTag {
    statementType type;

    union {
        constStatementType con;
        varStatementType var;
        assignStatementType ass;
        operationStatementType opr;
    };
} statement;

// log functions
void yyerror(const char *);

// parsing functions
statement* parse_const(union dataType data, constDataType type);
statement* declare_variable(constDataType type, const char* identifier);
statement* retrieve_variable(const char* identifier);
statement* assign(const char* identifier, statement* expr);
statement* parse_operation(operatorType type, statement* op1, statement* op2);
// execution functions
void free_statement(statement *s_ptr);

#endif
