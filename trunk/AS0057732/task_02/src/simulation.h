#pragma once

#include <vector>

std::vector<double> linear_model(
    const std::vector<double>& input,
    double alpha,
    double beta,
    double initial_temp
);

std::vector<double> nonlinear_model(
    const std::vector<double>& input,
    double alpha,
    double beta,
    double gamma,
    double delta,
    double initial_temp,
    double prev_temp
);
