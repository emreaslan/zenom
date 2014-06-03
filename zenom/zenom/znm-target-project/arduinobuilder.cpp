#include "arduinobuilder.h"
#include <string>
#include <stdio.h>
#include <cstdlib>

#define ARDUINO_BUILD_PARAMETER (std::string("--buildarduinoproject"))

ArduinoBuilder::ArduinoBuilder()
{
}


bool ArduinoBuilder::checkParameters(int argc, char *argv[])
{
    if ( argc != 2 || (std::string(argv[1]) != ARDUINO_BUILD_PARAMETER) )
    {
        return false;
    }
    return true;
}

bool ArduinoBuilder::processParameters(int argc, char *argv[])
{
    if (std::string(argv[1]) == ARDUINO_BUILD_PARAMETER )
    {
        return buildArduinoFile();
    }
}

void ArduinoBuilder::printUsage()
{
    printf("usage: znm-target-project --buildarduinoproject  : builds Arduino file (Run in .ino folder).\n");
}

bool ArduinoBuilder::buildArduinoFile()
{
    int status = system("ino build -d /usr/share/arduino");
    if (status == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
