#include <iostream>
#include <fstream>

#include "compiler/compiler.h"
#include "utils/utils.h"
#include "symbol_table/symbol_table.h"

Compiler::Compiler() { }

Compiler& Compiler::get()
{
    static Compiler gonot;
    return gonot;
}

void Compiler::compile(statement* s_ptr) { get()._compile(s_ptr); }

bool Compiler::has_errors() { return !get().errors.empty(); }

void Compiler::write(std::string filename) { get()._write(filename); }

void Compiler::_compile(statement* s_ptr)
{
    if (!s_ptr)
        return;

    std::variant<int, float, char, std::string> value;
    switch (s_ptr->type)
    {
        case CONST:
            con2variant(s_ptr->con, value);
            print_routine(value.index(), variant2str(value));
            break;
        case DECLARE:
            if (SymbolTable::declare(s_ptr->var.type, s_ptr->var.identifier) == MULTI_DECLARATION)
                errors.push_back("Error: " + std::string(s_ptr->var.identifier) + "is already declared");
            break;
        case RETRIEVE:
            if (get_variable(s_ptr->var, value))
                print_routine(value.index(), variant2str(value));
            break;
        case ASSIGN:
            compile_assignment(s_ptr);
            break;
        case OPERATION:
            compile_operation(s_ptr);
            break;
        default:
            break;
    }
}

void Compiler::compile_assignment(statement* s_ptr)
{
    std::string idf = s_ptr->ass.identifier;
    auto right_expr = s_ptr->ass.expr;
    std::variant<int, float, char, std::string> value;
    std::string command = "";
    switch (right_expr->type)
    {
        case CONST:
            command = "MOV " + idf + ", ";
            assign_const(right_expr->con, value, command);
            break;
        case RETRIEVE:
            command = "MOV " + idf + ", ";
            if (!assign_retrieve(right_expr->var, value, command))
                return;
            break;
        case OPERATION:
            if(!assign_operation(right_expr->opr, value, command))
                return;
            command += idf;
            break;
        default:
            errors.push_back("Error: invalid right hand side");
            return;
            break;
    }

    switch (SymbolTable::assign(idf, value))
    {
        case SUCCESS:
            result.push_back(command);
            break;
        case MISSING_DECLARATION:
            errors.push_back("Error: undefined variable " + idf);
            break;
        case TYPE_MISS_MATCH:
            errors.push_back("Error: undefined variable " + idf);
            break;
        default:
            break;
    }
}

void Compiler::assign_const(const constStatementType& con,
                             std::variant<int, float, char, std::string>& value,
                             std::string& command)
{
    switch(con.type)
    {
        case INT_TYPE:
            value = con.data.int_val;
            command += std::to_string(con.data.int_val);
            break;
        case FLOAT_TYPE:
            value = con.data.float_val;
            command += std::to_string(con.data.float_val);
            break;
        case CHAR_TYPE:
            value = con.data.char_val;
            command += "'";
            command += con.data.char_val;
            command += "'";
            break;
        case STRING_TYPE:
            value = std::string(con.data.str_val);
            command += "\"" + std::string(con.data.str_val) + "\"";
            break;
        default:
            break;
    }
}

bool Compiler::assign_retrieve(const varStatementType& var,
                                std::variant<int, float, char, std::string>& value,
                                std::string& command)
{
    std::string idf = std::string(var.identifier);
    switch(SymbolTable::retrieve(idf, value))
    {
        case MISSING_DECLARATION:
            errors.push_back("Error: undefined variable " + idf);
            return false;
            break;
        case BAD_ACCESS:
            errors.push_back("Error: variable is used without initialization " + idf);
            return false;
            break;
        case SUCCESS:
            command += idf;
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool Compiler::assign_operation(const operationStatementType& opr,
                                 std::variant<int, float, char, std::string>& value,
                                 std::string& command)
{
    std::variant<int, float, char, std::string> op1_value;
    std::variant<int, float, char, std::string> op2_value;

    if (!(get_operand(opr.op1, op1_value) && get_operand(opr.op2, op2_value)))
        return false;

    if (op1_value.index() > 1 || op2_value.index() > 1)
    {
        errors.push_back("Error: can't perform mathematical operations on non numeric values");
        return false;
    }

    if (op1_value.index() || op2_value.index())
    {
        float result = 0.0f;
        eval(opr.type, op1_value, op2_value, result);
        value = result;
    }
    else
    {
        int result = 0;
        eval(opr.type, op1_value, op2_value, result);
        value = result;
    }

    if (opr.type == ADD)
        command = "ADD ";
    else if (opr.type == MINUS)
        command = "SUB ";
    else if (opr.type == MULTIPLY)
        command = "MUL ";
    else
        command = "DIV ";

    if (opr.op1->type == CONST)
        command += variant2str(op1_value) + ", ";
    else if (opr.op1->type == RETRIEVE)
        command += std::string(opr.op1->var.identifier) + ", ";

    if (opr.op2->type == CONST)
        command += variant2str(op2_value) + ", ";
    else if (opr.op2->type == RETRIEVE)
        command += std::string(opr.op2->var.identifier) + ", ";

    return true;
}

void Compiler::compile_operation(statement* s_ptr)
{
    std::variant<int, float, char, std::string> value;
    std::variant<int, float, char, std::string> op1_value;
    std::variant<int, float, char, std::string> op2_value;

    if (!(get_operand(s_ptr->opr.op1, op1_value) && get_operand(s_ptr->opr.op2, op2_value)))
        return;

    if (op1_value.index() > 1 || op2_value.index() > 1)
    {
        errors.push_back("Error: can't perform mathematical operations on non numeric values");
        return;
    }

    if (op1_value.index() || op2_value.index())
    {
        float result = 0.0f;
        eval(s_ptr->opr.type, op1_value, op2_value, result);
        value = result;
    }
    else
    {
        int result = 0;
        eval(s_ptr->opr.type, op1_value, op2_value, result);
        value = result;
    }
    print_routine(value.index(), variant2str(value));
}

void Compiler::print_routine(int type, std::string value)
{
    if (type == 2)
        value = "'" + value + "'";
    else if (type == 3)
        value = "\"" + value + "\"";
    
    result.push_back(";print routine start");
    result.push_back("MOV stdout, " + value);
    result.push_back("MOV interrupt, 1");
    result.push_back("syscall");
    result.push_back(";print routine end");
}

bool Compiler::get_variable(const varStatementType& var, std::variant<int, float, char, std::string>& value)
{
    std::string idf = std::string(var.identifier);
    switch(SymbolTable::retrieve(idf, value))
    {
        case MISSING_DECLARATION:
            errors.push_back("Error: undefined variable " + idf);
            return false;
            break;
        case BAD_ACCESS:
            errors.push_back("Error: variable is used without initialization " + idf);
            return false;
            break;
        case SUCCESS:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool Compiler::get_operand(statement* op, std::variant<int, float, char, std::string>& value)
{
    switch(op->type)
    {
        case CONST:
            con2variant(op->con, value);
            break;
        case RETRIEVE:
            if (!get_variable(op->var, value))
                return false;
            break;
        default:
            errors.push_back("Error: invalid operand");
            return false;
            break;
    }

    return true;
}

void Compiler::log_errors()
{
    for (const auto& error : get().errors)
        std::cout << error << '\n';
}

void Compiler::_write(std::string filename)
{
    std::ofstream asm_file;
    asm_file.open(filename.c_str());
    for (const auto& line : result)
        asm_file << line << '\n';
    
    asm_file.close();
}
