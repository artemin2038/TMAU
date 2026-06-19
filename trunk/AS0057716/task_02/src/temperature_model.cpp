#include "temperature_model.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

TemperatureModel::TemperatureModel(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d) {}

double TemperatureModel::linearModel(double y, double u) const {
    return a * y + b * u;
}

double TemperatureModel::nonlinearModel(double y, double y_prev, double u, double u_prev) const {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u_prev);
}

double TemperatureModel::generateControlSignal(int tau) const {
    return (tau < 10) ? 5.0 : 10.0;
}

void TemperatureModel::runSimulation(int steps, double y0, double u0) {
    std::vector<double> y_lin(steps + 1), y_nonlin(steps + 1), u(steps + 1);
    y_lin[0] = y0;
    y_nonlin[0] = y0;
    u[0] = u0;

    for (int tau = 1; tau <= steps; ++tau) {
        u[tau] = generateControlSignal(tau);
    }

    std::cout << "=========================================================" << std::endl;
    std::cout << "tau\ty_linear\ty_nonlinear\tu" << std::endl;
    std::cout << "=========================================================" << std::endl;

    for (int tau = 1; tau <= steps; ++tau) {
        y_lin[tau] = linearModel(y_lin[tau - 1], u[tau - 1]);

        if (tau == 1) {
            y_nonlin[tau] = nonlinearModel(y_nonlin[tau - 1], y0, u[tau - 1], u0);
        } else {
            y_nonlin[tau] = nonlinearModel(y_nonlin[tau - 1], y_nonlin[tau - 2], u[tau - 1], u[tau - 2]);
        }

        std::cout << std::setw(3) << tau
                  << std::setw(12) << std::fixed << std::setprecision(2) << y_lin[tau]
                  << std::setw(16) << y_nonlin[tau]
                  << std::setw(10) << u[tau - 1] << std::endl;
    }

    lastLinear = y_lin[steps];
    lastNonlinear = y_nonlin[steps];

    std::cout << "=========================================================" << std::endl;
    std::cout << "Конечная температура (линейная): " << lastLinear << std::endl;
    std::cout << "Конечная температура (нелинейная): " << lastNonlinear << std::endl;
}