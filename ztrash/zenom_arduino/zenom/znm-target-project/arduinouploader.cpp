#include "arduinouploader.h"
#include <string>
#include <stdio.h>
#include <cstdlib>


#define ARDUINO_UPLOAD_PARAMETER (std::string("--uploadarduinoproject"))

ArduinoUploader::ArduinoUploader()
{
}


bool ArduinoUploader::checkParameters(int argc, char *argv[])
{
    if ( argc != 2 || (std::string(argv[1]) != ARDUINO_UPLOAD_PARAMETER) )
    {
        return false;
    }
    return true;
}

bool ArduinoUploader::processParameters(int argc, char *argv[])
{
    if (std::string(argv[1]) == ARDUINO_UPLOAD_PARAMETER )
    {
        return uploadToArduino();
    }
}

void ArduinoUploader::printUsage()
{
    printf("usage: znm-target-project --uploadarduinoproject  : uploads Arduino file (Run in .ino folder).\n");
}

bool ArduinoUploader::uploadToArduino()
{
    int status = system("ino upload -d /usr/share/arduino");
    if (status == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

