// test_temperature.cpp
// Модульные тесты для лабораторной работы №2
// Студент: группа 577, номер 17

#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "../src/models.hpp"

// Тест 1: Проверка входного сигнала
TEST(InputSignalTest, ReturnsCorrectValue) {
    EXPECT_NEAR(inputSignal(0), 5.0, 1e-6);
    EXPECT_NEAR(inputSignal(1), 5.0 + 10.0 * sin(0.1), 1e-6);
    EXPECT_NEAR(inputSignal(2), 5.0 + 10.0 * sin(0.2), 1e-6);
}

// Тест 2: Проверка линейной модели
TEST(LinearModelTest, ReturnsCorrectValue) {
    EXPECT_NEAR(linearModel(0.0, 0.0), 0.0, 1e-6);
    EXPECT_NEAR(linearModel(10.0, 5.0), 9.5, 1e-6);
    EXPECT_NEAR(linearModel(20.0, 10.0), 0.8*20 + 0.3*10, 1e-6);
}

// Тест 3: Проверка нелинейной модели
TEST(NonlinearModelTest, ReturnsCorrectValue) {
    double expected = 0.8*10 - 0.3*25 + 0.2*3 + 0.1*sin(2.0);
    EXPECT_NEAR(nonlinearModel(10.0, 5.0, 3.0, 2.0), expected, 1e-6);
    EXPECT_NEAR(nonlinearModel(0.0, 0.0, 0.0, 0.0), 0.0, 1e-6);
}

// Тест 4: Проверка симуляции линейной модели
TEST(SimulateLinearTest, ReturnsCorrectVector) {
    const int N = 5;
    const double Y_INIT = 20.0;
    std::vector<double> u(N, 5.0);
    
    std::vector<double> y = simulateLinear(N, Y_INIT, u);
    
    EXPECT_EQ(y.size(), N);
    EXPECT_NEAR(y[0], Y_INIT, 1e-6);
    EXPECT_NEAR(y[1], 17.5, 1e-6);
    EXPECT_NEAR(y[2], 15.5, 1e-6);
}

// Тест 5: Проверка симуляции нелинейной модели
TEST(SimulateNonlinearTest, ReturnsCorrectVector) {
    const int N = 5;
    const double Y_INIT = 20.0;
    std::vector<double> u(N, 5.0);
    
    std::vector<double> y = simulateNonlinear(N, Y_INIT, u);
    
    EXPECT_EQ(y.size(), N);
    EXPECT_NEAR(y[0], Y_INIT, 1e-6);
    
    double expected_y1 = 0.8*20 - 0.3*400 + 0.2*5 + 0.1*0;
    EXPECT_NEAR(y[1], expected_y1, 1e-6);
}

// Тест 6: Проверка расчета MSE
TEST(CalculateMSETest, ReturnsCorrectValue) {
    std::vector<double> y1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> y2 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> y3 = {1.0, 3.0, 5.0, 7.0};
    
    EXPECT_NEAR(calculateMSE(y1, y2), 0.0, 1e-6);
    EXPECT_NEAR(calculateMSE(y1, y3), 3.5, 1e-6);
    
    std::vector<double> empty;
    EXPECT_NEAR(calculateMSE(empty, empty), -1.0, 1e-6);
}

// Тест 7: Проверка граничных условий
TEST(BoundaryTest, HandlesExtremeValues) {
    double large = 1e6;
    EXPECT_FALSE(std::isnan(linearModel(large, large)));
    EXPECT_FALSE(std::isinf(linearModel(large, large)));
    EXPECT_NEAR(linearModel(-10.0, -5.0), 0.8*(-10) + 0.3*(-5), 1e-6);
}

// Тест 8: Проверка согласованности моделей
TEST(ModelConsistencyTest, ModelsAgreeForSmallValues) {
    const int N = 10;
    const double Y_INIT = 0.1;
    std::vector<double> u(N, 0.01);
    
    std::vector<double> y_linear = simulateLinear(N, Y_INIT, u);
    std::vector<double> y_nonlinear = simulateNonlinear(N, Y_INIT, u);
    
    double mse = calculateMSE(y_linear, y_nonlinear);
    EXPECT_LT(mse, 0.1);
}

// Тест 9: Проверка стационарного состояния
TEST(SteadyStateTest, LinearModelReachesSteadyState) {
    const int N = 100;
    const double Y_INIT = 20.0;
    std::vector<double> u(N, 10.0);
    
    std::vector<double> y = simulateLinear(N, Y_INIT, u);
    
    double steady_state = 0.3 * 10.0 / (1.0 - 0.8);
    EXPECT_NEAR(y[N-1], steady_state, 0.01);
}

// Тест 10: Проверка периодичности
TEST(InputSignalTest, IsPeriodic) {
    double val1 = inputSignal(0);
    double val2 = inputSignal(63);
    EXPECT_NEAR(val1, val2, 0.01);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
