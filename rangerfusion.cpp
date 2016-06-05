#include "rangerfusion.h"
#include <iostream>

using namespace std;

RangerFusion::RangerFusion()
{
}

/*
 * The RangerFusion method relies on the idea that all arrays passed into it have a size of 13. This is all values between 0 and 180 degrees, at 15 degree intervals.
 * Any values that are not populated by their relevant sensor classes are treated as NULL, or 0. Built into RangerFusion is a sweeper that disregards these values
 * from calculations
 */

/*************** TO SEE HOW THE PROGRAM FUNCTIONS, REMOVE COMMENTS FROM COMMENTED OUT CODE LABELLED "DEBUG" BELOW ***************/

void RangerFusion::minFusion(Ranger* rangerArray[3])
{
    // Generate an array for each of the 3 rangers
    for (int i = 0; i < 2; i++)
    {
        rangerArray[i]->genArray();
    }

    for (int i = 0; i < 13; i++)
    {
        /****** PROCESSING VALUES FOR CALCULATING ******/

        int numVals = 0;
        double val1 = 0;
        double val2 = 0;
//        cout << "DEBUG: Radar value [" << i << "] = " << (rangerArray[1]->getArray())[i] << endl;
//        cout << "DEBUG: Sonar value [" << i << "] = " << (rangerArray[2]->getArray())[i] << endl;

        // This section checks that the radar value is not zero or clipped, and if not, saves it as a value for calculations
        if (((rangerArray[0]->getArray())[i]) /* If it's not null */ && !(rangerArray[0]->disregard((rangerArray[0]->getArray())[i]))) // And if it's not disregarded as min or max
        {
            val1 = (rangerArray[0]->getArray())[i];
//            cout << "DEBUG: Laser set to " << (rangerArray[0]->getArray())[i] << endl;
            numVals++;
        }

        // This section checks that the sonar value is not zero or clipped, and if not, saves it as a value for calculations
        if (((rangerArray[1]->getArray())[i]) /* If it's not null */ && !(rangerArray[1]->disregard((rangerArray[1]->getArray())[i]))) // And if it's not disregarded as min or max
        {
            if (numVals == 0)
                val1 = (rangerArray[1]->getArray())[i];
            else if (numVals == 1)
                val2 = (rangerArray[1]->getArray())[i];
//            cout << "DEBUG: Radar set to " << (rangerArray[1]->getArray())[i] << endl;
            numVals++;
        }

        // This section checks that the sonar value is not zero or cliped, and if not, saves it as a value for calculations
//        cout << "DEBUG: val1 = " << val1 << endl;
//        cout << "DEBUG: val2 = " << val2 << endl;
//        cout << "DEBUG: val3 = " << val3 << endl;
//        cout << "DEBUG: numVals = " << numVals << endl;

        /****** USING PROCESSED VALUES TO CALCULATE MINIMUM ******/

        if (numVals == 0)
            fusedArray[i] = 0;
        if (numVals == 1)
            fusedArray[i] = val1;
        if (numVals == 2)
            if (val1 > val2)
                fusedArray[i] = val2;
            else
                fusedArray[i] = val1;
//        cout << "DEBUG: min set to: " << fusedArray[i] << endl;
//        cout << endl;
    }
}

void RangerFusion::avgFusion(Ranger* rangerArray[3])
{
    // Generate an array of each of the 3 rangers
    for (int i = 0; i < 2; i++)
    {
        rangerArray[i]->genArray();
    }

    for (int i = 0; i < 13; i++)
    {
        /****** PROCESSING VALUES FOR CALCULATING ******/

        int numVals = 0;
        double val1 = 0;
        double val2 = 0;
//        cout << "DEBUG: Laser value [" << i << "] = " << (rangerArray[0]->getArray())[i] << endl;
//        cout << "DEBUG: Radar value [" << i << "] = " << (rangerArray[1]->getArray())[i] << endl;
//        cout << "DEBUG: Sonar value [" << i << "] = " << (rangerArray[2]->getArray())[i] << endl;
        if (((rangerArray[0]->getArray())[i]) /* If it's not null */ && !(rangerArray[0]->disregard((rangerArray[0]->getArray())[i]))) // And if it's not disregarded as min or max
        {
            val1 = (rangerArray[0]->getArray())[i];
//            cout << "DEBUG: Laser set to " << (rangerArray[0]->getArray())[i] << endl;
            numVals++;
        }
        if (((rangerArray[1]->getArray())[i]) /* If it's not null */ && !(rangerArray[1]->disregard((rangerArray[1]->getArray())[i]))) // And if it's not disregarded as min or max
        {
            if (numVals == 0)
                val1 = (rangerArray[1]->getArray())[i];
            else if (numVals == 1)
                val2 = (rangerArray[1]->getArray())[i];
//            cout << "DEBUG: Radar set to " << (rangerArray[1]->getArray())[i] << endl;
            numVals++;
        }
//        cout << "DEBUG: val1 = " << val1 << endl;
//        cout << "DEBUG: val2 = " << val2 << endl;
//        cout << "DEBUG: val3 = " << val3 << endl;
//        cout << "DEBUG: numVals = " << numVals << endl;


        /****** USING PROCESSED VALUES TO CALCULATE AVERAGE ******/

        if (numVals == 0)
            fusedArray[i] = 0;
        if (numVals == 1)
            fusedArray[i] = val1;
        if (numVals == 2)
            fusedArray[i] = ((val1 + val2)/2);
//        cout << "DEBUG: mean set to: " << fusedArray[i] << endl;
//        cout << endl;
    }
}

void RangerFusion::maxFusion(Ranger* rangerArray[3])
{
//    cout << "DEBUG: maxFusion called" << endl;
    for (int i = 0; i < 3; i++)
    {
        rangerArray[i]->genArray();
    }

    for (int i = 0; i < 13; i++)
    {

        /****** PROCESSING VALUES FOR CALCULATING ******/

        int numVals = 0;
        double val1 = 0;
        double val2 = 0;
        double val3 = 0;
//        cout << "DEBUG: Laser value [" << i << "] = " << (rangerArray[0]->getArray())[i] << endl;
//        cout << "DEBUG: Radar value [" << i << "] = " << (rangerArray[1]->getArray())[i] << endl;
//        cout << "DEBUG: Sonar value [" << i << "] = " << (rangerArray[2]->getArray())[i] << endl;
        if (((rangerArray[0]->getArray())[i]) /* If it's not null */ && !(rangerArray[0]->disregard((rangerArray[0]->getArray())[i]))) // And if it's not disregarded as min or max
        {
            val1 = (rangerArray[0]->getArray())[i];
//            cout << "DEBUG: Laser set to " << (rangerArray[0]->getArray())[i] << endl;
            numVals++;
        }
        if (((rangerArray[1]->getArray())[i]) /* If it's not null */ && !(rangerArray[1]->disregard((rangerArray[1]->getArray())[i]))) // And if it's not disregarded as min or max
        {
            if (numVals == 0)
                val1 = (rangerArray[1]->getArray())[i];
            else if (numVals == 1)
                val2 = (rangerArray[1]->getArray())[i];
//            cout << "DEBUG: Radar set to " << (rangerArray[1]->getArray())[i] << endl;
            numVals++;
        }
//        cout << "DEBUG: val1 = " << val1 << endl;
//        cout << "DEBUG: val2 = " << val2 << endl;
//        cout << "DEBUG: val3 = " << val3 << endl;
//        cout << "DEBUG: numVals = " << numVals << endl;


        /****** USING PROCESSED VALUES TO CALCULATE AVERAGE ******/

        if (numVals == 0)
            fusedArray[i] = 0;
        if (numVals == 1)
            fusedArray[i] = val1;
        if (numVals == 2)
            if (val1 > val2)
                fusedArray[i] = val1;
            else
                fusedArray[i] = val2;
//        cout << "DEBUG: max set to: " << fusedArray[i] << endl;
//        cout << endl;
    }
}

double* RangerFusion::getArray()
{
    return fusedArray;
}

