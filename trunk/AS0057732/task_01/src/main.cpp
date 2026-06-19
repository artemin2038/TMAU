#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using std::cout;
using std::vector;

vector<double> calc_linear(int steps, double coeff_a, double coeff_b,
                           const vector<double>& input, double start_temp)
{
    vector<double> result(steps + 1, 0.0);
    result[0] = start_temp;

    for (int idx = 0; idx < steps; ++idx) {
        result[idx + 1] = coeff_a * result[idx] + coeff_b * input[idx];
    }
    return result;
}

vector<double> calc_nonlinear(int steps, double coeff_a, double coeff_b,
                              double coeff_c, double coeff_d,
                              const vector<double>& input,
                              double start_temp, double prev_temp)
{
    vector<double> result(steps + 1, 0.0);
    result[0] = start_temp;
    double prev_input = 0.0;

    for (int idx = 0; idx < steps; ++idx) {
        double y_prev = (idx == 0) ? prev_temp : result[idx - 1];
        double u_prev = (idx == 0) ? prev_input : input[idx - 1];

        result[idx + 1] = coeff_a * result[idx]
                        - coeff_b * (y_prev * y_prev)
                        + coeff_c * input[idx]
                        + coeff_d * std::sin(u_prev);
    }
    return result;
}

void print_separator() {
    cout << "+-----------+----------+------------------+-------------------+\n";
}

int main()
{
    constexpr int TOTAL_STEPS    = 15;
    constexpr double A_LIN       = 0.9;
    constexpr double B_LIN       = 0.35;
    constexpr double A_NLIN      = 0.9;
    constexpr double B_NLIN      = 0.015;
    constexpr double C_NLIN      = 0.35;
    constexpr double D_NLIN      = 0.25;
    constexpr double ROOM_TEMP   = 22.0;
    constexpr double PREV_TEMP   = 22.0;
    constexpr double HEAT_INPUT  = 10.0;

    vector<double> control_signal(TOTAL_STEPS, HEAT_INPUT);

    vector<double> lin_result  = calc_linear(
        TOTAL_STEPS, A_LIN, B_LIN, control_signal, ROOM_TEMP);

    vector<double> nlin_result = calc_nonlinear(
        TOTAL_STEPS, A_NLIN, B_NLIN, C_NLIN, D_NLIN,
        control_signal, ROOM_TEMP, PREV_TEMP);

    cout << std::fixed << std::setprecision(4);
    print_separator();
    cout << "|    Step   |  u(tau)  |  y_linear(tau)  | y_nonlinear(tau) |\n";
    print_separator();

    for (int t = 0; t <= TOTAL_STEPS; ++t) {
        cout << "| " << std::setw(9) << t << " | ";

        if (t < TOTAL_STEPS)
            cout << std::setw(8) << control_signal[t] << " | ";
        else
            cout << std::setw(8) << "---" << " | ";

        cout << std::setw(16) << lin_result[t] << " | "
             << std::setw(17) << nlin_result[t] << " |\n";
    }
    print_separator();

    return 0;
}
