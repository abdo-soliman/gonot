#ifndef COMPILER_H_
#define COMPILER_H_

#include "grammar/gonot.h"
#include <vector>
#include <string>
#include <variant>

class Compiler
{
public:
    static Compiler& get();
    Compiler(const Compiler&) = delete;

    static void next_line();
    static void compile(statement* s_ptr);
    static bool has_errors();
    static void log_errors(std::string filename="errors.log");
    static void write(std::string filename="a.asm");
private:
    Compiler();

    void _next_line();
    void _compile(statement* s_ptr);

    // issue print intrupt in case on non assignment statement with expression result
    void print_routine(int type, std::string value);

    // assignment sub functions
    void compile_assignment(statement* s_ptr);
    void assign_const(const constStatementType& con, std::variant<int, float, char, std::string>& value, std::string& command);
    bool assign_retrieve(const varStatementType& var, std::variant<int, float, char, std::string>& value, std::string& command);
    bool assign_operation(const operationStatementType& opr,
                           std::variant<int, float, char, std::string>& value,
                           std::string& command);

    void compile_operation(statement* s_ptr);

    // some helper functions
    bool get_variable(const varStatementType& var, std::variant<int, float, char, std::string>& value);
    bool get_operand(statement* op, std::variant<int, float, char, std::string>& value);

    void _write(std::string filename);

    std::vector<std::string> errors;
    std::vector<std::string> result;
    int line_number = 1;
};

#endif
