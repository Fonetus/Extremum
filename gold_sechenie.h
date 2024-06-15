#ifndef PROJECT_GOLD_SECHENIE_H
#define PROJECT_GOLD_SECHENIE_H

#include <tuple>
#include <map>
#include <string>

typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

FuncOutput golden_section(int word, double right_border, double left_border, double e, std::string function);

double calculate(std::string &str, double chislo);

#endif  // PROJECT_GOLD_SECHENIE_H