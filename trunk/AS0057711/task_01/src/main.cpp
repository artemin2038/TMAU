#include <iostream>
#include <vector>
#include <cmath>
#include <clocale> // Библиотека для работы с локализацией

using namespace std;

// Функция для линейной модели: y(t+1) = a*y(t) + b*u(t)
vector<double> simulateLinear(int n, double a, double b, double y0, const vector<double>& u) {
    vector<double> y(n + 1, 0.0);
    y[0] = y0;
    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

// Функция для нелинейной модели: y(t+1) = a*y(t) - b*y(t-1)^2 + c*u(t) + d*sin(u(t-1))
vector<double> simulateNonlinear(int n, double a, double b, double c, double d, double y0, double y_minus1, const vector<double>& u, double u_minus1) {
    vector<double> y(n + 1, 0.0);
    y[0] = y0;
    double prev_y = y_minus1;
    double prev_u = u_minus1;

    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] - b * pow(prev_y, 2) + c * u[t] + d * sin(prev_u);
        prev_y = y[t];
        prev_u = u[t];
    }
    return y;
}

int main() {
    // Включаем поддержку русского языка для консоли
    setlocale(LC_ALL, "Russian");

    int n = 10; // Количество дискретных моментов времени (шагов)

    // Коэффициенты
    double a = 0.8;
    double b_lin = 0.5; // b для линейной модели
    double b_nonlin = 0.05, c = 0.4, d = 0.2; // коэффициенты для нелинейной модели

    // Начальные условия
    double y0 = 20.0; // Начальная температура y(0)
    double y_minus1 = 19.5; // Температура в предыдущий момент y(-1)
    double u_minus1 = 0.0;  // Управляющее воздействие u(-1)

    // Управляющее воздействие u(t) на каждом шаге (например, постоянный нагрев)
    vector<double> u(n, 5.0);

    // Выполнение симуляции
    vector<double> linear_result = simulateLinear(n, a, b_lin, y0, u);
    vector<double> nonlinear_result = simulateNonlinear(n, a, b_nonlin, c, d, y0, y_minus1, u, u_minus1);

    // Вывод результатов на русском языке
    cout << "=====================================================" << endl;
    cout << "Время (t)\tЛинейная y(t)\tНелинейная y(t)" << endl;
    cout << "=====================================================" << endl;
    for (int t = 0; t <= n; ++t) {
        cout << t << "\t\t" << linear_result[t] << "\t\t" << nonlinear_result[t] << endl;
    }
    cout << "=====================================================" << endl;

    return 0;
}