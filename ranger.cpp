#include "ranger.h"
#include "generator.h"
#include <iostream>

Ranger::Ranger()
{
}

string Ranger::getModel()
{
    return model;
}

double Ranger::getMinDistance()
{
    return minDistance;
}

double Ranger::getMaxDistance()
{
    return maxDistance;
}

int Ranger::getBaud()
{
    return baud;
}
int Ranger::getPortNumber()
{
    return portNumber;
}
string Ranger::getPortDir()
{
    return portDir;
}

int Ranger::getFOV()
{
    return FOV;
}

string Ranger::getSensorType()
{
    return sensorType;
}

deque<SensorData> Ranger::getSensorData()
{
    return sensorDeque;
}


int Ranger::setBaud(int input)
{
    if (input == baud0_)
    {
        baud = baud0_;
        return 1;
    }
    else if (input == baud1_)
    {
        baud = baud1_;
        return 1;
    }
    else return 0;
}

int Ranger::setPORT(int input)
{

    if (input == port0_)
    {
        portNumber = port0_;
        portSet = true;
        return 1;
    }
    else if (input == port1_)
    {
        portNumber = port1_;
        portSet = true;
        return 1;
    }
    else if (input == port2_)
    {
        portNumber = port2_;
        portSet = true;
        return 1;
    }
    else return 0;
}

int Ranger::setFOV(int input)
{
    if (sensorType == "Radar")
    {
        if (input == 20)
        {
            FOV = 20;
            return 1;
        }
        else if (input == 40)
        {
            FOV = 40;
            return 1;
        }
    }
    else return 0;
}

bool Ranger::disregard(double check) // checks if the value is clipped, and therefore should be disregarded
{
    if ((check == maxDistance) || (check == minDistance))
    {
        return true;
    }
    else return false;
}

void Ranger::genDataR(chrono::steady_clock::time_point progStartTime, mutex &mxRadar)
{
    Generator rangeGen;
    using namespace std::chrono;
    while(true)
    {
        steady_clock::time_point endTime = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(endTime - progStartTime);
        double timestamp = time_span.count();
        double range = rangeGen.rangeGenerator(timestamp, maxDistance, minDistance);

        cout << "genDataR locking mxRadar" << endl;
        /********/ mxRadar.lock(); /********/
        sensorDeque.push_front(SensorData(range, timestamp)); // initialises Data with values, to front of array
        if (sensorDeque.size() > 150)
            sensorDeque.pop_back();
        //cout << "Val = " << sensorDeque.begin()->getSensorValue() << " Timestamp = " << sensorDeque.begin()->getTimeStamp() << endl;
        cout << "genDataR unlocking mxRadar" << endl;
        /********/ mxRadar.unlock(); /********/
        delay(dataRate_ms);
    }
}

void Ranger::genDataS(chrono::steady_clock::time_point progStartTime, mutex &mxSonar)
{
    Generator rangeGen;
    using namespace std::chrono;
    while(true)
    {
        steady_clock::time_point endTime = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(endTime - progStartTime);
        double timestamp = time_span.count();
        double range = rangeGen.rangeGenerator(timestamp, maxDistance, minDistance);

        /********/ mxSonar.lock(); /********/
        sensorDeque.push_front(SensorData(range, timestamp)); // initialises Data with values, to front of array
        if (sensorDeque.size() > 150)
            sensorDeque.pop_back();
        //cout << "Val = " << sensorDeque.begin()->getSensorValue() << " Timestamp = " << sensorDeque.begin()->getTimeStamp() << endl;
        /********/ mxSonar.unlock(); /********/
        delay(dataRate_ms);
    }
}

void Ranger::printData()
{
    for (deque<SensorData>::iterator it = sensorDeque.begin(); it < sensorDeque.end(); it++)
        {
            int currentLocation = it - sensorDeque.begin();
            cout << "Slot #" << currentLocation <<" Value: " << it->getSensorValue() << endl;
        }
}




