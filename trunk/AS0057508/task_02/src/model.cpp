#include "model.h"
#include <cmath>

double calculateLinearStep(double y_curr, double u_curr, double a, double b) {
    return a * y_curr + b * u_curr;
}

double calculateNonlinearStep(double y_curr, double y_prev, double u_curr, double u_prev, double a, double b, double c, double d) {
    return a * y_curr - b * std::pow(y_prev, 2) + c * u_curr + d * std::sin(u_prev);
}
