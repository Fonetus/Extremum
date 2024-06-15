#include <gtest/gtest.h>
#include "../perebor.h"

TEST(PereborTest, FindMinimum) {
std::string function = "x^2"; // функция x^2
double left_border = -10.0;
double right_border = 10.0;
double step = 0.1;
bool find_max = false; // ищем минимум

FuncOutput result = perebor(function, left_border, right_border, step, find_max);

// ожидаем, что минимум будет найден в точке x = 0
EXPECT_DOUBLE_EQ(std::get<0>(std::get<0>(result)), 0.0);
EXPECT_DOUBLE_EQ(std::get<1>(std::get<0>(result)), 0.0);
}

TEST(PereborTest, FindMaximum) {
std::string function = "-x^2"; // функция -x^2
double left_border = -10.0;
double right_border = 10.0;
double step = 0.1;
bool find_max = true; // ищем максимум

FuncOutput result = perebor(function, left_border, right_border, step, find_max);

// ожидаем, что максимум будет найден в точке x = 0
EXPECT_DOUBLE_EQ(std::get<0>(std::get<0>(result)), 0.0);
EXPECT_DOUBLE_EQ(std::get<1>(std::get<0>(result)), 0.0);
}

TEST(PereborTest, EdgeCase) {
std::string function = "x"; // функция x
double left_border = 0.0;
double right_border = 0.0;
double step = 0.1;
bool find_max = true; // ищем максимум

FuncOutput result = perebor(function, left_border, right_border, step, find_max);

// ожидаем, что максимум будет найден в точке x = 0
EXPECT_DOUBLE_EQ(std::get<0>(std::get<0>(result)), 0.0);
EXPECT_DOUBLE_EQ(std::get<1>(std::get<0>(result)), 0.0);
}