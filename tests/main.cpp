#include "../src/data_gen/data_structures.h"
#include "../src/data_gen/sensor_data_gen.h"

#include <iostream>

int main() {
    double sensorNoise = 5; // % standard deviation in sensor error
    int numObj = 3;
    double timeStep = 1;

    SensorDataGen generator(sensorNoise, numObj, timeStep);

    generator.genSensorData();

    lidarScan lidarScanOut = generator.getLidarOutput();
    std::vector<radarData> radarOutput = generator.getRadarOutput();

    std::cout << ("Finished generating data point");

    return 0;
}