#ifndef SENSORDATA_H
#define SENSORDATA_H

class SensorData
{
public:
    SensorData();
    SensorData(double val, double time);
    double getSensorValue();
    double getTimeStamp();
    void setTimeStamp(double inputTime);
    void setSensorValue(double inputVal);

private:
    double sensorValue;
    double timeStamp;
};

#endif // SENSORDATA_H
