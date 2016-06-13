#include "datafusion.h"
#include "ranger.h"

DataFusion::DataFusion()
{
}

void DataFusion::run(Ranger* rangerArray[2], mutex &mx0, mutex &mx1, chrono::_V2::steady_clock::time_point progStartTime, string fusion)
{
    while(true)
    {
        ////////////////////////////////////////// Sensor 1 Copy //////////////////////////////////////////
        cout << "run() locking mx0" << endl;
            /********/ mx0.lock(); /********/
        sensor1Deque = rangerArray[0]->getSensorData();
        sensor1MaxDistance = rangerArray[0]->getMaxDistance();
        cout << "run() unlocking mx0" << endl;
            /********/ mx0.unlock(); /********/
        ////////////////////////////////////////// Sensor 2 Copy //////////////////////////////////////////
        cout << "run() locking mx1" << endl;
            /********/ mx1.lock(); /********/
        sensor2Deque = rangerArray[1]->getSensorData();
        sensor2MaxDistance = rangerArray[1]->getMaxDistance();
        cout << "run() unlocking mx1" << endl;
            /********/ mx1.unlock(); /********/
        ////////////////////////////////////////// Extrapolate //////////////////////////////////////////
        cout << "Calling extrapolate()" << endl;
        double eSen1 = extrapolate(sensor1Deque, progStartTime, 1);
        if (eSen1 == -1)
        {
            cout << "Could not extrapolate sensor 1 data due to clipped values" << endl;
        }
        double eSen2 = extrapolate(sensor2Deque, progStartTime, 2);
        if (eSen2 == -1)
        {
            cout << "Could not extrapolate sensor 2 data due to clipped values" << endl;
        }
        ////////////////////////////////////////// Fusion //////////////////////////////////////////
        if (fusion == "min")
            minFusion();
        if (fusion == "avg")
            avgFusion();
        if (fusion == "max")
            maxFusion();
//        printData(sensor1Deque);
//        printData(sensor2Deque);
        delay(500);
    }
}

void DataFusion::minFusion()
{

}

void DataFusion::avgFusion()
{

}

void DataFusion::maxFusion()
{

}

double DataFusion::extrapolate(deque<SensorData> sensorDeque, chrono::steady_clock::time_point progStartTime_, int i)
{
    double t0, t1, r0, r1, tNow, eVal;
    deque<SensorData>::iterator it = sensorDeque.begin();
    t0 = it->getTimeStamp();
    r0 = it->getSensorValue();
    it++;
    t1 = it->getTimeStamp();
    r1 = it->getSensorValue();

    if (i == 1)
    {
        if (r0 == sensor1MaxDistance || r1 == sensor1MaxDistance)
        {
            eVal = -1;
            return eVal;
        } else {
            chrono::steady_clock::time_point t = chrono::steady_clock::now();
            chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t - progStartTime_);
            tNow = time_span.count();
            cout << "t0 = " << t0 << ", t1 = " << t1 << ", tNow = " << tNow << endl;
            cout << "r0 = " << r0 << ", r1 = " << r1 << endl;
            eVal = r0 + ((r0 - r1)/(t0 - t1))*(tNow - t0);
            cout << "eVal = " << eVal << endl;
            return eVal;
        }
    }
    else if (i == 2)
    {
        if (r0 == sensor2MaxDistance || r1 == sensor2MaxDistance)
        {
            eVal = -1;
            return eVal;
        } else {
            chrono::steady_clock::time_point t = chrono::steady_clock::now();
            chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t - progStartTime_);
            tNow = time_span.count();
            cout << "t0 = " << t0 << ", t1 = " << t1 << ", tNow = " << tNow << endl;
            cout << "r0 = " << r0 << ", r1 = " << r1 << endl;
            eVal = r0 + ((r0 - r1)/(t0 - t1))*(tNow - t0);
            cout << "eVal = " << eVal << endl;
            return eVal;
        }
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
