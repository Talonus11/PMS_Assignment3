#ifndef DATAFUSION_H
#define DATAFUSION_H

#include <deque>
#include <mutex>
#include <iostream>
#include "sensordata.h"
#include "ranger.h"
class DataFusion
{
public:
    DataFusion();
    void run(Ranger* rangerArray[2], mutex &mx0, mutex &mx1, chrono::steady_clock::time_point progStartTime, string fusion);
    double extrapolate(deque<SensorData> sensorDeque, chrono::_V2::steady_clock::time_point progStartTime_, int i);
    double minFusion(double e1, double e2);
    double avgFusion(double e1, double e2);
    double maxFusion(double e1, double e2);
    void printData(deque<SensorData>);

private:
    std::deque<SensorData> outputDeque;
    std::deque<SensorData> sensor1Deque;
    std::deque<SensorData> sensor2Deque;
    double sensor1MaxDistance;
    double sensor2MaxDistance;
//    string sensor1Type;
//    string sensor2Type;
};

#endif // DATAFUSION_H
