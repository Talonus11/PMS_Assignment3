#ifndef GENERATOR_H
#define GENERATOR_H

#include <ctime>
#include <random>
#include <chrono>

/**
 * @brief
 * Generator is used to generate normally distributed values. It is called by any program that requires random normally distributed values.
 */
class Generator
{
public:
    /**
     * @brief
     *
     */
    Generator();
    /**
     * @brief
     * returns a double value that follows a normal distribution, set by the mean and stdDev that are passed into the function as parameters. As this function is also intended to be used with sensors, it is built-in with clipping to the minimum and maximum values of the sensor. The minimum value is constant for all 3 sensors, and the maximum value is passed as an argument.
     * @param mean/
     * @param stdDev
     * @param max
     * @return double
     */
    double normalGenerator(double mean, double stdDev, double max);
    double normalGenerator(double mean, double stdDev);
    double rangeGenerator(double timeDiff, double max, double min);


private:

};

#endif // GENERATOR_H
