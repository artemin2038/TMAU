// main.cpp
// Лабораторная работа №2 - Моделирование управляемого объекта с модульными тестами
// Студент: группа 577, номер 17

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "models.hpp"

// Определение констант
const double A = 0.8;      // коэффициент a
const double B = 0.3;      // коэффициент b
const double C = 0.2;      // коэффициент c (для нелинейной модели)
const double D = 0.1;      // коэффициент d (для нелинейной модели)
const double Y0 = 25.0;    // комнатная температура

// Реализация функций

double inputSignal(int tau) {
    return 10.0 * sin(0.1 * tau) + 5.0;
}

double linearModel(double y_prev, double u) {
    return A * y_prev + B * u;
}

double nonlinearModel(double y_prev, double y_prev2, double u, double u_prev) {
    return A * y_prev - B * y_prev2 * y_prev2 + C * u + D * sin(u_prev);
}

std::vector<double> simulateLinear(int N, double y_init, const std::vector<double>& u) {
    std::vector<double> y(N);
    y[0] = y_init;
    for (int i = 1; i < N; ++i) {
        y[i] = linearModel(y[i-1], u[i-1]);
    }
    return y;
}

std::vector<double> simulateNonlinear(int N, double y_init, const std::vector<double>& u) {
    std::vector<double> y(N);
    y[0] = y_init;
    
    double y_prev = y_init;
    double y_prev2 = y_init;
    double u_prev = 0.0;
    
    for (int i = 1; i < N; ++i) {
        if (i == 1) {
            y[i] = nonlinearModel(y[i-1], y_prev2, u[i-1], u_prev);
        } else {
            y[i] = nonlinearModel(y[i-1], y[i-2], u[i-1], u[i-2]);
        }
    }
    return y;
}

double calculateMSE(const std::vector<double>& y1, const std::vector<double>& y2) {
    if (y1.size() != y2.size() || y1.empty()) {
        return -1.0;
    }
    double mse = 0.0;
    for (size_t i = 0; i < y1.size(); ++i) {
        mse += pow(y1[i] - y2[i], 2);
    }
    return mse / y1.size();
}

void printResults(const std::vector<double>& time, const std::vector<double>& y_linear, 
                  const std::vector<double>& y_nonlinear, const std::vector<double>& u) {
    std::cout << "\n=== Результаты моделирования ===\n";
    std::cout << "----------------------------------------\n";
    std::cout << "  τ  |   u(τ)  |  Линейная  | Нелинейная\n";
    std::cout << "----------------------------------------\n";
    
    for (size_t i = 0; i < time.size(); ++i) {
        std::cout << std::setw(4) << i 
                  << " | " << std::setw(7) << std::fixed << std::setprecision(2) << u[i]
                  << " | " << std::setw(9) << y_linear[i]
                  << " | " << std::setw(10) << y_nonlinear[i] << "\n";
    }
    std::cout << "----------------------------------------\n";
}

int main() {
    std::cout << "Лабораторная работа №2\n";
    std::cout << "Моделирование управляемого объекта\n";
    std::cout << "Студент: группа 577, номер 17\n";
    std::cout << "====================================\n";
    
    const int N = 20;
    const double Y_INIT = 20.0;
    
    // Генерация входного сигнала
    std::vector<double> u(N);
    for (int i = 0; i < N; ++i) {
        u[i] = inputSignal(i);
    }
    
    // Моделирование
    std::vector<double> y_linear = simulateLinear(N, Y_INIT, u);
    std::vector<double> y_nonlinear = simulateNonlinear(N, Y_INIT, u);
    
    // Вывод результатов
    std::vector<double> tau(N);
    for (int i = 0; i < N; ++i) {
        tau[i] = i;
    }
    printResults(tau, y_linear, y_nonlinear, u);
    
    // Расчет MSE
    double mse = calculateMSE(y_linear, y_nonlinear);
    std::cout << "\nСреднеквадратичная разница между моделями: " << mse << "\n";
    
    return 0;
}

