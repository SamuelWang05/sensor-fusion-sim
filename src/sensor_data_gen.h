#pragma once

#include <random>

#include "data_structures.h"
#include <vector>

class SensorDataGen {
public:
  SensorDataGen(double sensorNoise, int numObj, double timestep);

  void genSensorData();
  void updateTime();

  lidarScan getLidarOutput();
  std::vector<radarData> getRadarOutput();

private:
  // Helper functions to calculate data
  void genLidarData();
  void genRadarData();

  std::vector<trueObj> objList; // List of objects "on the road"

  // Input values
  double sensorNoise; // standard deviation for % error in sensors
  int numObj; // Keep track of # of obstacles/objects on the road
  double timestep;

  // Used to generate random object (obstacle) values
  std::default_random_engine re;
  std::normal_distribution<double> normal;
  double currTime;

  // Output values
  lidarScan lidarScanOutput; // Lidar scan implicitly stores points for all objects scanned
  std::vector<radarData> radarOutput;
};