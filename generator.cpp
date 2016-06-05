#include "generator.h"
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include <chrono>

using namespace std;

Generator::Generator()
{
}

// normal generator with clipping to 0.2 and max value passed in as argument

double Generator::normalGenerator(double mean, double stdDev, double max)
{
    double randomVal;
    static default_random_engine generator(time(0));
    normal_distribution<double> distribution(mean,stdDev);
    randomVal = distribution(generator);
    if (randomVal < 0.2) // clips values below 0.2 to minDistance
    {
        randomVal = 0.2;
    }
    if (randomVal > max) // clips values above max to max, where max is passed in as an argument
    {
        randomVal = max;
    }
    return randomVal;
}

// normal generator with no clipping

double Generator::normalGenerator(double mean, double stdDev)
{
    static default_random_engine generator(time(0));
    normal_distribution<double> distribution(mean,stdDev);
    return distribution(generator);
}

// range generator

double Generator::rangeGenerator(double timeDiff)
{
    using namespace std::chrono;
    double r;
    double t = timeDiff;
//    cout << "t = " << t << endl;
    double omega = 2*M_PI*0.01;
//    cout << "omega = " << omega << endl;
    double delta = normalGenerator(0,0.1);
//    cout << "delta = " << delta << endl;
    r = (6 + (4*sin(omega*t)) + delta);
    return r;

}
