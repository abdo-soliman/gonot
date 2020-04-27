#include "utils/utils.h"
#include <iostream>

std::string sttos(statementType st_type)
{
    switch (st_type)
    {
        case CONST:
            return "CONST";
            break;
        case RETRIEVE:
            return "RETRIEVE";
            break;
        case OPERATION:
            return "OPERATION";
            break;
        case ASSIGN:
            return "ASSIGN";
            break;
        case DECLARE:
            return "DECLARE";
            break;
        default:
            break;
    }

    return "unknown";
}

std::string dttos(constDataType dt_type)
{
    switch (dt_type)
    {
        case INT_TYPE:
            return "INT";
            break;
        case FLOAT_TYPE:
            return "FLOAT";
            break;
        case CHAR_TYPE:
            return "CHAR";
            break;
        case STRING_TYPE:
            return "STRING";
            break;
        default:
            break;
    }

    return "unknown";
}

std::string oprtos(operatorType opr_type)
{
    switch (opr_type)
    {
        case ADD:
            return "ADD";
            break;
        case MINUS:
            return "MINUS";
            break;
        case MULTIPLY:
            return "MULTIPLY";
            break;
        case DIVIDE:
            return "DIVIDE";
            break;
        default:
            break;
    }

    return "unknown";
}

std::string consttos(constStatementType const_obj)
{
    std::string info = "constant with type: " + dttos(const_obj.type) + ", value: ";
    switch (const_obj.type)
    {
        case INT_TYPE:
            info += std::to_string(const_obj.data.int_val);
            break;
        case FLOAT_TYPE:
            info += std::to_string(const_obj.data.float_val);
            break;
        case CHAR_TYPE:
            if (const_obj.data.char_val == 0)
                info += "NULL";
            else
                info += const_obj.data.char_val;
            break;
        case STRING_TYPE:
            if (const_obj.data.str_val == 0)
                info += "NULL";
            else
                info += std::string(const_obj.data.str_val);
            break;
        default:
            break;
    }

    return info;
}
