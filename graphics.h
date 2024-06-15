#ifndef PROJECT_GRAPHICS_H
#define PROJECT_GRAPHICS_H

#include <vector>
#include <map>
#include <string>
#include <tuple>

class Plot;

int graphics_func(double left_border, double right_border, double result, int type, std::string function, std::map<int, std::tuple<double,double>> const &diction);

int graphics_precision(std::map<int, std::tuple<double,double>> const &diction, int type, double left_border, double right_border);

int draw_cycle_through_precision(double left_border, double right_border, int choice, Plot plot_for_iter_precision, double it, std::string function);

int graphics_iter_precision(double left_border, double right_border, int choice, std::string function);

#endif // PROJECT_GRAPHICS_H