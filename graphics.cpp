#include "sciplot/sciplot.hpp"
#include <cmath>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <algorithm>

using namespace sciplot;

/**
 * @brief Вычисляет значение математического выражения для заданного входного значения.
 * 
 * @param str Математическое выражение в строковом формате.
 * @param chislo Входное значение для вычисления.
 * @return Вычисленный результат.
 */
double calculate(std::string &str, double chislo);

/**
 * @brief Общая математическая функция, обрабатывающая строковое выражение.
 * 
 * @param param1 Первый строковый параметр.
 * @param param2 Второй строковый параметр.
 * @param param3 Ссылка на беззнаковое целое число.
 * @param chislo Входное значение для функции.
 * @return Результат выполнения функции.
 */
double function(std::string &param1, std::string &param2, unsigned &param3, double chislo);

/**
 * @brief Обертка для вычисления значения функции, заданной в строковом формате.
 * 
 * @param function Математическая функция в строковом формате.
 * @param chislo Входное значение для функции.
 * @return Результат выполнения функции.
 */
double f(std::string function, double chislo) {
    double y;
    y = calculate(function, chislo);
    return y;
}

typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

/**
 * @brief Генерация и сохранение графиков для заданной функции и ее результатов.
 * 
 * @param left_border Левая граница.
 * @param right_border Правая граница.
 * @param result Результат вычисления.
 * @param type Тип графика (1 - дихотомия, 2 - золотое сечение, 3 - перебор).
 * @param function Математическая функция в строковом формате.
 * @param diction Словарь значений для итераций.
 * @return 0, если выполнение успешно.
 */
int graphics_func(double left_border, double right_border, double result, int type, std::string function, std::map<int, std::tuple<double, double>> const &diction) {
    
    Vec x = linspace(left_border, right_border, 200);
    Vec xBox = linspace(result, result, 1);
    Vec yBox = linspace(f(function, result), f(function, result), 1);
    Vec ZeroBox = linspace(0.0, 0.0, 1);
    Plot plot1, plot2;
    
    std::vector colors = {"yellow", "orange", "coral", "red", "brown", "navy", "black"};
    int num_color = 0;
    std::vector<double> y;
    for (int i = 0; i < 200; i++) {
        y.push_back(f(function, x[i]));
    }
    double fmax = *std::max_element(y.begin(), y.end());
    double fmin = *std::min_element(y.begin(), y.end());
    double absmax = std::max(fabs(fmax), fabs(fmin));

    plot1.size(600, 600);
    plot1.xlabel("x");
    plot1.ylabel("y");

    plot1.xrange(left_border, right_border);
    plot1.yrange(-absmax, absmax);
    
    plot1.legend()
         .atOutsideBottom()
         .displayHorizontal();

    plot1.drawCurve(x, y).label(function).lineColor("green");
    
    plot2.size(600, 600);
    plot2.xlabel("x");
    plot2.ylabel("y");

    plot2.xrange(left_border, right_border);
    plot2.yrange(-absmax, absmax);
    
    plot2.legend()
         .atOutsideBottom()
         .displayHorizontal();

    plot2.drawCurve(x, y).label(function).lineColor("green");
    
    Vec vec_for_x1, vec_for_x2, vec_for_y1, vec_for_y2;
    for (auto const &pair: diction) {
        vec_for_x1 = linspace(std::get<0>(pair.second), std::get<0>(pair.second), 200);
        vec_for_y1 = linspace(-absmax, absmax, 200);
        plot2.drawCurve(vec_for_x1, vec_for_y1).label("iteration :" + std::to_string(pair.first)).lineColor(colors[num_color % colors.size()]);
        vec_for_x2 = linspace(std::get<1>(pair.second), std::get<1>(pair.second), 200);
        vec_for_y2 = linspace(-absmax, absmax, 200);
        plot2.drawCurve(vec_for_x2, vec_for_y2).label("iteration :" + std::to_string(pair.first)).lineColor(colors[num_color % colors.size()]);
        num_color += 1;
    }

    plot1.drawCurveWithPoints(xBox, ZeroBox).label("extremum : " + std::to_string(result));
    plot1.drawCurveWithPoints(xBox, yBox).label("pointer to the extremum");

    plot2.drawCurveWithPoints(xBox, ZeroBox).label("extremum : " + std::to_string(result));
    plot2.drawCurveWithPoints(xBox, yBox).label("pointer to the extremum");

    Figure plots = {{ plot1, plot2 }};
    plots.size(1200, 600);
    plots.title("Plots");
    plots.palette("dark2");
    
    if (type == 1) {
        plots.save("plot_dichotomy.pdf");
    } else if (type == 2) {
        plots.save("plot_section.pdf");
    } else if (type == 3) {
        plots.save("plot_perebor.pdf");
    }
    return 0;
}

/**
 * @brief Генерация и сохранение графиков точности для заданной функции.
 * 
 * @param diction Словарь значений для итераций.
 * @param type Тип графика (1 - дихотомия, 2 - золотое сечение, 3 - перебор).
 * @param left_border Левая граница.
 * @param right_border Правая граница.
 * @return 0, если выполнение успешно.
 */
int graphics_precision(std::map<int, std::tuple<double, double>> const &diction, int type, double left_border, double right_border) {
    
    Plot plot1;
    plot1.xlabel("iteration");
    plot1.ylabel("center");
    Vec vec_for_x, vec_for_y;
    plot1.xrange(0.0, diction.size());
    plot1.yrange(left_border, right_border); 
    plot1.legend()
         .atOutsideBottom()
         .displayHorizontal()
         .displayExpandWidthBy(2);

    for (auto const &pair: diction) {
        vec_for_x = linspace(pair.first, pair.first, 200);
        vec_for_y = linspace(std::get<0>(pair.second), std::get<1>(pair.second), 200);
        plot1.drawCurve(vec_for_x, vec_for_y).label("iteration :" + std::to_string(pair.first));
    }

    if (type == 1) {
        plot1.save("precision_dichotomy.pdf");
    } else if (type == 2) {
        plot1.save("precision_section.pdf");
    } else if (type == 3) {
        plot1.save("precision_perebor.pdf");
    }
    return 0;
}

/**
 * @brief Выполняет метод дихотомии для нахождения экстремума функции.
 * 
 * @param left_border Левая граница.
 * @param right_border Правая граница.
 * @param eps Точность.
 * @param l Параметр метода.
 * @param function Математическая функция в строковом формате.
 * @return Результаты выполнения метода и словарь значений для итераций.
 */
FuncOutput dixot(double left_border, double right_border, double eps, int l, std::string function);

/**
 * @brief Выполняет метод золотого сечения для нахождения экстремума функции.
 * 
 * @param word Параметр метода.
 * @param right_border Правая граница.
 * @param left_border Левая граница.
 * @param e Точность.
 * @param function Математическая функция в строковом формате.
 * @return Результаты выполнения метода и словарь значений для итераций.
 */
FuncOutput golden_section(int word, double right_border, double left_border, double e, std::string function);

/**
 * @brief Выполняет метод перебора для нахождения экстремума функции.
 * 
 * @param function Математическая функция в строковом формате.
 * @param left_border Левая граница.
 * @param right_border Правая граница.
 * @param step Шаг перебора.
 * @param find_max Найти максимум (true) или минимум (false).
 * @return Результаты выполнения метода и словарь значений для итераций.
 */
FuncOutput perebor(std::string &function, double left_border, double right_border, double step, bool find_max);

/**
 * @brief Визуализация зависимости числа итераций от точности для различных методов.
 * 
 * @param left_border Левая граница.
 * @param right_border Правая граница.
 * @param choice Выбор метода (1 - дихотомия, 2 - золотое сечение, 3 - перебор).
 * @param plot_for_iter_precision График для итераций и точности.
 * @param it Текущая итерация.
 * @param function Математическая функция в строковом формате.
 * @return Текущее количество итераций.
 */
int draw_cycle_through_precision(double left_border, double right_border, int choice, Plot plot_for_iter_precision, double it, std::string function) {
    
    int current_it_size;
    
    if (choice == 1) {
        FuncOutput cycle_of_func = dixot(left_border, right_border, 1 / pow(10, it), choice, function);
        current_it_size = std::get<1>(cycle_of_func).size();
    } else if (choice == 2) {
        FuncOutput cycle_of_func = golden_section(choice, right_border, left_border, 1 / pow(10, it), function);
        current_it_size = std::get<1>(cycle_of_func).size();
    } else if (choice == 3) {
        FuncOutput cycle_of_func = perebor(function, left_border, right_border, 0.001, 1 / pow(10, it));
        current_it_size = std::get<1>(cycle_of_func).size();
    }
    return current_it_size;
}

/**
 * @brief Генерация и сохранение графиков зависимости числа итераций от точности для заданной функции.
 * 
 * @param left_border Левая граница.
 * @param right_border Правая граница.
 * @param choice Выбор метода (1 - дихотомия, 2 - золотое сечение, 3 - перебор).
 * @param function Математическая функция в строковом формате.
 * @return 0, если выполнение успешно.
 */
int graphics_iter_precision(double left_border, double right_border, int choice, std::string function) {
    
    Plot plot_for_iter_precision;
    int curr_iter_size;
    std::vector<double> x;
    std::vector<int> y;

    for (double i = 0.0; i < 10; i += 0.1) {
        curr_iter_size = draw_cycle_through_precision(left_border, right_border, choice, plot_for_iter_precision, i, function);
        y.push_back(curr_iter_size);
        x.push_back(1 / pow(10, i + 1));
    }
    
    plot_for_iter_precision.size(400, 400);
    plot_for_iter_precision.xrange(0.0, 0.1);
    plot_for_iter_precision.yrange(0.0, *std::max_element(y.begin(), y.end()));
    plot_for_iter_precision.ylabel("iterations");
    plot_for_iter_precision.xlabel("precision");
    plot_for_iter_precision.drawCurve(x, y).label("iterations-precision dependency");
    
    if (choice == 1) {
        plot_for_iter_precision.save("iteration-precision-dichotomy.pdf");
    } else if (choice == 2) {
        plot_for_iter_precision.save("iteration-precision-section.pdf");
    } else if (choice == 3) {
        plot_for_iter_precision.save("iteration-precision-perebor.pdf");
    }
    return 0;
}
