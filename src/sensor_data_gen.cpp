#include "sensor_data_gen.h"

#include <random>
#include <cmath>

double OBJ_POS_RANGE = 101;
double OBJ_VEL_RANGE = 20;

SensorDataGen::SensorDataGen(double sensorNoise, int numObj, double timestep)
    : currTime(0.0), sensorNoise(sensorNoise), numObj(numObj), timestep(timestep) {

    std::uniform_real_distribution<double> unifPos(0, OBJ_POS_RANGE);
    std::uniform_real_distribution<double> unifVel(0, OBJ_VEL_RANGE);

    for (int i = 0; i < numObj; ++i) {
        objList.push_back(
            trueObj(i, unifPos(re), unifPos(re), unifVel(re), unifVel(re))
        );
    }
}

// ====== Data Generation Helper Functions ====== //
void SensorDataGen::genLidarData() {
    lidarScanOutput.points.clear(); // Previously generated points are still in vector

    // Simulate sensor inaccuracies using a normal distributions (others can be used)
    std::normal_distribution<double> normal(1, sensorNoise / (double) 100);

    for (int i = 0; i < numObj; ++i) {
        lidarScanOutput.points.push_back(lidarPoint(
            sqrt(pow(objList[i].truePosX, 2) + pow(objList[i].truePosY, 2)) * normal(re), // Calculate distance using pythagorean theorem
            atan2(objList[i].truePosX, objList[i].truePosY) * (180 / M_PI) * normal(re)         // Calculate angle using trig, convert to degrees
            ));
    }

    lidarScanOutput.timestamp = currTime;
}

void SensorDataGen::genRadarData() {
    return;
}

void SensorDataGen::genCameraData() {
    return;
}

// ====== Data Generation ====== //
void SensorDataGen::genSensorData() {
    genLidarData();
    genRadarData();
    genCameraData();
}

void SensorDataGen::updateTime() {
    currTime += timestep;
    // Do calculations for updating position based on velocity
}

// ====== Getter Functions ====== //
lidarScan SensorDataGen::getLidarOutput() {
    return lidarScanOutput;
}

std::vector<radarOutput> SensorDataGen::getRadarOutput() {
    return radarOutput;
}

std::vector<cameraOutput> SensorDataGen::getCameraOutput() {
    return cameraOutput;
}