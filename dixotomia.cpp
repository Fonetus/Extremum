#include <cmath>
#include <map>
#include <tuple>
#include <string>

typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

/**
 * @brief Вычисляет значение математического выражения для заданного числа.
 *
 * @param str Математическое выражение.
 * @param chislo Значение, которое подставляется в переменную в выражении.
 * @return Результат вычисления.
 */
double calculate(std::string &str, double chislo);

/**
 * @brief Вычисляет значение математической функции для заданного аргумента.
 *
 * @param name Название функции.
 * @param str Математическое выражение, содержащее аргумент функции.
 * @param index Индекс начала аргумента в выражении.
 * @param chislo Значение, которое подставляется в переменную в выражении.
 * @return Значение функции при заданном аргументе.
 */
double function(std::string &name, std::string &str, unsigned &index, double chislo);

/**
 * Оценивает математическую функцию в заданном интервале с использованием метода бисекции.
 *
 * @param left_border Левый конец интервала.
 * @param right_border Правый конец интервала.
 * @param eps Желаемая точность.
 * @param l Определяет направление минимизации функции (l=1 для минимизации, l=0 для максимизации).
 * @param function Математическая функция для оценки.
 * @return Кортеж, содержащий интервал, в котором находится минимум/максимум, и карту итераций и соответствующих интервалов.
 */
FuncOutput dixot(double left_border, double right_border, double eps, int l, std::string function) {
    double center, check1, check2;
    typedef std::map<int, std::tuple<double, double>> ForGraph;
    ForGraph dict;
    int counter = 0;
    std::tuple<double, double> pre_interval;

    if (l == 1) {
        while (std::fabs(right_border - left_border) > eps) {
            center = (left_border + right_border) / 2;
            check1 = calculate(function, center + eps);
            check2 = calculate(function, center - eps);
            if (check1 < check2) {
                right_border = center;
            } else {
                left_border = center;
            }
            counter += 1;
            pre_interval = std::make_tuple(left_border, right_border);
            dict.insert(std::make_pair(counter, pre_interval));
        }
    } else {
        while (std::fabs(right_border - left_border) > eps) {
            center = (left_border + right_border) / 2;
            check1 = calculate(function, center + eps);
            check2 = calculate(function, center - eps);
            if (check1 > check2) {
                right_border = center;
            } else {
                left_border = center;
            }
            counter += 1;
            pre_interval = std::make_tuple(left_border, right_border);
            dict.insert(std::make_pair(counter, pre_interval));
        }
    }

    std::tuple<double, double> interval = std::make_tuple(left_border, right_border);
    return std::make_tuple(interval, dict);
}
