#include <gtest/gtest.h>
#include "../src/simulation.h"

TEST(LinearSuite, BasicCalculation) {
    std::vector<double> u = {10.0, 10.0};
    double alpha = 0.9;
    double beta  = 0.35;
    double y0    = 22.0;

    auto y = linear_model(u, alpha, beta, y0);

    ASSERT_EQ(y.size(), 3);
    EXPECT_DOUBLE_EQ(y[0], 22.0);

    double expected = alpha * y0 + beta * u[0];
    EXPECT_NEAR(y[1], expected, 1e-9);

    expected = alpha * y[1] + beta * u[1];
    EXPECT_NEAR(y[2], expected, 1e-9);
}

TEST(LinearSuite, SingleStep) {
    std::vector<double> u = {5.0};
    double alpha = 0.8;
    double beta  = 0.5;
    double y0    = 10.0;

    auto y = linear_model(u, alpha, beta, y0);
    ASSERT_EQ(y.size(), 2);
    EXPECT_DOUBLE_EQ(y[0], 10.0);
    EXPECT_NEAR(y[1], 0.8 * 10.0 + 0.5 * 5.0, 1e-9);
}

TEST(NonlinearSuite, BasicCalculation) {
    std::vector<double> u = {10.0};
    double alpha = 0.9;
    double beta  = 0.015;
    double gamma = 0.35;
    double delta = 0.25;
    double y0    = 22.0;
    double ym1   = 22.0;

    auto y = nonlinear_model(u, alpha, beta, gamma, delta, y0, ym1);

    ASSERT_EQ(y.size(), 2);
    EXPECT_DOUBLE_EQ(y[0], 22.0);

    double expected = alpha * y0 - beta * (ym1 * ym1) + gamma * u[0] + delta * std::sin(0.0);
    EXPECT_NEAR(y[1], expected, 1e-9);
}

TEST(NonlinearSuite, ZeroInput) {
    std::vector<double> u = {0.0, 0.0, 0.0};
    double alpha = 0.9;
    double beta  = 0.015;
    double gamma = 0.35;
    double delta = 0.25;
    double y0    = 25.0;
    double ym1   = 25.0;

    auto y = nonlinear_model(u, alpha, beta, gamma, delta, y0, ym1);
    ASSERT_EQ(y.size(), 4);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
