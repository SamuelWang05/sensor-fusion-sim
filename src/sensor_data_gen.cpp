#include "sensor_data_gen.h"

#include <random>
#include <cmath>

double OBJ_POS_RANGE = 101;
double OBJ_VEL_RANGE = 20000; // 20 kmh

SensorDataGen::SensorDataGen(double sensorNoise, int numObj, double timestep)
    : currTime(0.0), sensorNoise(sensorNoise), numObj(numObj), timestep(timestep), normal(1, sensorNoise / (double) 100) {

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

    for (int i = 0; i < numObj; ++i) {
        lidarScanOutput.points.push_back(lidarPoint(
            sqrt(pow(objList[i].truePosX, 2) + pow(objList[i].truePosY, 2)) * normal(re), // Calculate distance using pythagorean theorem
            atan2(objList[i].truePosY, objList[i].truePosX) * (180 / M_PI) * normal(re)         // Calculate angle using trig, convert to degrees
            ));
    }

    lidarScanOutput.timestamp = currTime;
}

void SensorDataGen::genRadarData() {
    radarOutput.clear();

    for (int i = 0; i < numObj; ++i) {
        radarOutput.push_back(radarData(
            sqrt(pow(objList[i].truePosX, 2) + pow(objList[i].truePosY, 2)) * normal(re), // Calculate distance using pythagorean theorem
            sqrt(pow(objList[i].trueVelX,2) + pow(objList[i].trueVelY, 2)) * normal(re), // TODO -- Need to update to radial velocity
            atan2(objList[i].truePosY, objList[i].truePosX) * (180 / M_PI) * normal(re)
        ));
    }
}

// ====== Data Generation ====== //
void SensorDataGen::genSensorData() {
    genLidarData();
    genRadarData();
}

void SensorDataGen::updateTime() {
    currTime += timestep;

    for (int i = 0; i < numObj; ++i) {
        objList[i].truePosX += objList[i].trueVelX * timestep;
        objList[i].truePosY += objList[i].trueVelY * timestep;
    }
}

// ====== Getter Functions ====== //
lidarScan SensorDataGen::getLidarOutput() {
    return lidarScanOutput;
}

std::vector<radarData> SensorDataGen::getRadarOutput() {
    return radarOutput;
}