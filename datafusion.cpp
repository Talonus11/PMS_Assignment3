#include "datafusion.h"
#include "ranger.h"

DataFusion::DataFusion()
{
}

void DataFusion::run(Ranger* rangerArray[2], mutex &mx0, mutex &mx1, chrono::_V2::steady_clock::time_point progStartTime, string fusion, condition_variable &cv, condition_variable &cv2, int &newData1, int &newData2)
{
    while(true)
    {
        cout << "newData1 = " << newData1 << endl;
        cout << "newData2 = " << newData2 << endl;
        if (newData1 == 2)
        {
            /********/ mx0.lock(); /********/
            sensor1Deque = rangerArray[0]->getSensorData();
            sensor1MaxDistance = rangerArray[0]->getMaxDistance();
            /********/ mx0.unlock(); /********/
        }
        else
        {
            unique_lock<mutex> lck(mx0);
            if (newData1 == 1) // true if newData = 1
            {
                cv.wait(lck);
            }
            sensor1Deque = rangerArray[0]->getSensorData();
            sensor1MaxDistance = rangerArray[0]->getMaxDistance();
            newData1 = 0;
        }

        if (newData2 == 2)
        {
            /********/ mx1.lock(); /********/
            sensor2Deque = rangerArray[1]->getSensorData();
            sensor2MaxDistance = rangerArray[1]->getMaxDistance();
            /********/ mx1.unlock(); /********/
        }
        else
        {
            unique_lock<mutex> lck2(mx1);
            if (newData2 == 1) // true if newData2 = 1
            {
                cv2.wait(lck2);
            }
            sensor2Deque = rangerArray[1]->getSensorData();
            sensor2MaxDistance = rangerArray[1]->getMaxDistance();
            newData2 = 0;
        }

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
        cout << "eSen1 = " << eSen1 << ", eSen2 = " << eSen2 << endl;
        if ((eSen1 == -1) && (eSen2 == -1))
        {
            cout << "Could not produce a reliable fused result due to clipped values" << endl;

        }
        else
        {
            if (fusion == "min")
                cout << "Minimum value: " << minFusion(eSen1, eSen2) << endl;
            if (fusion == "avg")
                cout << "Average value: " << avgFusion(eSen1, eSen2) << endl;
            if (fusion == "max")
                cout << "Maximum value: " << maxFusion(eSen1, eSen2) << endl;
        }
//        delay(200);
        cout << endl;
    }
}

double DataFusion::minFusion(double e1, double e2)
{
    if (e1 == -1)
    {
        cout << "Sensor 1 extrapolated value unreliable." << endl;
        return e2;
    }
    else if (e2 == -1)
    {
        cout << "Sensor 2 extrapolated value unreliable." << endl;
        return e1;
    }
    else if (e1 > e2)
        return e2;
    else if (e2 > e1)
        return e1;
    else return e1;
}

double DataFusion::avgFusion(double e1, double e2)
{
    if (e1 == -1)
    {
        cout << "Sensor 1 extrapolated value unreliable." << endl;
        return e2;
    }
    else if (e2 == -1)
    {
        cout << "Sensor 2 extrapolated value unreliable." << endl;
        return e1;
    }
    else
    {
        double avg = (e1 + e2)/2;
        return avg;
    }
}

double DataFusion::maxFusion(double e1, double e2)
{
    if (e1 == -1)
    {
        cout << "Sensor 1 extrapolated value unreliable." << endl;
        return e2;
    }
    else if (e2 == -1)
    {
        cout << "Sensor 2 extrapolated value unreliable." << endl;
        return e1;
    }
    if (e1 > e2)
        return e1;
    else if (e2 > e1)
        return e2;
    else return e1;
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
//            cout << "t0 = " << t0 << ", t1 = " << t1 << ", tNow = " << tNow << endl;
//            cout << "r0 = " << r0 << ", r1 = " << r1 << endl;
            eVal = r0 + ((r0 - r1)/(t0 - t1))*(tNow - t0);
//            cout << "eVal = " << eVal << endl;
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
