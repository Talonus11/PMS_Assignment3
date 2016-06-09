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

#include "generator.h"
#include "radar.h"
#include "ranger.h"
#include "sonar.h"
#include "rangerfusion.h"

using namespace std;

//// This if statement determines if the program is being run in windows or linux, and sets "delay()" to refer to the correct platform method for delaying code

//#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

//  #include <windows.h>

//inline void delay( unsigned long ms )
//{
//    std::chrono::milliseconds duration(ms);
//    std::this_thread::sleep_for(duration);
//}

void th1Function(Ranger* rangerArray[2], chrono::steady_clock::time_point progStartTime)
{
    rangerArray[0]->genData(progStartTime);
}

//#else  /* presume POSIX */

//  #include <unistd.h>

//  inline void delay( unsigned long ms )
//    {
//        usleep( ms * 1000 );
//    }

//#endif

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

void sensorSetup(Ranger &rdr1, Ranger &snr1, Ranger* rangerArray[2])
{
    int uinput; // user input for ints

    cout << "Rangers created" << endl;


    Ranger* tempArray[2]; // stores one of each type of sensor in an array. Note that they can be reordered any way desired
    tempArray[0] = &rdr1;
    tempArray[1] = &snr1;


    cout << "Ranger Array created" << endl;


//     Sort array so that:
//     laser (sensorType = 0) is slot 0
//     radar (sensorType = 1) is slot 1
//     sonar (sensorType = 2) is slot 2
//     NB: This code still assumes that there is only one of each sensor type

    for (int i = 0; i < 2; i++)
    {
        if ((tempArray[i]->getSensorType()) == "Radar")
            rangerArray[0] = tempArray[i];
        if ((tempArray[i]->getSensorType()) == "Sonar")
            rangerArray[1] = tempArray[i];
    }

    //////////////////////////////////////////////
    /******* RADAR FIXED PARAMETERS PRINT *******/
    //////////////////////////////////////////////

    cout << "*****RADAR*****" << endl;
    cout << "Fixed Parameters" << endl;
    cout << "Model: " << rangerArray[0]->getModel() << endl;
    cout << "Scan range: " << rangerArray[0]->getMinDistance() << "m - " << rangerArray[0]->getMaxDistance() << "m" << endl << endl;


    //////////////////////////////////////////
    /******* RADAR SETTING PARAMETERS *******/
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

    cout << "Default FOV: " << rangerArray[0]->getFOV() << endl;
    cout << "Set FOV (20 or 40) degrees: ";
    cin >> uinput;

    if (rangerArray[0]->setFOV(uinput) == 0) // checks setPort method was successful (returns 1)
    {
        cout << "Unable to set FOV - incorrect value entered. Reverting to default: " << rangerArray[0]->getFOV() << endl;
    }
    cout << "FOV set to: " << rangerArray[0]->getFOV() << endl << endl;


    /**** RADAR ALL PARAMETERS PRINT ****/

    cout << "----- FINAL SET VALUES -----" << endl;
    cout << "Model: " << rangerArray[0]->getModel() << endl;
    cout << "Baud: " << rangerArray[0]->getBaud() << endl;
    cout << "Port: " << rangerArray[0]->getPortDir() << rangerArray[0]->getPortNumber() << endl;
    cout << "FOV: " << rangerArray[0]->getFOV() << endl;
    cout << "Min Distance: " << rangerArray[0]->getMinDistance() << endl;
    cout << "Max Distance: " << rangerArray[0]->getMaxDistance() << endl;
    cout << endl;


    //////////////////////////////////////////////
    /******* SONAR FIXED PARAMETERS PRINT *******/
    //////////////////////////////////////////////

    cout << "*****SONAR*****" << endl;
    cout << "Fixed Parameters" << endl;
    cout << "Model: " << rangerArray[1]->getModel() << endl;
    cout << "Scan range: " << rangerArray[1]->getMinDistance() << "m - " << rangerArray[1]->getMaxDistance() << "m" << endl << endl;


    //////////////////////////////////////////
    /******* SONAR SETTING PARAMETERS *******/
    //////////////////////////////////////////

    cout << "Setting non-fixed parameters" << endl;


    /**** PORT SET ****/

    cout << "Default Port: " << rangerArray[1]->getPortDir() << endl;
    cout << "Set Port Number (0,1,2) " << rangerArray[1]->getPortDir();
    cin >> uinput;

    if (uinput != rangerArray[0]->getPortNumber()) // checks if the port entered clashes with the radar port
    {
        // Does not clash with radar
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

    /**** RADAR ALL PARAMETERS PRINT ****/

    cout << "----- RADAR FINAL SET VALUES -----" << endl;
    cout << "Model: " << rangerArray[0]->getModel() << endl;
    cout << "Baud: " << rangerArray[0]->getBaud() << endl;
    cout << "Port: " << rangerArray[0]->getPortDir() << rangerArray[0]->getPortNumber() << endl;
    cout << "FOV: " << rangerArray[0]->getFOV() << endl;
    cout << "Min Distance: " << rangerArray[0]->getMinDistance() << endl;
    cout << "Max Distance: " << rangerArray[0]->getMaxDistance() << endl;
    cout << endl;

    /**** SONAR ALL PARAMETERS PRINT ****/

    cout << "----- SONAR FINAL SET VALUES -----" << endl;
    cout << "Model: " << rangerArray[1]->getModel() << endl;
    cout << "Baud: " << rangerArray[1]->getBaud() << endl;
    cout << "Port: " << rangerArray[1]->getPortDir() << rangerArray[1]->getPortNumber() << endl;
    cout << "FOV: " << rangerArray[1]->getFOV() << endl;
    cout << "Min Distance: " << rangerArray[1]->getMinDistance() << endl;
    cout << "Max Distance: " << rangerArray[1]->getMaxDistance() << endl;
    cout << endl;
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

int main( int argc, char ** argv )
{
    chrono::steady_clock::time_point programStartTime = chrono::steady_clock::now();
    Radar radar1;
    Sonar sonar1;
    Ranger* rangerArray[2];
    sensorSetup(radar1, sonar1, rangerArray);

    std::thread thSensor1(th1Function, ref(rangerArray), ref(programStartTime));
    thSensor1.join();



//    cout << rangerArray[1]->getPortNumber() << endl;

//    cout << "Program started" << endl;
//    Generator gen;
//    std::chrono::milliseconds duration(100);

///*
// * Code to generate range values for testing
// */

////    for (int i = 0; i < 10000; i++)
////    {
////        double generated;
////        generated = gen.rangeGenerator(programStartTime);
////        cout << generated << endl;
////    }

//    vector<Ranger> rangerVector;
//    Radar radar1;
////    radar1.initSensorData(100);
//    radar1.genData(programStartTime);
//    radar1.printData();



    return 0;
}

