#ifndef TEMPERATURE_MODEL_HPP
#define TEMPERATURE_MODEL_HPP

class TemperatureModel {
public:
    // Конструктор с параметрами
    TemperatureModel(double a = 0.8, double b = 0.3, double c = 0.4, double d = 0.1);

    // Линейная модель: y_{t+1} = a*y_t + b*u_t
    double linearModel(double y, double u) const;

    // Нелинейная модель: y_{t+1} = a*y_t - b*y_{t-1}^2 + c*u_t + d*sin(u_{t-1})
    double nonlinearModel(double y, double y_prev, double u, double u_prev) const;

    // Генерация управляющего сигнала
    double generateControlSignal(int tau) const;

    // Запуск симуляции
    void runSimulation(int steps, double y0, double u0);

    // Геттеры для результатов
    double getLastLinear() const { return lastLinear; }
    double getLastNonlinear() const { return lastNonlinear; }

private:
    double a, b, c, d;
    double lastLinear = 0.0;
    double lastNonlinear = 0.0;
};

#endif // TEMPERATURE_MODEL_HPP