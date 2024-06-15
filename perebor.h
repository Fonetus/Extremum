#ifndef PROJECT_PEREBOR_H
#define PROJECT_PEREBOR_H

#include <tuple>
#include <map>
#include <string>

typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

FuncOutput perebor(std::string& function, double left_border, double right_border, double step, bool find_max);

double calculate(std::string& str, double chislo);

#endif  // PROJECT_PEREBOR_H