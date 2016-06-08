#include "ranger.h"

Ranger::Ranger()
{
    baud = baud0_;
    portNumber = port0_;
    portSet = false;
    portDir = PORT_STRING_;

}

int Ranger::getBaud()
{
    return baud;
}
int Ranger::getPortNumber()
{
    return portNumber;
}
string Ranger::getPortDir()
{
    return portDir;
}


int Ranger::setBaud(int input)
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
int Ranger::setPORT(int input)
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
