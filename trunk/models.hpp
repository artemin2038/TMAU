// models.hpp
// Заголовочный файл с объявлениями функций для моделирования температуры
// Студент: группа 577, номер 17

#ifndef MODELS_HPP
#define MODELS_HPP

#include <vector>

// Константы модели
extern const double A;      // коэффициент a
extern const double B;      // коэффициент b
extern const double C;      // коэффициент c (для нелинейной модели)
extern const double D;      // коэффициент d (для нелинейной модели)
extern const double Y0;     // комнатная температура

// Входной сигнал (управление)
double inputSignal(int tau);

// Линейная модель
double linearModel(double y_prev, double u);

// Нелинейная модель
double nonlinearModel(double y_prev, double y_prev2, double u, double u_prev);

// Функция для моделирования линейной модели на N шагов
std::vector<double> simulateLinear(int N, double y_init, const std::vector<double>& u);

// Функция для моделирования нелинейной модели на N шагов
std::vector<double> simulateNonlinear(int N, double y_init, const std::vector<double>& u);

// Функция для расчета среднеквадратичной ошибки между моделями
double calculateMSE(const std::vector<double>& y1, const std::vector<double>& y2);

// Функция для вывода результатов
void printResults(const std::vector<double>& time, const std::vector<double>& y_linear, 
                  const std::vector<double>& y_nonlinear, const std::vector<double>& u);

#endif // MODELS_HPP
