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

void eval(operatorType type,
           std::variant<int, float, char, std::string> value1,
           std::variant<int, float, char, std::string> value2,
           int& result)
{
    switch(type)
    {
        case ADD:
            result = std::get<int>(value1) + std::get<int>(value2);
            break;
        case MINUS:
            result = std::get<int>(value1) - std::get<int>(value2);
            break;
        case MULTIPLY:
            result = std::get<int>(value1) * std::get<int>(value2);
            break;
        case DIVIDE:
            result = std::get<int>(value1) / std::get<int>(value2);
            break;
        default:
            break;
    }
}

void eval(operatorType type,
           std::variant<int, float, char, std::string> value1,
           std::variant<int, float, char, std::string> value2,
           float& result)
{
    switch(type)
    {
        case ADD:
            if (value1.index() == 1 && value2.index() == 1)
                result = std::get<float>(value1) + std::get<float>(value2);
            else if (value1.index() == 0 && value2.index() == 1)
                result = std::get<int>(value1) + std::get<float>(value2);
            else if (value1.index() == 1 && value2.index() == 0)
                result = std::get<float>(value1) + std::get<int>(value2);
            break;
        case MINUS:
            if (value1.index() == 1 && value2.index() == 1)
                result = std::get<float>(value1) - std::get<float>(value2);
            else if (value1.index() == 0 && value2.index() == 1)
                result = std::get<int>(value1) - std::get<float>(value2);
            else if (value1.index() == 1 && value2.index() == 0)
                result = std::get<float>(value1) - std::get<int>(value2);
            break;
        case MULTIPLY:
            if (value1.index() == 1 && value2.index() == 1)
                result = std::get<float>(value1) * std::get<float>(value2);
            else if (value1.index() == 0 && value2.index() == 1)
                result = std::get<int>(value1) * std::get<float>(value2);
            else if (value1.index() == 1 && value2.index() == 0)
                result = std::get<float>(value1) * std::get<int>(value2);
            break;
        case DIVIDE:
            if (value1.index() == 1 && value2.index() == 1)
                result = std::get<float>(value1) / std::get<float>(value2);
            else if (value1.index() == 0 && value2.index() == 1)
                result = std::get<int>(value1) / std::get<float>(value2);
            else if (value1.index() == 1 && value2.index() == 0)
                result = std::get<float>(value1) / std::get<int>(value2);
            break;
        default:
            break;
    }
}

std::string variant2str(const std::variant<int, float, char, std::string>& value)
{
    if (value.index() == 0)
        return std::to_string(std::get<int>(value));
    else if (value.index() == 1)
        return std::to_string(std::get<float>(value));
    else if (value.index() == 2)
    {
        std::string result = "";
        result += std::get<char>(value);
        return result;
    }
    else
        return std::get<std::string>(value);
}

void con2variant(const constStatementType& con, std::variant<int, float, char, std::string>& value)
{
    switch(con.type)
    {
        case INT_TYPE:
            value = con.data.int_val;
            break;
        case FLOAT_TYPE:
            value = con.data.float_val;
            break;
        case CHAR_TYPE:
            value = con.data.char_val;
            break;
        case STRING_TYPE:
            value = std::string(con.data.str_val);
            break;
        default:
            break;
    }
}
