#ifndef MODEL_H
#define MODEL_H

#include <vector>

std::vector<double> simulateLinear(int n, double a, double b, double y0, const std::vector<double>& u);
std::vector<double> simulateNonlinear(int n, double a, double b, double c, double d, double y0, double y_minus1, const std::vector<double>& u, double u_minus1);

#endif // MODEL_H