#include "data_structures.h"
#include "sensor_data_gen.h"

#include <iostream>

int main() {
    double sensorNoise = 10;
    int numObj = 3;
    double timeStep = 1;

    SensorDataGen generator(sensorNoise, numObj, timeStep);

    generator.genSensorData();

    lidarScan lidarScanOut = generator.getLidarOutput();

    std::cout << ("Finished generating data point");

    return 0;
}