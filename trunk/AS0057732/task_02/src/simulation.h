#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

std::vector<double> simulateLinear(const std::vector<double>& u, double a, double b, double y0);

std::vector<double> simulateNonlinear(const std::vector<double>& u, double a, double b, 
                                      double c, double d, double y0, double y_minus1);

#endif // SIMULATION_H