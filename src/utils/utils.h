#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <variant>
#include "grammar/gonot.h"

std::string sttos(statementType st_type);
std::string dttos(constDataType dt_type);
std::string oprtos(operatorType opr_type);
std::string consttos(constStatementType const_obj);

void eval(operatorType type,
           std::variant<int, float, char, std::string> value1,
           std::variant<int, float, char, std::string> value2,
           int& result);

void eval(operatorType type,
           std::variant<int, float, char, std::string> value1,
           std::variant<int, float, char, std::string> value2,
           float& result);

std::string variant2str(const std::variant<int, float, char, std::string>& value);
void con2variant(const constStatementType& con, std::variant<int, float, char, std::string>& value);

#endif
