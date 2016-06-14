/* Assignment 2
 * Chris Schiller 11377773
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <array>
#include <thread>
#include <vector>
#include <condition_variable>

#include "generator.h"
#include "radar.h"
#include "ranger.h"
#include "sonar.h"
#include "datafusion.h"

using namespace std;

void th1Func(Ranger* ranger0, chrono::steady_clock::time_point progStartTime, mutex &mx0, condition_variable &cv_, int &newData_)
{
    ranger0->genData0(progStartTime, mx0, cv_, newData_);
}

void th2Func(Ranger* ranger1, chrono::steady_clock::time_point progStartTime, mutex &mx1, condition_variable &cv2_, int &newData2_)
{
    ranger1->genData1(progStartTime, mx1, cv2_, newData2_);
}

void thFusionFunc(DataFusion &fuser, Ranger* rangerArray[2], mutex &mx0, mutex &mx1, chrono::steady_clock::time_point progStartTime, string fuseType_, condition_variable &cv_, condition_variable &cv2_, int &newData_, int &newData2_)
{
    fuser.run(rangerArray, mx0, mx1, progStartTime, fuseType_, cv_, cv2_, newData_, newData2_);
}

bool port0Taken = false;
bool port1Taken = false;
bool port2Taken = false;

/*
 *  nextPort method returns the number (int) of the next free port. eg. if port 0 is taken, it will return 1; if port 1 and 2 are taken, will return 0
 */

int nextPort()
{
    if (port0Taken)
    {
        if (port1Taken)
        {
            return 2;
        }
        else return 1;
    }
    else return 0;
}

/*
 *  portTaken method takes an input between 0 and 2 and sets the relevant portTaken variable to true
 */

void portTaken(int input)
{
    switch (input)
    {
        case 0:
            port0Taken = true;
            break;
        case 1:
            port1Taken = true;
            break;
        case 2:
            port2Taken = true;
            break;
    }
}

void sensorSetup(Ranger &rdr1, Ranger &snr1, Ranger* rangerArray[2], string &fuseType);

void fusionRun();

int main( int argc, char ** argv )
{
    chrono::steady_clock::time_point programStartTime = chrono::steady_clock::now();
    Radar radar1;
    Sonar sonar1;
    Ranger* rangerArray[2];
    mutex mx0_;
    mutex mx1_;
    condition_variable cv;
    condition_variable cv2;
    int newData = 0;
    int newData2 = 2;
    DataFusion fuser_;
    string fuseType;
    sensorSetup(radar1, sonar1, rangerArray, fuseType);
//    Ranger **radar; //placeholder for sorting which ranger to pass into threads
//    Ranger **sonar; //placeholder for sorting which ranger to pass into threads


    std::thread th2(th2Func,ref(rangerArray[1]),ref(programStartTime),ref(mx1_), ref(cv), ref(newData2));
    std::thread th1(th1Func,ref(rangerArray[0]),ref(programStartTime),ref(mx0_), ref(cv2), ref(newData));
    std::thread thFusion(thFusionFunc, ref(fuser_) ,ref(rangerArray), ref(mx0_), ref(mx1_), ref(programStartTime), fuseType, ref(cv), ref(cv2), ref(newData), ref(newData2));
    th1.join();
    th2.join();
    thFusion.join();

    return 0;
}

void fusionRun()
{
//    int uinput;
//    RangerFusion fusion;
//    cout << "Choose fusion method (min = 0, avg = 1, max = 2): " << endl;
//    cin >> uinput;

//    double outputArray[10000][13]; // Creates a 2 dimensional array. The first value (column) will be used to store up to 10,000 arrays of values. The second is the array of values generated by fusion
//    int y = 0; //The counter for sequence, and mover between arrays


//    if (uinput == 0) // Minimum
//    {
//        while(1)
//        {
//            cout << "Minimum Values" << endl;
//            fusion.minFusion(rangerArray);
//            for (int i = 0; i < 13; i++)
//            {
//                outputArray[y][i] = (fusion.getArray())[i]; // Populates the output Array with all 13 values from fusion
//                cout << "Sequence #[" << y <<"]:["<< i*15 << "] = " << outputArray[y][i] << endl;
//            }
//            cout << endl;
//            y++;
//            delay(1000);
//        }
//    }

//    if (uinput == 1) // Average
//    {
//        while(1)
//        {
//            cout << "Average Values" << endl;
//            fusion.avgFusion(rangerArray);
//            for (int i = 0; i < 13; i++)
//            {
//                outputArray[y][i] = (fusion.getArray())[i]; // Populates the output Array with all 13 values from fusion
//                cout << "Sequence #[" << y <<"]:["<< i*15 << "] = " << outputArray[y][i] << endl;
//            }
//            cout << endl;
//            y++;
//            delay(1000);
//        }
//    }

//    if (uinput == 2) // Maximum
//    {
//        while(1)
//        {
//            cout << "Maximum Values" << endl;
//            fusion.maxFusion(rangerArray);
//            for (int i = 0; i < 13; i++)
//            {
//                outputArray[y][i] = (fusion.getArray())[i]; // Populates the output Array with all 13 values from fusion
//                cout << "Sequence #[" << y <<"]:["<< i*15 << "] = " << outputArray[y][i] << endl;
//            }
//            cout << endl;
//            y++;
//            delay(1000);
//        }
//    }
}

void sensorSetup(Ranger &rdr1, Ranger &snr1, Ranger *rangerArray[], string &fuseType)
{
    int uinput; // user input for ints

    cout << "Rangers created" << endl;

    rangerArray[0] = &rdr1;
    rangerArray[1] = &snr1;

    //////////////////////////////////////////////
    /******* SENSOR 0 FIXED PARAMETERS PRINT *******/
    //////////////////////////////////////////////

    cout << "*****" << rangerArray[0]->getSensorType() << "*****" << endl;
    cout << "Fixed Parameters" << endl;
    cout << "Model: " << rangerArray[0]->getModel() << endl;
    cout << "Scan range: " << rangerArray[0]->getMinDistance() << "m - " << rangerArray[0]->getMaxDistance() << "m" << endl << endl;


    //////////////////////////////////////////
    /******* SENSOR 0 SETTING PARAMETERS *******/
    //////////////////////////////////////////

    cout << "Setting non-fixed parameters" << endl;


    /**** PORT SET ****/

    cout << "Default Port: " << rangerArray[0]->getPortDir() << endl;
    cout << "Set Port Number (0,1,2) " << rangerArray[0]->getPortDir();
    cin >> uinput;

    if (uinput != rangerArray[0]->getPortNumber()) // checks if the port entered clashes with the laser sensor port
    {
        // Does not clash with laser
        if (rangerArray[0]->setPORT(uinput) == 0) // checks setPort method was successful (returns 1)
        {
            cout << "Unable to set port - incorrect value entered. Choosing next available port." << endl;
            if (rangerArray[0]->setPORT(nextPort()) == 1) // gets next free port, sends it to be set, then checks it was successful
            {
                cout << "Port set to: " << rangerArray[0]->getPortNumber() << endl;
                portTaken(nextPort()); // sets portTaken to true for port that has been set
            }

        }
        else // success
        {
            cout << "Port set to: " << rangerArray[0]->getPortNumber() << endl;
            portTaken(uinput); // sets portTaken to true for port that has been set
        }
    }
    else // clashes
    {
        cout << "Port unavailable. Choosing next available port. " << endl;
        if (rangerArray[0]->setPORT(nextPort()) == 1) // gets next free port, sends it to be set, then checks it was successful
        {
            cout << "Port set to: " << rangerArray[0]->getPortNumber() << endl;
            portTaken(nextPort()); // sets portTaken to true for port that has been set
        }
    }


    /**** BAUD SET ****/

    cout << "Default Baud: " << rangerArray[0]->getBaud() << endl;
    cout << "Set Baud (38400 or 115200): ";
    cin >> uinput;

    if (rangerArray[0]->setBaud(uinput) == 0) // checks setBaud method was successful (returns 1)
    {
        cout << "Unable to set Baud - incorrect value entered. Reverting to default: " << rangerArray[0]->getBaud() << endl;
    }
    cout << "Baud set to: " << rangerArray[0]->getBaud() << endl << endl;


    /**** FOV SET ****/
    if (rangerArray[0]->getSensorType() == "Radar")
    {
        cout << "Default FOV: " << rangerArray[0]->getFOV() << endl;
        cout << "Set FOV (20 or 40) degrees: ";
        cin >> uinput;

        if (rangerArray[0]->setFOV(uinput) == 0) // checks setPort method was successful (returns 1)
        {
            cout << "Unable to set FOV - incorrect value entered. Reverting to default: " << rangerArray[0]->getFOV() << endl;
        }
        cout << "FOV set to: " << rangerArray[0]->getFOV() << endl << endl;
    }


    /**** SENSOR 0 ALL PARAMETERS PRINT ****/

    cout << "----- FINAL SET VALUES -----" << endl;
    cout << "Model: " << rangerArray[0]->getModel() << endl;
    cout << "Baud: " << rangerArray[0]->getBaud() << endl;
    cout << "Port: " << rangerArray[0]->getPortDir() << rangerArray[0]->getPortNumber() << endl;
    cout << "FOV: " << rangerArray[0]->getFOV() << endl;
    cout << "Min Distance: " << rangerArray[0]->getMinDistance() << endl;
    cout << "Max Distance: " << rangerArray[0]->getMaxDistance() << endl;
    cout << endl;


    //////////////////////////////////////////////
    /******* SENSOR 1 FIXED PARAMETERS PRINT *******/
    //////////////////////////////////////////////

    cout << "*****" << rangerArray[1]->getSensorType() << "*****" << endl;
    cout << "Fixed Parameters" << endl;
    cout << "Model: " << rangerArray[1]->getModel() << endl;
    cout << "Scan range: " << rangerArray[1]->getMinDistance() << "m - " << rangerArray[1]->getMaxDistance() << "m" << endl << endl;


    //////////////////////////////////////////
    /******* SENSOR 1 SETTING PARAMETERS *******/
    //////////////////////////////////////////

    cout << "Setting non-fixed parameters" << endl;


    /**** PORT SET ****/

    cout << "Default Port: " << rangerArray[1]->getPortDir() << endl;
    cout << "Set Port Number (0,1,2) " << rangerArray[1]->getPortDir();
    cin >> uinput;

    if (uinput != rangerArray[0]->getPortNumber()) // checks if the port entered clashes with the Sensor 0 port
    {
        // Does not clash with Sensor 0
        if (rangerArray[1]->setPORT(uinput) == 0) // checks setPort method was successful (returns 1)
        {
            cout << "Unable to set port - incorrect value entered. Choosing next available port." << endl;
            if (rangerArray[1]->setPORT(nextPort()) == 1) // gets next free port, sends it to be set, then checks it was successful
            {
                cout << "Port set to: " << rangerArray[1]->getPortNumber() << endl;
                portTaken(nextPort()); // sets portTaken to true for port that has been set
            }

        }
        else // success
        {
            cout << "Port set to: " << rangerArray[1]->getPortNumber() << endl;
            portTaken(uinput); // sets portTaken to true for port that has been set
        }
    }
    else // clashes
    {
        cout << "Port unavailable. Choosing next available port. " << endl;
        if (rangerArray[1]->setPORT(nextPort()) == 1) // gets next free port, sends it to be set, then checks it was successful
        {
            cout << "Port set to: " << rangerArray[1]->getPortNumber() << endl;
            portTaken(nextPort()); // sets portTaken to true for port that has been set
        }
    }


    /**** BAUD SET ****/

    cout << "Default Baud: " << rangerArray[1]->getBaud() << endl;
    cout << "Set Baud (38400 or 115200): ";
    cin >> uinput;

    if (rangerArray[1]->setBaud(uinput) == 0) // checks setBaud method was successful (returns 1)
    {
        cout << "Unable to set Baud - incorrect value entered. Reverting to default: " << rangerArray[1]->getBaud() << endl;
    }
    cout << "Baud set to: " << rangerArray[1]->getBaud() << endl << endl;

    /**** FOV SET ****/
    if (rangerArray[1]->getSensorType() == "Radar")
    {
        cout << "Default FOV: " << rangerArray[1]->getFOV() << endl;
        cout << "Set FOV (20 or 40) degrees: ";
        cin >> uinput;

        if (rangerArray[1]->setFOV(uinput) == 0) // checks setPort method was successful (returns 1)
        {
            cout << "Unable to set FOV - incorrect value entered. Reverting to default: " << rangerArray[0]->getFOV() << endl;
        }
        cout << "FOV set to: " << rangerArray[1]->getFOV() << endl << endl;
    }

    /**** SENSOR 0 ALL PARAMETERS PRINT ****/

    cout << "-----" << rangerArray[0]->getSensorType() << " FINAL SET VALUES -----" << endl;
    cout << "Model: " << rangerArray[0]->getModel() << endl;
    cout << "Baud: " << rangerArray[0]->getBaud() << endl;
    cout << "Port: " << rangerArray[0]->getPortDir() << rangerArray[0]->getPortNumber() << endl;
    cout << "FOV: " << rangerArray[0]->getFOV() << endl;
    cout << "Min Distance: " << rangerArray[0]->getMinDistance() << endl;
    cout << "Max Distance: " << rangerArray[0]->getMaxDistance() << endl;
    cout << endl;

    /**** SENSOR 1 ALL PARAMETERS PRINT ****/

    cout << "-----" << rangerArray[1]->getSensorType() << " FINAL SET VALUES -----" << endl;
    cout << "Model: " << rangerArray[1]->getModel() << endl;
    cout << "Baud: " << rangerArray[1]->getBaud() << endl;
    cout << "Port: " << rangerArray[1]->getPortDir() << rangerArray[1]->getPortNumber() << endl;
    cout << "FOV: " << rangerArray[1]->getFOV() << endl;
    cout << "Min Distance: " << rangerArray[1]->getMinDistance() << endl;
    cout << "Max Distance: " << rangerArray[1]->getMaxDistance() << endl;
    cout << endl;

    cout << "What kind of fusion would you like to perform? Enter 1 for Min, 2 for Avg, 3 for Max: ";
    cin >> uinput;
    if (uinput == 1)
        fuseType = "min";
    if (uinput == 2)
        fuseType = "avg";
    if (uinput == 3)
        fuseType = "max";
}
