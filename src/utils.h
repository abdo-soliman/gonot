#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "gonot.h"

std::string sttos(statementType st_type);
std::string dttos(constDataType dt_type);
std::string oprtos(operatorType opr_type);
std::string consttos(constStatementType const_obj);

#endif
