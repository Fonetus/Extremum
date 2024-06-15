#include "graphics.cpp"
#include "dixotomia.cpp"
#include "gold_sechenie.cpp"
#include "parser.cpp"
#include "perebor.cpp"
#include <iostream>
#include <string>

#if defined(__has_include)
#  if __has_include(<windows.h>)
#    include <windows.h>
#  endif
#endif

/**
 * @brief Главная функция программы.
 *
 * Эта функция инициализирует необходимые параметры и вызывает различные методы
 * оптимизации (дихотомия, золотое сечение и перебор) для нахождения экстремума
 * заданной математической функции. Затем результаты визуализируются с
 * использованием различных графических функций.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Аргументы командной строки.
 * @return int Статус выхода программы.
 */
int main(int argc, char **argv) {

#if defined(__has_include)
#  if __has_include(<windows.h>)
#    define INCLUDED true
#  else
#    define INCLUDED false
#  endif
#endif

#if INCLUDED
    SetConsoleOutputCP(CP_UTF8);
#endif

    double left_border, right_border, eps, choice;
    typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;
    std::string function;

    std::cout << "EXTREMUM" << std::endl;

    std::cout << "Введите значение левой границы" << std::endl;
    std::cin >> left_border;
    std::cout << "Введите значение правой границы" << std::endl;
    std::cin >> right_border;
    std::cout << "Введите значение погрешности" << std::endl;
    std::cin >> eps;
    std::cout << "Что нужно найти? \n 1-максимум \n 2-минимум" << std::endl;
    std::cin >> choice;
    std::cout << "Введите выражение:" << std::endl;
    std::cin >> function;

    // Вызов метода дихотомии для нахождения экстремума
    FuncOutput result_dichotomy = dixot(left_border, right_border, eps, choice, function);
    // Вызов метода золотого сечения для нахождения экстремума
    FuncOutput result_section = golden_section(choice, right_border, left_border, eps, function);

    std::cout << "Дихотомия:" << (std::get<0>(std::get<0>(result_dichotomy)) + std::get<1>(std::get<0>(result_dichotomy))) / 2 << std::endl;
    std::cout << "Золотое Сечение:" << (std::get<0>(std::get<0>(result_section)) + std::get<1>(std::get<0>(result_section))) / 2 << std::endl;

    FuncOutput result_perebor;
    if (choice == 1) {
        // Вызов метода перебора для нахождения максимума
        result_perebor = perebor(function, left_border, right_border, 0.001, true);
    } else {
        // Вызов метода перебора для нахождения минимума
        result_perebor = perebor(function, left_border, right_border, 0.001, false);
    }

    std::cout << "Перебор: " << (std::get<0>(std::get<0>(result_perebor)) + std::get<1>(std::get<0>(result_perebor))) / 2 << std::endl;

    // Визуализация результатов для каждого метода
    graphics_func(left_border, right_border, std::get<0>(std::get<0>(result_dichotomy)), 1, function, std::get<1>(result_dichotomy));
    graphics_func(left_border, right_border, std::get<0>(std::get<0>(result_section)), 2, function, std::get<1>(result_section));
    graphics_func(left_border, right_border, std::get<0>(std::get<0>(result_perebor)), 3, function, std::get<1>(result_perebor));

    // Визуализация точности для каждого метода
    graphics_precision(std::get<1>(result_dichotomy), 1, left_border, right_border);
    graphics_precision(std::get<1>(result_section), 2, left_border, right_border);
    graphics_precision(std::get<1>(result_perebor), 3, left_border, right_border);

    // Визуализация итераций и точности для каждого метода
    graphics_iter_precision(left_border, right_border, 1, function); //dichotomy
    graphics_iter_precision(left_border, right_border, 2, function); //section
    graphics_iter_precision(left_border, right_border, 3, function); //perebor

    return 0;
}
