#include "sensordata.h"

SensorData::SensorData()
{
    sensorValue = 0;
    timeStamp = 0;
}

SensorData::SensorData(double val, double time)
{
    sensorValue = val;
    timeStamp = time;
}

double SensorData::getSensorValue()
{
    return sensorValue;
}

double SensorData::getTimeStamp()
{
    return timeStamp;
}

void SensorData::setSensorValue(double inputVal)
{
    sensorValue = inputVal;
}

void SensorData::setTimeStamp(double inputTime)
{
    timeStamp = inputTime;
}
