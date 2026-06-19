#include "simulation.h"
#include <cmath>

std::vector<double> linear_model(
    const std::vector<double>& input,
    const double alpha,
    const double beta,
    const double initial_temp)
{
    const std::size_t n = input.size();
    std::vector<double> out(n + 1, 0.0);
    out[0] = initial_temp;

    for (std::size_t i = 0; i < n; ++i) {
        out[i + 1] = alpha * out[i] + beta * input[i];
    }
    return out;
}

std::vector<double> nonlinear_model(
    const std::vector<double>& input,
    const double alpha,
    const double beta,
    const double gamma,
    const double delta,
    const double initial_temp,
    const double prev_temp)
{
    const std::size_t n = input.size();
    std::vector<double> out(n + 1, 0.0);
    out[0] = initial_temp;

    const double u_prev_init = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double y_prev = (i == 0) ? prev_temp : out[i - 1];
        double u_prev = (i == 0) ? u_prev_init : input[i - 1];

        out[i + 1] = alpha * out[i]
                   - beta  * (y_prev * y_prev)
                   + gamma * input[i]
                   + delta * std::sin(u_prev);
    }
    return out;
}
