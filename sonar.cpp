#include "sonar.h"
#include <iostream>
#include <cstdio>
#include "generator.h"

Sonar::Sonar()
{
    model = MODEL_;
    baud = baud0_;
    portDir = PORT_STRING_;
    FOV = FOV_;
    maxDistance = MAX_DISTANCE_;
    minDistance = MIN_DISTANCE_;
    portSet = false;
    dataRate = DATA_RATE_;
    sensorType = "Sonar";
    dataRate_ms = 1000/dataRate;
}
