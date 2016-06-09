#include "radar.h"
#include <iostream>
#include <cstdio>

#include "generator.h"
#include "sensordata.h"

Radar::Radar()
{
    model = MODEL_;
    baud = baud0_;
    FOV = FOV1_;
    maxDistance = MAX_DISTANCE_;
    minDistance = MIN_DISTANCE_;
    portSet = false;
    dataRate = DATA_RATE_;
    sensorType = "Radar"; /**< Identifies sensor as Radar */
}



