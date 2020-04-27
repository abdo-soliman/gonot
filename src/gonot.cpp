#include "gonot.h"
#include "y.tab.h"

statement* parse_const(union dataType data, constDataType type)
{
    statement *s_ptr = new statement;

    s_ptr->type = CONST;
    s_ptr->con.type = type;
    s_ptr->con.data = data;

    return s_ptr;
}

statement* declare_variable(constDataType type, int index)
{
    statement *s_ptr = new statement;
    
    s_ptr->type = DECLARE;
    s_ptr->var.type = type;
    s_ptr->var.index = index;

    return s_ptr;
}

statement* retrieve_variable(int index)
{
    statement *s_ptr = new statement;
    
    s_ptr->type = RETRIEVE;
    s_ptr->var.index = index;

    return s_ptr;
}

statement* assign(int index, statement* expr)
{
    statement *s_ptr = new statement;

    s_ptr->type = ASSIGN;
    s_ptr->ass.index = index;
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
