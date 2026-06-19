#include <gtest/gtest.h>
#include "../src/model.h"

// Тест 1: Проверка линейной модели с базовыми значениями
TEST(ModelTestSuite, LinearModelStandardCalculations) {
    // Если y_curr=20, u_curr=1, a=0.8, b=0.5 -> 20*0.8 + 1*0.5 = 16.5
    double result = calculateLinearStep(20.0, 1.0, 0.8, 0.5);
    EXPECT_NEAR(result, 16.5, 0.001);
}

// Тест 2: Проверка линейной модели с нулевыми значениями
TEST(ModelTestSuite, LinearModelZeroInputs) {
    double result = calculateLinearStep(0.0, 0.0, 0.8, 0.5);
    EXPECT_NEAR(result, 0.0, 0.001);
}

// Тест 3: Проверка одного шага нелинейной модели с контролируемыми числами
TEST(ModelTestSuite, NonlinearModelStandardCalculations) {
    // Подставим простые значения: y_curr=10, y_prev=2, u_curr=1, u_prev=0
    // Константы: a=0.5, b=0.1, c=0.2, d=0.5
    // Формула: 0.5*10 - 0.1*(2^2) + 0.2*1 + 0.5*sin(0) = 5 - 0.4 + 0.2 + 0 = 4.8
    double result = calculateNonlinearStep(10.0, 2.0, 1.0, 0.0, 0.5, 0.1, 0.2, 0.5);
    EXPECT_NEAR(result, 4.8, 0.001);
}
