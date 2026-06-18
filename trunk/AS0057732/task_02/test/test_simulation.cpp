#include <gtest/gtest.h>
#include "../src/simulation.h"

// Тест для линейной модели
TEST(SimulationTest, LinearModelCalculatesCorrectly) {
    std::vector<double> u = {12.0, 12.0}; // 2 шага
    double a = 0.85;
    double b = 0.4;
    double y0 = 20.0;

    auto result = simulateLinear(u, a, b, y0);

    // Размер вектора должен быть n + 1
    ASSERT_EQ(result.size(), 3);
    
    // y[0] == y0
    EXPECT_NEAR(result[0], 20.0, 1e-5);
    
    // y[1] = a * y[0] + b * u[0] = 0.85 * 20 + 0.4 * 12 = 17 + 4.8 = 21.8
    EXPECT_NEAR(result[1], 21.8, 1e-5);
}

// Тест для нелинейной модели
TEST(SimulationTest, NonlinearModelCalculatesCorrectly) {
    std::vector<double> u = {12.0}; // 1 шаг
    double a = 0.85;
    double b = 0.01;
    double c = 0.4;
    double d = 0.2;
    double y0 = 20.0;
    double y_minus1 = 20.0;

    auto result = simulateNonlinear(u, a, b, c, d, y0, y_minus1);

    ASSERT_EQ(result.size(), 2);
    EXPECT_NEAR(result[0], 20.0, 1e-5);

    // На шаге t = 0: 
    // y[1] = a * y[0] - b * (y_minus1^2) + c * u[0] + d * sin(u_minus1)
    // y[1] = 0.85 * 20 - 0.01 * (20^2) + 0.4 * 12 + 0.2 * sin(0)
    // y[1] = 17 - 4 + 4.8 + 0 = 17.8
    EXPECT_NEAR(result[1], 17.8, 1e-5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}