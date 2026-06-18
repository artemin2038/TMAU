#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Функция для моделирования линейного объекта
// y_{τ+1} = a * y_τ + b * u_τ
std::vector<double> simulateLinear(int n, double a, double b, const std::vector<double>& u, double y0) {
    std::vector<double> y(n + 1, 0.0);
    y[0] = y0; // Начальное значение температуры
    
    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

// Функция для моделирования нелинейного объекта
// y_{τ+1} = a * y_τ - b * y_{τ-1}^2 + c * u_τ + d * sin(u_{τ-1})
std::vector<double> simulateNonlinear(int n, double a, double b, double c, double d, 
                                      const std::vector<double>& u, double y0, double y_minus1) {
    std::vector<double> y(n + 1, 0.0);
    y[0] = y0;
    
    // Примем его равным 0.0 по умолчанию
    double u_minus1 = 0.0;
    
    for (int t = 0; t < n; ++t) {
        // Определение предыдущих значений с учетом начальных условий на шаге t = 0
        double prev_y = (t == 0) ? y_minus1 : y[t - 1];
        double prev_u = (t == 0) ? u_minus1 : u[t - 1];
        
        y[t + 1] = a * y[t] - b * (prev_y * prev_y) + c * u[t] + d * std::sin(prev_u);
    }
    return y;
}

int main() {
    // Количество дискретных моментов времени (шагов симуляции)
    const int n = 15;
    
    // Коэффициенты-константы для линейной модели (примерные значения)
    double a_lin = 0.85;
    double b_lin = 0.4;
    
    // Коэффициенты-константы для нелинейной модели (примерные значения)
    double a_nonlin = 0.85;
    double b_nonlin = 0.01; // малый коэффициент, чтобы система была стабильной
    double c_nonlin = 0.4;
    double d_nonlin = 0.2;
    
    // Начальные условия
    double y0 = 20.0;        // Температура в начальный момент y(0)
    double y_minus1 = 20.0;  // Температура в предшествующий момент y(-1) для нелинейной модели
    
    // Входной поток тепла / управление u(τ) на каждом шаге
    // Заполнение массива постоянным значением 
    std::vector<double> u(n, 12.0); 
    
    // Выполнение симуляции
    std::vector<double> y_linear = simulateLinear(n, a_lin, b_lin, u, y0);
    std::vector<double> y_nonlinear = simulateNonlinear(n, a_nonlin, b_nonlin, c_nonlin, d_nonlin, u, y0, y_minus1);
    
    // вывод результатов в консоль
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Step (tau) |  u(tau)  |  y(tau) Linear  |  y(tau) Nonlinear\n";
    std::cout << "-------------------------------------------------------------\n";
    
    for (int t = 0; t <= n; ++t) {
        std::cout << std::setw(9) << t << " | ";
        
        if (t < n) {
            std::cout << std::setw(8) << u[t] << " | ";
        } else {
            std::cout << std::setw(8) << "-" << " | "; // на последнем шаге n управление уже не прикладывается
        }
        
        std::cout << std::setw(16) << y_linear[t] << " | "
                  << std::setw(17) << y_nonlinear[t] << "\n";
    }
    
    return 0;
}