/**
* Contains the data structures used to hold the data "generated" by the sensors
*
* I feel like this entire file could benefit from some polymorphism... may decide to implement later
*/

#pragma once

#include <vector>

/**
* LiDAR uses lasers to scan an area to obtain information. Each point has a distance and angle
* associated with it, and multiple of these points are put together to create the scan
*/
struct lidarPoint {
    double distance;
    double angle;
};

struct lidarScan {
    std::vector<lidarPoint> points;
    double timestamp;
};

/**
* Assuming radars pre-process detection of objects (i.e. output will be characteristics of object)
*/
struct radarOutput {
    double range;
    double velocity;
    double angle;
};

/**
* Camera output will provide a "bounding box"
*/
struct cameraOutput {
    double x, y; // x, y coordinates of top-left corner of bounding box
    double width, height; // Width and height of the box
};

/**
 * Object's actual position and velocity
 */
struct trueObj {
    int id;
    double truePosX, truePosY; // Position in meters, note: xy-plane is parallel to ground
    double trueVelX, trueVelY; // Velocity in m/s
};

/**
* Object that is tracked after processing data outputs - may be different from actual pos and vel
*/
struct trackedObj {
    int id;
    double posX, posY; // Position in meters, note: xy-plane is parallel to ground
    double velX, velY; // Velocity in m/s
    double confidence;
    double last_updated_timestamp; // Time in seconds
};