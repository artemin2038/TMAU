#include <iostream>
#include <cmath>
#include <iomanip>

double linearModel(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinearModel(double y, double yPrevious, double u, double uPrevious,
                      double a, double b, double c, double d) {
    return a * y - b * yPrevious * yPrevious + c * u + d * std::sin(uPrevious);
}

int main() {
    const int steps = 20;

double a = 0.8;
double b = 0.001;
double c = 0.12;
double d = 0.05;

    double yLinear = 20.0;
    double yNonlinear = 20.0;
    double yPrevious = 20.0;

    double u = 10.0;
    double uPrevious = 10.0;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Step\tLinear model\tNonlinear model\n";

    for (int t = 1; t <= steps; ++t) {
        double newLinear = linearModel(yLinear, u, a, b);
        double newNonlinear = nonlinearModel(yNonlinear, yPrevious, u, uPrevious, a, b, c, d);

        std::cout << t << "\t" << newLinear << "\t\t" << newNonlinear << '\n';

        yPrevious = yNonlinear;
        yLinear = newLinear;
        yNonlinear = newNonlinear;
        uPrevious = u;
    }

    return 0;
}