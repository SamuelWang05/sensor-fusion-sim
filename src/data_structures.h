/**
* Contains the data structures used to hold the data "gathered" by the sensors
*/

#pragma once

/**
* LiDAR uses lasers to scan an area to obtain information. Each point has a distance and angle
* associated with it, and multiple of these points are put together to create the scan
*/
struct liDarPoint {
    double distance;
    double angle;
};

struct liDarScan {
    liDarPoint points[50]; // 50 is arbritrary
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
* Object that is tracked after processing data outputs
*/
struct trackedObj {
    int id;
    double posX, posY;
    double velX, velY;
    double confidence;
    double last_updated_timestamp;
};