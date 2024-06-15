#include <gtest/gtest.h>
#include "../gold_sechenie.h"

double calculate(std::string &str, double chislo);
double expression(std::string &, unsigned &, double chislo);
double multiply_divide(std::string &, unsigned &, double chislo);
double sign(std::string &, unsigned &, double chislo);
double brackets(std::string &, unsigned &, double chislo);
double number(std::string &, unsigned &, double chislo);
double identificator(std::string &, unsigned &, double chislo);
double function(std::string &, std::string &, unsigned &, double chislo);

TEST(GoldenSectionTest, Minimization) {
// Тест на минимизацию функции x^2 на интервале [-10, 10]
std::string function = "x^2";
double left_border = -10.0;
double right_border = 10.0;
double e = 0.01;
int word = 1; // минимизация

FuncOutput result = golden_section(word, right_border, left_border, e, function);

std::tuple<double, double> interval = std::get<0>(result);
double min_x = (std::get<0>(interval) + std::get<1>(interval)) / 2;
double min_y = calculate(function, min_x);

EXPECT_NEAR(min_y, 0.0, e); // ожидаем, что минимум функции близок к 0
}

TEST(GoldenSectionTest, Maximization) {
// Тест на максимизацию функции x^2 на интервале [-10, 10]
std::string function = "x^2";
double left_border = -10.0;
double right_border = 10.0;
double e = 0.01;
int word = 2; // максимизация

FuncOutput result = golden_section(word, right_border, left_border, e, function);

std::tuple<double, double> interval = std::get<0>(result);
double max_x = (std::get<0>(interval) + std::get<1>(interval)) / 2;
double max_y = calculate(function, max_x);

EXPECT_NEAR(max_y, 100.0, e); // ожидаем, что максимум функции близок к 100
}

TEST(GoldenSectionTest, EdgeCase) {
// Тест на граничный случай, когда функция линейна
std::string function = "x";
double left_border = 0.0;
double right_border = 1.0;
double e = 0.01;
int word = 1; // минимизация

FuncOutput result = golden_section(word, right_border, left_border, e, function);

std::tuple<double, double> interval = std::get<0>(result);
double min_x = (std::get<0>(interval) + std::get<1>(interval)) / 2;
double min_y = calculate(function, min_x);

EXPECT_NEAR(min_y, 0.0, e); // ожидаем, что минимум функции близок к 0
}