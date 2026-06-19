#include <gtest/gtest.h>
#include "../src/model.h"
#include <vector>
#include <clocale>   // Для поддержки русского языка
#include <iostream>  // Для вывода текста
#include <locale>
#include <windows.h> // Подключаем библиотеку для настройки консоли Windows
// Тест для проверки правильности расчетов линейной модели
TEST(ModelTest, LinearModelCalculatesCorrectly) {
    int n = 2;
    double a = 0.5, b = 1.0, y0 = 10.0;
    std::vector<double> u = { 5.0, 5.0 }; // Управляющее воздействие

    auto result = simulateLinear(n, a, b, y0, u);

    // Ожидаемые результаты расчетов:
    // Шаг 0: y[0] = 10.0
    // Шаг 1: y[1] = 0.5 * 10.0 + 1.0 * 5.0 = 10.0
    // Шаг 2: y[2] = 0.5 * 10.0 + 1.0 * 5.0 = 10.0

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 10.0);
    EXPECT_DOUBLE_EQ(result[1], 10.0);
    EXPECT_DOUBLE_EQ(result[2], 10.0);
}

// Тест для проверки правильности расчетов нелинейной модели
TEST(ModelTest, NonlinearModelCalculatesCorrectly) {
    int n = 1;
    double a = 1.0, b = 0.5, c = 1.0, d = 0.0;
    double y0 = 4.0, y_minus1 = 2.0;
    std::vector<double> u = { 2.0 };
    double u_minus1 = 0.0;

    auto result = simulateNonlinear(n, a, b, c, d, y0, y_minus1, u, u_minus1);

    // Ожидаемые результаты расчетов:
    // Шаг 0: y[0] = 4.0
    // Шаг 1: y[1] = 1.0 * 4.0 - 0.5 * (2.0^2) + 1.0 * 2.0 + 0.0 * sin(0.0) = 4.0 - 2.0 + 2.0 + 0 = 4.0

    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], 4.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0);
}

// Главная функция запуска тестов
int main(int argc, char** argv) {
    // Устанавливаем кодировку UTF-8 для корректного вывода русского текста в консоли Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ::testing::InitGoogleTest(&argc, argv);

    std::cout << "=======================================" << std::endl;
    std::cout << "Запуск модульных тестов для Задания 2..." << std::endl;
    std::cout << "=======================================" << std::endl;

    // Запускаем все тесты GTest
    int result = RUN_ALL_TESTS();

    std::cout << "=======================================" << std::endl;
    if (result == 0) {
        std::cout << "Итог: Все тесты успешно пройдены! Можно сдавать." << std::endl;
    }
    else {
        std::cout << "Итог: Обнаружены ошибки. Проверьте логи выше." << std::endl;
    }
    std::cout << "=======================================" << std::endl;

    return result;
}