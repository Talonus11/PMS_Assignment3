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
     *
     * @return string
     */
    virtual string getPortDir(void) = 0;
    /**
     * @brief
     *
     * @return double
     */
    virtual double getMinDistance(void) = 0;
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
     *
     * @return int
     */
    virtual int getPortNumber(void) = 0;
    /**
     * @brief
     *
     * @return int
     */
    virtual int getBaud(void) = 0;
    /**
     * @brief
     *
     * @return double
     */
    virtual double* getArray(void) = 0;
    /**
     * @brief
     *
     * @return
     */
    virtual int getSensorType(void) = 0;
    /**
     * @brief
     *
     * @param check
     * @return bool
     */
    virtual bool disregard(double check) = 0;
    /**
     * @brief
     *
     */
    virtual void genArray(void) = 0;
    /**
      *@brief
      *
      */
    virtual int setPORT(int) = 0;
    /**
     * @brief
     * @return
     */
    virtual int setBaud(int) = 0;
    /**
     * @brief
     * @return
     */
    virtual int setFOV(int) = 0;
    /**
     * @brief
     * @return
     */
    virtual int setAngularResolution(int) = 0;
};

#endif // RANGER_H
