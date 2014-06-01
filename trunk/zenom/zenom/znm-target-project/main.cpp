#include <iostream>
#include "targetprojectmanager.h"
#include <cstdlib>

using namespace std;


int main(int argc, char *argv[])
{
    TargetProjectManager targetProjectManager;

    if ( !targetProjectManager.checkParameters(argc, argv))
    {
        targetProjectManager.printUsage();
        exit(1);  /* exit status of the program : non-zero for errors */
    }


    /*
    cppParser.parseFile("/home/zenom/Desktop/zenom/examples/ArduinoDistance/main.cpp");

    std::cout << "Printing Log Vars" << std::endl;
    for (int i = 0; i < cppParser.logVariables().size(); ++i)
    {
        std::cout << "Variable : " << cppParser.logVariables()[i].toStdString() << std::endl;
    }

    std::cout << std::endl << "Printing Control Vars" << std::endl;
    for (int i = 0; i < cppParser.controlVariables().size(); ++i)
    {
        std::cout << "Variable : " << cppParser.controlVariables()[i].toStdString() << std::endl;
    }
    */

    return 0;
}

