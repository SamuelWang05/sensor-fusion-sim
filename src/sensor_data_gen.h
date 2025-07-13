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
  std::vector<radarOutput> getRadarOutput();
  std::vector<cameraOutput> getCameraOutput();

private:
  // Helper functions to calculate data
  void genLidarData();
  void genRadarData();
  void genCameraData();

  std::vector<trueObj> objList; // List of objects "on the road"

  // Used to generate random object (obstacle) values
  std::default_random_engine re;
  double currTime;

  // Input values
  double sensorNoise; // standard deviation for % error in sensors
  int numObj; // Keep track of # of obstacles/objects on the road
  double timestep;

  // Output values
  lidarScan lidarScanOutput; // Lidar scan implicitly stores points for all objects scanned
  std::vector<radarOutput> radarOutput;
  std::vector<cameraOutput> cameraOutput;
};