#include "symbol_table/symbol_table.h"
#include "utils/utils.h"
#include <fstream>

SymbolTable::SymbolTable() { }

SymbolTable& SymbolTable::get()
{
    static SymbolTable table;
    return table;
}

status SymbolTable::declare(constDataType type, std::string identifier) { return get()._declare(type, identifier); }
status SymbolTable::assign(std::string identifier, std::variant<int, float, char, std::string> value) { return get()._assign(identifier, value); }
status SymbolTable::retrieve(std::string identifier, std::variant<int, float, char, std::string>& value) { return get()._retrieve(identifier, value); }
bool SymbolTable::is_declared(std::string identifier) { return get()._is_declared(identifier); }
bool SymbolTable::is_assigned(std::string identifier) { return get()._is_assigned(identifier); }
void SymbolTable::write(std::string filename) { get()._write(filename); }

status SymbolTable::_declare(constDataType type, std::string identifier)
{
    if (table.find(identifier) != table.end())
        return MULTI_DECLARATION;

    info i;
    i.type = type;
    i.initialized = false;
    table.insert(std::pair<std::string, info>(identifier, i));

    return SUCCESS;
}

status SymbolTable::_assign(std::string identifier, std::variant<int, float, char, std::string> value)
{
    auto ptr = table.find(identifier);
    if (ptr == table.end())
        return MISSING_DECLARATION;

    if (!(value.index() == 0 && ptr->second.type == FLOAT_TYPE) && value.index() != ptr->second.type)
        return TYPE_MISS_MATCH;

    ptr->second.initialized = true;
    ptr->second.value = value;

    return SUCCESS;
}

status SymbolTable::_retrieve(std::string identifier, std::variant<int, float, char, std::string>& value)
{
    auto ptr = table.find(identifier);
    if (ptr == table.end())
        return MISSING_DECLARATION;

    if (!ptr->second.initialized)
        return BAD_ACCESS;

    value = ptr->second.value;
    return SUCCESS;
}

bool SymbolTable::_is_declared(std::string identifier)
{
    if (table.find(identifier) != table.end())
        return true;

    return false;
}

bool SymbolTable::_is_assigned(std::string identifier)
{
    auto ptr = table.find(identifier);
    if (ptr != table.end())
        return false;

    return ptr->second.initialized;
}

void SymbolTable::_write(std::string filename)
{
    std::ofstream table_file;
    table_file.open(filename.c_str());
    table_file << "identifier,type,initialized,value\n";
    for (auto it = table.begin(); it != table.end(); it++)
    {
        table_file << it->first << ",";
        table_file << dttos(it->second.type) << ",";
        if (it->second.initialized)
            table_file << "true,";
        else
            table_file << "false,";

        switch (it->second.value.index())
        {
            case INT_TYPE:
                table_file << std::get<int>(it->second.value) << '\n';
                break;
            case FLOAT_TYPE:
                table_file << std::get<float>(it->second.value) << '\n';
                break;
            case CHAR_TYPE:
                table_file << std::get<char>(it->second.value) << '\n';
                break;
            case STRING_TYPE:
                table_file << std::get<std::string>(it->second.value) << '\n';
                break;
            default:
                table_file << '\n';
                break;
        }
    }

    table_file.close();
}
