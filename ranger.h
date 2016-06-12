#ifndef RANGER_H
#define RANGER_H

#include <string>
#include <deque>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

#include "sensordata.h"

using namespace std;

inline void delay( unsigned long ms )
{
    std::chrono::milliseconds duration(ms);
    std::this_thread::sleep_for(duration);
}


/**
 * @brief
 * This is the abstract base class that inherits from Laser, Sonar and Radar. All methods are virtual, so that when called the program will instead seek the respective method in Laser, Sonar or Radar classes. For more information on each method, refer to the sub-classes.
 */
class Ranger
{
public:
    /**
     * @brief
     *
     */
    Ranger();

// GET Methods
    /**
     * @brief
     * Returns the model of Radar
     * @return string
     */
    string getModel();
    /**
     * @brief
     * Returns the port directory of Radar
     * @return string
     */
    string getPortDir();
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
     * returns the FOV of Radar
     * @return int
     */
    int getFOV();
    /**
     * @brief
     * returns the Port Number of Radar
     * @return int
     */
    int getPortNumber();
    /**
     * @brief
     * returns the Baud Rate of Radar
     * @return int
     */
    int getBaud();
    /**
     * @brief
     *
     * @return
     */
    string getSensorType();
    deque<SensorData> getSensorData();
    /**
     * @brief
     * compares the parameter taken in against the MIN_DISTANCE and MAX_DISTANCE properties of Radar. If the parameter "check" is equal to either, returns "true" to signify that the value should be disregarded. This is called in RangerFusion
     * @param check
     * @return bool
     */
    bool disregard(double check);
    /**
     * @brief
     * sets the portNumber to the parameter taken in. As the Rangers are initialised in the order Laser > Radar > Sonar, this method also ensures that Radar's portNumber does not clash with Laser.
     * Lastly, this method also returns a 1 if successful, or a 0 if unsuccessful.
     * @param int
     * @return int
     */
    int setPORT(int);
    /**
     * @brief
     * sets the Baud to the parameter taken in, as long as that value is sane. This method also returns a 1 if successful, or a 0 if unsuccessful.
     * @param int
     * @return int
     */
    int setBaud(int);
    /**
     * @brief
     * @return
     */
    int setFOV(int);
    void genData1(chrono::steady_clock::time_point progStartTime, mutex &mx1);
    void genData0(chrono::steady_clock::time_point progStartTime, mutex &mx0);
    void printData();

protected:
    //Sensor Variables
    unsigned int baud; /**< Baud Rate */
    unsigned int portNumber; /**< Number of the Port */
    bool portSet; /**< Has the port been set? */
    string portDir; /**< Directory of the Port */
    unsigned int FOV; /**< Field of View */
    string model; /**< Model Name */
    double minDistance; /**< Minimum Distance */
    double maxDistance; /**< Maximum Distance */
    deque<SensorData> sensorDeque;
    string sensorType;
    int dataRate;
    int dataRate_ms;

    //Sensor Variable Options
    const int baud0_ = 38400;
    const int baud1_ = 115200;
    const int port0_ = 0;
    const int port1_ = 1;
    const int port2_ = 2;
    const string PORT_STRING_ = "USB: /dev/ttyACM";
    const double MIN_DISTANCE_ = 0.2;

};

#endif // RANGER_H
