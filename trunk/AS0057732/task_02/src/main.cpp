#include <iostream>
#include <iomanip>
#include "simulation.h"

int main()
{
    constexpr int N = 15;
    constexpr double A  = 0.9;
    constexpr double B  = 0.35;
    constexpr double C  = 0.9;
    constexpr double D  = 0.015;
    constexpr double E  = 0.35;
    constexpr double F  = 0.25;
    constexpr double Y0 = 22.0;
    constexpr double YM = 22.0;

    std::vector<double> ctrl(N, 10.0);

    auto lin_res  = linear_model(ctrl, A, B, Y0);
    auto nlin_res = nonlinear_model(ctrl, C, D, E, F, Y0, YM);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "tau | u | linear | nonlinear\n";
    std::cout << "-----------------------------\n";

    for (std::size_t t = 0; t <= ctrl.size(); ++t) {
        std::cout << std::setw(3) << t << " | ";
        if (t < ctrl.size())
            std::cout << std::setw(5) << ctrl[t] << " | ";
        else
            std::cout << "  --- | ";

        std::cout << std::setw(7) << lin_res[t] << " | "
                  << std::setw(9) << nlin_res[t] << "\n";
    }

    return 0;
}
