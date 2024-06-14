#include "sciplot/sciplot.hpp"
#include <cmath>
#include <vector>
#include <string>

using namespace sciplot;

double calculate(std::string& str, double chislo);
double function(std::string&, std::string&, unsigned&, double chislo);

double f(std::string function, double chislo) {
    double y;
    y = calculate(function, chislo);
    return y;
}

typedef std::tuple<std::tuple<double, double>, std::map<int, std::tuple<double, double>>> FuncOutput;

int graphics_func(double left_border, double right_border, double result, int type, std::string function, const std::map<int, std::tuple<double, double>>& diction) {
    Vec x = linspace(left_border, right_border, 200);
    Vec xBox = linspace(result, result, 1);
    Vec yBox = linspace(f(function, result), f(function, result), 1);
    Vec ZeroBox = linspace(0.0, 0.0, 1);
    Plot plot1, plot2;

    std::vector<std::string> colors = {"yellow", "orange", "coral", "red", "brown", "navy", "black"};
    int num_color = 0;
    std::vector<double> y;
    for (int i = 0; i < 200; ++i) {
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
    for (const auto& pair : diction) {
        vec_for_x1 = linspace(std::get<0>(pair.second), std::get<0>(pair.second), 200);
        vec_for_y1 = linspace(-absmax, absmax, 200);
        plot2.drawCurve(vec_for_x1, vec_for_y1).label("iteration :" + std::to_string(pair.first)).lineColor(colors[num_color % colors.size()]);
        vec_for_x2 = linspace(std::get<1>(pair.second), std::get<1>(pair.second), 200);
        vec_for_y2 = linspace(-absmax, absmax, 200);
        plot2.drawCurve(vec_for_x2, vec_for_y2).label("iteration :" + std::to_string(pair.first)).lineColor(colors[num_color % colors.size()]);
        ++num_color;
    }

    plot1.drawCurveWithPoints(xBox, ZeroBox).label("extremum : " + std::to_string(result));
    plot1.drawCurveWithPoints(xBox, yBox).label("pointer to the extremum");

    plot2.drawCurveWithPoints(xBox, ZeroBox).label("extremum : " + std::to_string(result));
    plot2.drawCurveWithPoints(xBox, yBox).label("pointer to the extremum");

    Figure plots = {{plot1, plot2}};
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

int graphics_precision(const std::map<int, std::tuple<double, double>>& diction, int type, double left_border, double right_border) {
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

    for (const auto& pair : diction) {
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

FuncOutput dixot(double left_border, double right_border, double eps, int l, std::string function);

FuncOutput golden_section(int word, double right_border, double left_border, double e, std::string function);

FuncOutput perebor(std::string& function, double left_border, double right_border, double step, bool find_max);
