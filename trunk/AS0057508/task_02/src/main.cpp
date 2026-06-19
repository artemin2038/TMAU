#include <iostream>
#include <vector>
#include <iomanip>
#include "model.h"

using namespace std;

int main() {
    int n = 10;
    double a = 0.8, b = 0.5, c = 0.3, d = 0.1;

    vector<double> u(n + 1, 1.0); 
    vector<double> y_linear(n + 1, 0.0);
    vector<double> y_nonlinear(n + 1, 0.0);

    y_linear[0] = 20.0; 
    y_nonlinear[0] = 20.0; 
    y_nonlinear[1] = 20.0; 

    cout << "--- Linear Model ---" << endl;
    for (int tau = 0; tau < n; ++tau) {
        y_linear[tau + 1] = calculateLinearStep(y_linear[tau], u[tau], a, b);
        cout << "Step " << tau + 1 << ": Temp = " << fixed << setprecision(2) << y_linear[tau + 1] << endl;
    }

    cout << "\n--- Nonlinear Model ---" << endl;
    for (int tau = 1; tau < n; ++tau) {
        y_nonlinear[tau + 1] = calculateNonlinearStep(y_nonlinear[tau], y_nonlinear[tau - 1], u[tau], u[tau - 1], a, b, c, d);
        cout << "Step " << tau + 1 << ": Temp = " << fixed << setprecision(2) << y_nonlinear[tau + 1] << endl;
    }

    return 0;
}
