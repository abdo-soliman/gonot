#include <iostream>
#include <string>

#include "grammar/gonot.h"
#include "utils/utils.h"
#include "grammar/y.tab.h"

int compile(statement* s_ptr)
{
    if (!s_ptr)
        return 0;

    switch (s_ptr->type)
    {
        case CONST:
            std::cout << consttos(s_ptr->con) << '\n';
            break;
        case DECLARE:
            std::cout << "declaration variable with index: " << s_ptr->var.index << ", type: " << dttos(s_ptr->var.type) << '\n';
            break;
        case RETRIEVE:
            std::cout << "retrieving variable with index: " << s_ptr->var.index << '\n';
            break;
        case ASSIGN:
            std::cout << "assignment with index: " << s_ptr->ass.index << ", expr_type: " << sttos(s_ptr->ass.expr->type) << '\n';
            break;
        case OPERATION:
            std::cout << "operator: " << oprtos(s_ptr->opr.type) << ", op1_type: " << sttos(s_ptr->opr.op1->type) << ", op2_type: " << sttos(s_ptr->opr.op2->type) << '\n';
            break;
        default:
            break;
    }

    return 0;
}
