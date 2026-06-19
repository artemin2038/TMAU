#include "simulation.h"
#include <cmath>

std::vector<double> simulateLinear(const std::vector<double>& u, const double a, const double b, const double y0) {
    const size_t n = u.size();
    std::vector<double> y(n + 1, 0.0);
    y[0] = y0;
    
    for (size_t t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

std::vector<double> simulateNonlinear(const std::vector<double>& u, const double a, const double b, 
                                      const double c, const double d, const double y0, const double y_minus1) {
    const size_t n = u.size();
    std::vector<double> y(n + 1, 0.0);
    y[0] = y0;
    
    const double u_minus1 = 0.0;
    
    for (size_t t = 0; t < n; ++t) {
        double prev_y = (t == 0) ? y_minus1 : y[t - 1];
        double prev_u = (t == 0) ? u_minus1 : u[t - 1];
        
        y[t + 1] = a * y[t] - b * (prev_y * prev_y) + c * u[t] + d * std::sin(prev_u);
    }
    return y;
}