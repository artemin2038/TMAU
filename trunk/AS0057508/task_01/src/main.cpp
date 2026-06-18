#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // 1. Инициализация параметров и констант
    int n = 10; // Количество шагов (дискретных моментов времени)
    
    // Константы для уравнений (задай свои, если они выданы преподавателем)
    double a = 0.8;
    double b = 0.5;
    double c = 0.3;
    double d = 0.1;

    // Входной сигнал u (предположим, что он постоянный и равен 1.0 для простоты)
    // В реальной задаче это может быть массив разных значений.
    vector<double> u(n + 1, 1.0); 

    // Векторы для хранения значений температуры y
    vector<double> y_linear(n + 1, 0.0);
    vector<double> y_nonlinear(n + 1, 0.0);

    // Начальные условия
    y_linear[0] = 20.0; // Комнатная температура для линейной модели
    
    // Для нелинейной модели нам нужны y[0] и y[1], так как формула использует y_{tau-1}
    y_nonlinear[0] = 20.0; 
    y_nonlinear[1] = 20.0; 

    // 2. Моделирование линейной системы
    // Формула: y_{tau+1} = a * y_{tau} + b * u_{tau}
    cout << "--- Линейная модель ---" << endl;
    for (int tau = 0; tau < n; ++tau) {
        y_linear[tau + 1] = a * y_linear[tau] + b * u[tau];
        cout << "Шаг " << tau + 1 << ": Температура = " << fixed << setprecision(2) << y_linear[tau + 1] << endl;
    }

    // 3. Моделирование нелинейной системы
    // Формула: y_{tau+1} = a * y_{tau} - b * (y_{tau-1})^2 + c * u_{tau} + d * sin(u_{tau-1})
    cout << "\n--- Нелинейная модель ---" << endl;
    for (int tau = 1; tau < n; ++tau) {
        y_nonlinear[tau + 1] = a * y_nonlinear[tau] 
                             - b * pow(y_nonlinear[tau - 1], 2) 
                             + c * u[tau] 
                             + d * sin(u[tau - 1]);
        cout << "Шаг " << tau + 1 << ": Температура = " << fixed << setprecision(2) << y_nonlinear[tau + 1] << endl;
    }

    return 0;
}
