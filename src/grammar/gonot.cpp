#include "grammar/gonot.h"
#include "grammar/y.tab.h"

#include <stdlib.h>
#include <string.h>

statement* parse_const(union dataType data, constDataType type)
{
    statement *s_ptr = new statement;
    s_ptr->type = CONST;
    s_ptr->con.type = type;
    s_ptr->con.data = data;
    return s_ptr;
}

statement* declare_variable(constDataType type, const char* identifier)
{
    statement *s_ptr = new statement;
    
    s_ptr->type = DECLARE;
    s_ptr->var.type = type;
    s_ptr->var.identifier = (char *)malloc(strlen(identifier) * sizeof(char));
    strcpy(s_ptr->var.identifier, identifier);

    return s_ptr;
}

statement* retrieve_variable(const char* identifier)
{
    statement *s_ptr = new statement;
    
    s_ptr->type = RETRIEVE;
    s_ptr->var.identifier = (char *)malloc(strlen(identifier) * sizeof(char));
    strcpy(s_ptr->var.identifier, identifier);

    return s_ptr;
}

statement* assign(const char* identifier, statement* expr)
{
    statement *s_ptr = new statement;

    s_ptr->type = ASSIGN;
    s_ptr->ass.identifier = (char *)malloc(strlen(identifier) * sizeof(char));
    strcpy(s_ptr->ass.identifier, identifier);
    s_ptr->ass.expr = expr;

    return s_ptr;
}

statement* parse_operation(operatorType type, statement* op1, statement* op2)
{
    statement *s_ptr = new statement;

    s_ptr->type = OPERATION;
    s_ptr->opr.type = type;
    s_ptr->opr.op1 = op1;
    s_ptr->opr.op2 = op2;

    return s_ptr;
}

void free_statement(statement* s_ptr)
{
    if (!s_ptr)
        return;
    delete s_ptr;
}
