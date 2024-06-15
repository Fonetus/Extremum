#include <iostream>
#include <cmath>
#include <map>
#include <tuple>
#include <string>

/**
 * @brief Вычисляет значение функции, представленной строкой, в заданной точке.
 *
 * @param str Строка, представляющая функцию.
 * @param chislo Число, в котором необходимо вычислить функцию.
 * @return Значение функции в точке chislo.
 */
double calculate(std::string& str, double chislo);

/**
 * @typedef FuncOutput
 * @brief Определяет тип возвращаемого значения для функции golden_section.
 *
 * FuncOutput представляет собой std::tuple, состоящий из:
 * 1. std::tuple<double, double>: Интервал, в котором находится минимум или максимум функции.
 * 2. std::map<int, std::tuple<double, double>>: Словарь, содержащий историю интервалов на каждом шаге алгоритма.
 */
typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

/**
 * @brief Реализует алгоритм золотого сечения для поиска минимума или максимума функции на заданном интервале.
 *
 * @param word Флаг, определяющий, искать ли минимум (1) или максимум (любое другое значение).
 * @param right_border Правая граница интервала поиска.
 * @param left_border Левая граница интервала поиска.
 * @param e Точность, при достижении которой алгоритм прекращает работу.
 * @param function Строка, представляющая функцию, для которой ищется минимум или максимум.
 * @return FuncOutput Кортеж, содержащий конечный интервал и историю интервалов на каждом шаге.
 */
FuncOutput golden_section(int word, double right_border, double left_border, double e, std::string function) {
    typedef std::map<int, std::tuple<double, double>> ForGraph;
    ForGraph dict;
    double t = (sqrt(5) + 1) / 2;
    double x_1;
    double x_2;
    int counter = 0;
    std::tuple<double, double> pre_interval;

    if (word == 1) {
        // Поиск минимума
        while (e < fabs(right_border - left_border)) {
            counter += 1;
            x_1 = right_border - (right_border - left_border) / t;
            x_2 = left_border + (right_border - left_border) / t;
            if (calculate(function, x_1) <= calculate(function, x_2)) {
                left_border = x_1;
            } else {
                right_border = x_2;
            }
            pre_interval = std::make_tuple(left_border, right_border);
            dict.insert(std::make_pair(counter, pre_interval));
        }
    } else {
        // Поиск максимума
        while (e < fabs(right_border - left_border)) {
            counter += 1;
            x_1 = right_border - (right_border - left_border) / t;
            x_2 = left_border + (right_border - left_border) / t;
            if (calculate(function, x_1) >= calculate(function, x_2)) {
                left_border = x_1;
            } else {
                right_border = x_2;
            }
            pre_interval = std::make_tuple(left_border, right_border);
            dict.insert(std::make_pair(counter, pre_interval));
        }
    }

    std::tuple<double, double> interval = std::make_tuple(left_border, right_border);
    return std::make_tuple(interval, dict);
}
