#ifndef SONAR_H
#define SONAR_H
#include <string>
#include "ranger.h"

using namespace std;

/**
 * @brief
 * The Sonar class is a sub-class of Ranger. It is one of 3 types of Ranger used for distance sensing.
 */
class Sonar : public Ranger
{
public:
    /**
     * @brief
     *
     */
    Sonar();

private:

    //Sensor Variable Options
    const int FOV_ = 90;
    const string MODEL_ = "SONX-001";
    const double MAX_DISTANCE_ = 6.0;
    const string PORT_STRING_ = "USB: /dev/ttyACM";
    const int DATA_RATE_ = 3;
};

#endif // SONAR_H
