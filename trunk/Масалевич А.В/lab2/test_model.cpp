#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

// 1. Тест линейной модели с нулевыми параметрами
TEST(LinearModelTest, ZeroParameters) {
    EXPECT_DOUBLE_EQ(linear_model(5.0, 3.0, 0.0, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.0, 0.0), 0.0);
}

// 2. Тест линейной модели с единичными коэффициентами
TEST(LinearModelTest, UnitCoefficients) {
    EXPECT_DOUBLE_EQ(linear_model(2.0, 3.0, 1.0, 1.0), 5.0);
    EXPECT_DOUBLE_EQ(linear_model(-1.0, 2.0, 1.0, 1.0), 1.0);
}

// 3. Тест линейной модели с произвольными коэффициентами
TEST(LinearModelTest, ArbitraryCoefficients) {
    EXPECT_DOUBLE_EQ(linear_model(2.0, 3.0, 0.5, 0.3), 1.9); // 0.5*2 + 0.3*3 = 1.9
    EXPECT_DOUBLE_EQ(linear_model(4.0, -2.0, 0.8, 0.2), 2.8); // 0.8*4 + 0.2*(-2) = 2.8
}

// 4. Тест нелинейной модели: проверка члена с y_prev^2
TEST(NonlinearModelTest, SquareTerm) {
    double a = 1.0, b = 1.0, c = 0.0, d = 0.0;
    // y_{t+1} = y_t - y_{t-1}^2
    EXPECT_DOUBLE_EQ(nonlinear_model(2.0, 3.0, 0.0, 0.0, a, b, c, d), 2.0 - 9.0);
    EXPECT_DOUBLE_EQ(nonlinear_model(-1.0, 2.0, 0.0, 0.0, a, b, c, d), -1.0 - 4.0);
}

// 5. Тест нелинейной модели: проверка синусоидального члена
TEST(NonlinearModelTest, SinTerm) {
    double a = 0.0, b = 0.0, c = 0.0, d = 1.0;
    // y_{t+1} = sin(u_{t-1})
    EXPECT_DOUBLE_EQ(nonlinear_model(0.0, 0.0, 0.0, 0.0, a, b, c, d), sin(0.0));
    EXPECT_DOUBLE_EQ(nonlinear_model(0.0, 0.0, 0.0, M_PI/2, a, b, c, d), sin(M_PI/2));
}

// 6. Комбинированный тест нелинейной модели
TEST(NonlinearModelTest, CombinedTerms) {
    double a = 0.8, b = 0.3, c = 0.2, d = 0.1;
    // y = 0.8*5 - 0.3*3^2 + 0.2*2 + 0.1*sin(1)
    double expected = 0.8*5 - 0.3*9 + 0.2*2 + 0.1*sin(1.0);
    EXPECT_NEAR(nonlinear_model(5.0, 3.0, 2.0, 1.0, a, b, c, d), expected, 1e-9);
}

// 7. Тест: линейная модель с отрицательными коэффициентами
TEST(LinearModelTest, NegativeCoefficients) {
    EXPECT_DOUBLE_EQ(linear_model(3.0, 2.0, -1.0, -2.0), -7.0);
    EXPECT_DOUBLE_EQ(linear_model(-3.0, -2.0, -1.0, -2.0), 7.0);
}

// 8. Тест: нелинейная модель с отрицательными коэффициентами
TEST(NonlinearModelTest, NegativeCoefficients) {
    double a = -0.5, b = 0.2, c = -0.3, d = -0.1;
    double expected = -0.5*4 - 0.2*9 - 0.3*1 - 0.1*sin(2.0);
    EXPECT_NEAR(nonlinear_model(4.0, 3.0, 1.0, 2.0, a, b, c, d), expected, 1e-9);
}

// Основная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}