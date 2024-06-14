#include <cmath>
#include <map>
#include <tuple>
#include <string>

typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

double calculate(std::string& str, double chislo);

FuncOutput perebor(std::string& function, double left_border, double right_border, double step, bool find_max) {
    double best_val = find_max? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity();
    double best_arg = left_border;
    std::map<int, std::tuple<double, double>> evaluations;

    for (double x = left_border; x <= right_border; x += step) {
        double val = calculate(function, x);
        evaluations[int(x)] = std::make_tuple(x, val);

        if ((find_max && val > best_val) || (!find_max && val < best_val)) {
            best_val = val;
            best_arg = x;
        }
    }

    return std::make_tuple(std::make_tuple(best_arg, best_val), evaluations);
}
