#include <gtest/gtest.h>
#include "../src/temperature_model.hpp"

// Тест 1: Линейная модель
TEST(TemperatureModelTest, LinearModel) {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    
    // y = 20, u = 5 => y_next = 0.8*20 + 0.3*5 = 16 + 1.5 = 17.5
    EXPECT_DOUBLE_EQ(model.linearModel(20.0, 5.0), 17.5);
    
    // y = 0, u = 0 => y_next = 0
    EXPECT_DOUBLE_EQ(model.linearModel(0.0, 0.0), 0.0);
    
    // y = 10, u = 10 => y_next = 8 + 3 = 11
    EXPECT_DOUBLE_EQ(model.linearModel(10.0, 10.0), 11.0);
}

// Тест 2: Нелинейная модель
TEST(TemperatureModelTest, NonlinearModel) {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    
    // y = 20, y_prev = 20, u = 5, u_prev = 5
    // 0.8*20 - 0.3*400 + 0.4*5 + 0.1*sin(5)
    // = 16 - 120 + 2 + 0.1*(-0.9589) ≈ -102.0959
    EXPECT_NEAR(model.nonlinearModel(20.0, 20.0, 5.0, 5.0), -102.0959, 1e-4);
}

// Тест 3: Генерация управляющего сигнала
TEST(TemperatureModelTest, ControlSignal) {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    
    // При tau < 10 управление = 5
    EXPECT_DOUBLE_EQ(model.generateControlSignal(1), 5.0);
    EXPECT_DOUBLE_EQ(model.generateControlSignal(5), 5.0);
    EXPECT_DOUBLE_EQ(model.generateControlSignal(9), 5.0);
    
    // При tau >= 10 управление = 10
    EXPECT_DOUBLE_EQ(model.generateControlSignal(10), 10.0);
    EXPECT_DOUBLE_EQ(model.generateControlSignal(15), 10.0);
    EXPECT_DOUBLE_EQ(model.generateControlSignal(20), 10.0);
}

// Тест 4: Симуляция с заданными параметрами
TEST(TemperatureModelTest, Simulation) {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    
    // Запускаем симуляцию
    model.runSimulation(20, 20.0, 5.0);
    
    // Проверяем конечные значения
    EXPECT_NEAR(model.getLastLinear(), 29.99, 0.1);
    EXPECT_NEAR(model.getLastNonlinear(), 29.99, 0.1);
}

// Тест 5: Проверка разных параметров модели
TEST(TemperatureModelTest, DifferentParameters) {
    TemperatureModel model(0.5, 0.2, 0.3, 0.05);
    
    // y = 20, u = 5 => y_next = 0.5*20 + 0.2*5 = 10 + 1 = 11
    EXPECT_DOUBLE_EQ(model.linearModel(20.0, 5.0), 11.0);
}

// Тест 6: Проверка симуляции с 10 шагами
TEST(TemperatureModelTest, ShortSimulation) {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    
    model.runSimulation(10, 20.0, 5.0);
    
    // Первые 10 шагов управление = 5
    EXPECT_NEAR(model.getLastLinear(), 20.0, 0.1);
    EXPECT_NEAR(model.getLastNonlinear(), 20.0, 0.1);
}

// Тест 7: Проверка отрицательных значений
TEST(TemperatureModelTest, NegativeValues) {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    
    // y = -10, u = 5 => y_next = -8 + 1.5 = -6.5
    EXPECT_DOUBLE_EQ(model.linearModel(-10.0, 5.0), -6.5);
}

// Тест 8: Проверка граничных условий
TEST(TemperatureModelTest, BoundaryConditions) {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    
    // y = 1000, u = 100 => y_next = 800 + 30 = 830
    EXPECT_DOUBLE_EQ(model.linearModel(1000.0, 100.0), 830.0);
}