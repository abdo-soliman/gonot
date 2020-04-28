#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <map>
#include <string>
#include <variant>
#include "grammar/gonot.h"

typedef struct
{
    bool initialized;
    constDataType type;
    std::variant<int, float, char, std::string> value;
} info;
typedef enum { SUCCESS, TYPE_MISS_MATCH, MULTI_DECLARATION, MISSING_DECLARATION, BAD_ACCESS } status;

class SymbolTable
{
public:
    SymbolTable(const SymbolTable&) = delete;
    static SymbolTable& get();

    static status declare(constDataType type, std::string identifier);
    static status assign(std::string identifier, std::variant<int, float, char, std::string> value);
    static status retrieve(std::string identifier, std::variant<int, float, char, std::string>& value);

    static bool is_declared(std::string identifier);
    static bool is_assigned(std::string identifier);

    static void write(std::string filename="a.table.csv");
private:
    SymbolTable();
    status _declare(constDataType type, std::string identifier);
    status _assign(std::string identifier, std::variant<int, float, char, std::string> value);
    status _retrieve(std::string identifier, std::variant<int, float, char, std::string>& value);

    bool _is_declared(std::string identifier);
    bool _is_assigned(std::string identifier);

    void _write(std::string filename);
    std::string get_value(std::variant<int, float, char, std::string>);
    std::map<std::string, info> table;
};

#endif
