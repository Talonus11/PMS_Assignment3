#ifndef RANGER_H
#define RANGER_H

#include <string>

using namespace std;


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
     *
     * @return string
     */
    virtual string getModel(void) = 0;
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
     *
     * @return double
     */
    virtual double getMaxDistance(void) = 0;
    /**
     * @brief
     *
     * @return double
     */
    virtual double getAngularResolution(void) = 0;
    /**
     * @brief
     *
     * @return int
     */
    virtual int getFOV(void) = 0;
    /**
     * @brief
     * returns the Port Nmber of Radar
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
     * @return double
     */
//    virtual double* getArray(void) = 0;
//    /**
//     * @brief
//     *
//     * @return
//     */
    virtual int getSensorType(void) = 0;
    /**
     * @brief
     *
     * @param check
     * @return bool
     */
    virtual bool disregard(double check) = 0;
//    /**
//     * @brief
//     *
//     */
//    virtual void genArray(void) = 0;
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
    virtual int setFOV(int) = 0;
    /**
     * @brief
     * @return
     */
//    virtual int setAngularResolution(int) = 0;

private:
    //Sensor Variables
    unsigned int baud; /**< Baud Rate */
    unsigned int portNumber; /**< Number of the Port */
    bool portSet; /**< Has the port been set? */
    string portDir; /**< Directory of the Port */
    double minDistance; /**< Minimum Distance */



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
