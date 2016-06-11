#include "datafusion.h"
#include "ranger.h"

DataFusion::DataFusion()
{
}

void DataFusion::copyData(Ranger* rangerArray[2], mutex &mxRadar, mutex &mxSonar)
{
    while(true)
    {
        ////////////////////////////////////////// Sensor 1 Copy //////////////////////////////////////////
        if (rangerArray[0]->getSensorType() == "Radar")
        {
            cout << "copyData locking mxRadar" << endl;
            /********/ mxRadar.lock(); /********/
        }
        else if (rangerArray[0]->getSensorType() == "Sonar")
        {
            cout << "copyData locking mxSonar" << endl;
            /********/ mxSonar.lock(); /********/
        }
        sensor1Deque = rangerArray[0]->getSensorData();
        if (rangerArray[0]->getSensorType() == "Radar")
        {
            cout << "copyData unlocking mxRadar" << endl;
            /********/ mxRadar.unlock(); /********/
        }
        else if (rangerArray[0]->getSensorType() == "Sonar")
        {
            cout << "copyData unlocking mxSonar" << endl;
            /********/ mxSonar.unlock(); /********/
        }
        ////////////////////////////////////////// Sensor 2 Copy //////////////////////////////////////////
        if (rangerArray[1]->getSensorType() == "Radar")
        {
            cout << "copyData locking mxRadar" << endl;
            /********/ mxRadar.lock(); /********/
        }
        else if (rangerArray[1]->getSensorType() == "Sonar")
        {
            cout << "copyData locking mxSonar" << endl;
            /********/ mxSonar.lock(); /********/
        }
        sensor2Deque = rangerArray[1]->getSensorData();
        if (rangerArray[1]->getSensorType() == "Radar")
        {
            cout << "copyData unlocking mxRadar" << endl;
            /********/ mxRadar.unlock(); /********/
        }
        else if (rangerArray[1]->getSensorType() == "Sonar")
        {
            cout << "copyData unlocking mxSonar" << endl;
            /********/ mxSonar.unlock(); /********/
        }
        printData(sensor1Deque);
        printData(sensor2Deque);
        delay(500);
    }
}

void DataFusion::printData(deque<SensorData> toPrint)
{
    cout << "Printing deque. Size = " << toPrint.size() << endl;
    for (deque<SensorData>::iterator it = toPrint.begin(); it < toPrint.end(); it++)
        {
            int currentLocation = it - toPrint.begin();
            cout << "Slot #" << currentLocation <<" Value: " << it->getSensorValue() << endl;
        }
}
