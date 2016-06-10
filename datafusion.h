#ifndef DATAFUSION_H
#define DATAFUSION_H

#include <deque>
#include <mutex>
#include "sensordata.h"
#include "ranger.h"
class DataFusion
{
public:
    DataFusion();
    void copyData(Ranger* rangerArray[2], mutex &mxRadar, mutex &mxSonar);
    void extrapolate();
    void minFusion();
    void avgFusion();
    void maxFusion();

private:
    std::deque<SensorData> outputDeque;
    std::deque<SensorData> sensor1Deque;
    std::deque<SensorData> sensor2Deque;
};

#endif // DATAFUSION_H
