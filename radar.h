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

private:

    //Sensor Variables
    //double scanValues[13]; /**< Array of scanned values */

    //Sensor Variable Options
    const int FOV1_ = 20;
    const int FOV2_ = 40;
    const string MODEL_ = "RAD-001";
    const double MAX_DISTANCE_ = 10.0;
    const int DATA_RATE_ = 10;
};

#endif // RADAR_H
