#include "model.h"
#include <cmath>

std::vector<double> simulateLinear(int n, double a, double b, double y0, const std::vector<double>& u) {
    std::vector<double> y(n + 1, 0.0);
    y[0] = y0;
    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

std::vector<double> simulateNonlinear(int n, double a, double b, double c, double d, double y0, double y_minus1, const std::vector<double>& u, double u_minus1) {
    std::vector<double> y(n + 1, 0.0);
    y[0] = y0;
    double prev_y = y_minus1;
    double prev_u = u_minus1;

    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] - b * std::pow(prev_y, 2) + c * u[t] + d * std::sin(prev_u);
        prev_y = y[t];
        prev_u = u[t];
    }
    return y;
}