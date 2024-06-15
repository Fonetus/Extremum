#ifndef PROJECT_DIXOTOMIA_H
#define PROJECT_DIXOTOMIA_H

#include <tuple>
#include <map>
#include <string>

typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

FuncOutput dixot(double left_border, double right_border, double eps, int l, std::string function);

double calculate(std::string &str, double chislo);
double function(std::string &, std::string &, unsigned &, double chislo);

#endif  // PROJECT_DIXOTOMIA_H