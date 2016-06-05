#include "sonar.h"
#include <iostream>
#include <cstdio>
#include "generator.h"

Sonar::Sonar()
{
    model = MODEL_;
    baud = baud0_;
    portNumber = port0_;
    portDir = PORT_STRING_;
    FOV = FOV_;
    maxDistance = MAX_DISTANCE_;
    minDistance = MIN_DISTANCE_;
    portSet = false;
    dataRate = DATA_RATE_;
}

// GET Methods

string Sonar::getModel()
{
    return model;
}

string Sonar::getPortDir()
{
    return portDir;
}

int Sonar::getPortNumber()
{
    return portNumber;
}

double Sonar::getMaxDistance()
{
    return maxDistance;
}

double Sonar::getMinDistance()
{
    return minDistance;
}

int Sonar::getFOV()
{
    return FOV;
}

int Sonar::getBaud()
{
    return baud;
}

double Sonar::getAngularResolution()
{
    return -1.0;
}

double* Sonar::getArray()
{
    return scanValues;
}

int Sonar::getSensorType()
{
    return sensorType;
}


// SET Methods

int Sonar::setPORT(int input)
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


int Sonar::setBaud(int input)
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

int Sonar::setFOV(int)
{
    return -1;
}

int Sonar::setAngularResolution(int)
{
    return -1;
}

// Other Methods

void Sonar::genArray()
{
    Generator myGen;
    double mean = 6.0;
    double stdDev = 5.0;
    double genVal = myGen.normalGenerator(mean,stdDev,maxDistance);
    for (int i = 0; i < 13; i++)
    {

        if ((i > 2) && (i < 10))
        {
            scanValues[i] = genVal;
        }
        else
        {
            scanValues[i] = NULL;
        }
    }
}

bool Sonar::disregard(double check) // checks if the value is clipped, and therefore should be disregarded
{
    if ((check == maxDistance) || (check == minDistance))
    {
        return true;
    }
    else return false;
}
