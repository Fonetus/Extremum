#include "gtest/gtest.h"
#include "graphics.h"

class GraphicsTest : public ::testing::Test {
protected:
    std::map<int, std::tuple<double, double>> diction = {{1, {1.0, 2.0}}, {2, {3.0, 4.0}}};
};

TEST_F(GraphicsTest, GraphicsFuncValidInput) {
    graphics_func(0.0, 10.0, 5.0, 1, "x^2", diction);
}

TEST_F(GraphicsTest, GraphicsFuncInvalidType) {
    EXPECT_THROW(graphics_func(0.0, 10.0, 5.0, 4, "x^2", diction), std::invalid_argument);
}

TEST_F(GraphicsTest, GraphicsFuncInvalidFunction) {
    EXPECT_THROW(graphics_func(0.0, 10.0, 5.0, 1, "invalid_function", diction), std::invalid_argument);
}

TEST_F(GraphicsTest, GraphicsFuncInvalidInterval) {
    EXPECT_THROW(graphics_func(-10.0, -5.0, 5.0, 1, "x^2", diction), std::invalid_argument);
}

TEST_F(GraphicsTest, GraphicsPrecisionValidInput) {
    graphics_precision(diction, 1, 0.0, 10.0);
}

TEST_F(GraphicsTest, GraphicsPrecisionInvalidType) {
    EXPECT_THROW(graphics_precision(diction, 4, 0.0, 10.0), std::invalid_argument);
}

TEST_F(GraphicsTest, GraphicsPrecisionInvalidInterval) {
    EXPECT_THROW(graphics_precision(diction, 1, -10.0, -5.0), std::invalid_argument);
}

TEST_F(GraphicsTest, DrawCycleThroughPrecisionValidInput) {
    Plot plot_for_iter_precision;
    draw_cycle_through_precision(0.0, 10.0, 1, plot_for_iter_precision, 1.0, "x^2");
}

TEST_F(GraphicsTest, DrawCycleThroughPrecisionInvalidType) {
    Plot plot_for_iter_precision;
    EXPECT_THROW(draw_cycle_through_precision(0.0, 10.0, 4, plot_for_iter_precision, 1.0, "x^2"), std::invalid_argument);
}

TEST_F(GraphicsTest, DrawCycleThroughPrecisionInvalidFunction) {
    Plot plot_for_iter_precision;
    EXPECT_THROW(draw_cycle_through_precision(0.0, 10.0, 1, plot_for_iter_precision, 1.0, "invalid_function"), std::invalid_argument);
}

TEST_F(GraphicsTest, GraphicsIterPrecisionValidInput) {
    graphics_iter_precision(0.0, 10.0, 1, "x^2");
}

TEST_F(GraphicsTest, GraphicsIterPrecisionInvalidType) {
    EXPECT_THROW(graphics_iter_precision(0.0, 10.0, 4, "x^2"), std::invalid_argument);
}

TEST_F(GraphicsTest, GraphicsIterPrecisionInvalidFunction) {
    EXPECT_THROW(graphics_iter_precision(0.0, 10.0, 1, "invalid_function"), std::invalid_argument);
}