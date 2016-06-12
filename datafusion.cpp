#include "datafusion.h"
#include "ranger.h"

DataFusion::DataFusion()
{
}

void DataFusion::copyDataS(Ranger sonar, mutex &mxSonar)
{

}

void DataFusion::copyDataR(Ranger radar, mutex &mxRadar)
{

}

void DataFusion::run(Ranger* rangerArray[2], mutex &mx0, mutex &mx1)
{
    while(true)
    {
        ////////////////////////////////////////// Sensor 1 Copy //////////////////////////////////////////
        cout << "run() locking mx0" << endl;
            /********/ mx0.lock(); /********/
        sensor1Deque = rangerArray[0]->getSensorData();
        cout << "run() unlocking mx0" << endl;
            /********/ mx0.unlock(); /********/
        ////////////////////////////////////////// Sensor 2 Copy //////////////////////////////////////////
        cout << "run() locking mx1" << endl;
            /********/ mx1.lock(); /********/
        sensor2Deque = rangerArray[1]->getSensorData();
        cout << "run() unlocking mx1" << endl;
            /********/ mx1.unlock(); /********/
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
