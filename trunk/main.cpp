// temperature_model.cpp
// Лабораторная работа №1 - Моделирование управляемого объекта
// Студент: группа 577, номер 17

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Константы модели
const double A = 0.8;      // коэффициент a
const double B = 0.3;      // коэффициент b
const double C = 0.2;      // коэффициент c (для нелинейной модели)
const double D = 0.1;      // коэффициент d (для нелинейной модели)
const double Y0 = 25.0;    // комнатная температура

// Входной сигнал (управление)
double inputSignal(int tau) {
    return 10.0 * sin(0.1 * tau) + 5.0;
}

// Линейная модель
double linearModel(double y_prev, double u) {
    return A * y_prev + B * u;
}

// Нелинейная модель
double nonlinearModel(double y_prev, double y_prev2, double u, double u_prev) {
    return A * y_prev - B * y_prev2 * y_prev2 + C * u + D * sin(u_prev);
}

// Функция для вывода результатов
void printResults(const vector<double>& time, const vector<double>& y_linear, 
                  const vector<double>& y_nonlinear, const vector<double>& u) {
    cout << "\n=== Результаты моделирования ===\n";
    cout << "----------------------------------------\n";
    cout << "  τ  |   u(τ)  |  Линейная  | Нелинейная\n";
    cout << "----------------------------------------\n";
    
    for (size_t i = 0; i < time.size(); ++i) {
        cout << setw(4) << i 
             << " | " << setw(7) << fixed << setprecision(2) << u[i]
             << " | " << setw(9) << y_linear[i]
             << " | " << setw(10) << y_nonlinear[i] << "\n";
    }
    cout << "----------------------------------------\n";
}

int main() {
    cout << "Лабораторная работа №1\n";
    cout << "Моделирование управляемого объекта\n";
    cout << "Студент: группа 577, номер 17\n";
    cout << "====================================\n";
    
    const int N = 20;
    const double Y_INIT = 20.0;
    
    vector<double> tau(N);
    vector<double> y_linear(N);
    vector<double> y_nonlinear(N);
    vector<double> u(N);
    
    y_linear[0] = Y_INIT;
    y_nonlinear[0] = Y_INIT;
    
    double y_prev_nonlinear = Y_INIT;
    double y_prev2_nonlinear = Y_INIT;
    double u_prev = 0.0;
    
    for (int i = 0; i < N; ++i) {
        tau[i] = i;
    }
    
    for (int i = 0; i < N; ++i) {
        u[i] = inputSignal(i);
    }
    
    for (int i = 1; i < N; ++i) {
        y_linear[i] = linearModel(y_linear[i-1], u[i-1]);
        
        if (i == 1) {
            y_nonlinear[i] = nonlinearModel(y_nonlinear[i-1], y_prev2_nonlinear, 
                                           u[i-1], u_prev);
        } else {
            y_nonlinear[i] = nonlinearModel(y_nonlinear[i-1], y_nonlinear[i-2], 
                                           u[i-1], u[i-2]);
        }
    }
    
    printResults(tau, y_linear, y_nonlinear, u);
    
    double mse = 0.0;
    for (int i = 0; i < N; ++i) {
        mse += pow(y_linear[i] - y_nonlinear[i], 2);
    }
    mse /= N;
    cout << "\nСреднеквадратичная разница между моделями: " << mse << "\n";
    
    return 0;
}
