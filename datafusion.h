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
    void run(Ranger* rangerArray[2], mutex &mx0, mutex &mx1);
    void copyDataS(Ranger sonar, mutex &mxSonar);
    void copyDataR(Ranger radar, mutex &mxRadar);
    void extrapolate();
    void minFusion();
    void avgFusion();
    void maxFusion();
    void printData(deque<SensorData>);

private:
    std::deque<SensorData> outputDeque;
    std::deque<SensorData> sensor1Deque;
    std::deque<SensorData> sensor2Deque;
    string sensor1Type;
    string sensor2Type;
};

#endif // DATAFUSION_H
