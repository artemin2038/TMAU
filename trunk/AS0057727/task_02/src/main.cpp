#include <iostream>
#include <iomanip>
#include "simulation.h"

int main() {
    const int steps = 15;
    const double a_lin = 0.85, b_lin = 0.4;
    const double a_nonlin = 0.85, b_nonlin = 0.01, c_nonlin = 0.4, d_nonlin = 0.2;
    const double y0 = 20.0, y_minus1 = 20.0;
    
    std::vector<double> u(steps, 12.0); 
    
    std::vector<double> y_linear = simulateLinear(u, a_lin, b_lin, y0);
    std::vector<double> y_nonlinear = simulateNonlinear(u, a_nonlin, b_nonlin, c_nonlin, d_nonlin, y0, y_minus1);
    
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Step (tau) |  u(tau)  |  y(tau) Linear  |  y(tau) Nonlinear\n";
    std::cout << "-------------------------------------------------------------\n";
    
    for (size_t t = 0; t <= u.size(); ++t) {
        std::cout << std::setw(9) << t << " | ";
        if (t < u.size()) std::cout << std::setw(8) << u[t] << " | ";
        else std::cout << std::setw(8) << "-" << " | ";
        
        std::cout << std::setw(16) << y_linear[t] << " | " << std::setw(17) << y_nonlinear[t] << "\n";
    }
    return 0;
}