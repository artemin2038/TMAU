#include "temperature_model.hpp"

int main() {
    TemperatureModel model(0.8, 0.3, 0.4, 0.1);
    model.runSimulation(20, 20.0, 5.0);
    return 0;
}