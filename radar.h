#ifndef RADAR_H
#define RADAR_H
#include <string>
#include <deque>
#include <chrono>

#include "ranger.h"
#include "sensordata.h"

using namespace std;

/**
 * @brief
 * The Radar class is a sub-class of Ranger. It is one of 3 types of Ranger used for distance sensing.
 */
class Radar : public Ranger
{
public:
    /**
     * @brief
     *
     */
    Radar();

// GET Methods
    /**
     * @brief
     * Returns the model of Radar
     * @return string
     */
    string getModel();

    /**
     * @brief
     * returns the MIN_DISTANCE of Radar
     * @return double
     */
    double getMinDistance();
    /**
     * @brief
     * returns the MAX_DISTANCE of Radar
     * @return double
     */
    double getMaxDistance();
    /**
     * @brief
     * returns the Angular Resolution of Radar. Since Radar does not have an Angular Resolution this returns -1. It is included so that the code is agnostic.
     * @return double
     */
    double getAngularResolution();
    /**
     * @brief
     * returns the FOV of Radar
     * @return int
     */
    int getFOV();


    /**
     * @brief
     * returns the generated array of normally distributed values, representing a distance scan performed by Radar
     * @return double
     */
    double* getArray();
    /**
     * @brief
     * returns the type of sensor: 0 = Laser, 1 = Radar, 2 = Sonar
     * @return
     */
    int getSensorType();

// SET Methods

    /**
     * @brief
     * sets the FOV to the parameter taken in, as long as that value is sane. This method also returns a 1 if successful, or a 0 if unsuccessful.
     * @param int
     * @return int
     */
    int setFOV(int);


//    /**
//     * @brief
//     * generates an array of size 13, populating it with values taken from Generator's normal distribution generator. This is saved into the array scanValues in Radar.
//     */
//    void genArray();
    /**
     * @brief
     * compares the parameter taken in against the MIN_DISTANCE and MAX_DISTANCE properties of Radar. If the parameter "check" is equal to either, returns "true" to signify that the value should be disregarded. This is called in RangerFusion
     * @param check
     * @return bool
     */
    bool disregard(double check);
//    /**
//     * @brief
//     * returns -1. This method does not serve a purpose for radar, as it does not have an angular resolution. The method exists to allow for agnostic code only.
//     * @return
//     */
//    int setAngularResolution(int);
//    void initSensorData(int size);
    deque<SensorData> getSensorData();
    void genData(chrono::steady_clock::time_point progStartTime);
    void printData();

private:

    //Sensor Variables
    string model; /**< Model Name */
    unsigned int FOV; /**< Field of View */
    double minDistance; /**< Minimum Distance */
    double maxDistance; /**< Maximum Distance */
    int angRes; /**< Angular Resolution */
    int dataRate;
    //double scanValues[13]; /**< Array of scanned values */
    int sensorType = 0; /**< Identifies sensor as Radar */
    deque<SensorData> sensorArray;

    //Sensor Variable Options
    const int FOV1_ = 20;
    const int FOV2_ = 40;
    const string MODEL_ = "RAD-001";
    const double MAX_DISTANCE_ = 10.0;
    const double MIN_DISTANCE_ = 0.2;


    const int DATA_RATE_ = 10;

};

#endif // RADAR_H
