#include <iostream>
#include "cppparser.h"

using namespace std;

int main()
{
    CppParser cppParser;
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


    return 0;
}

