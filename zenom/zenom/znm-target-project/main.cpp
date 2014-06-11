#include <iostream>
#include "targetprojectmanager.h"
#include <cstdlib>

using namespace std;


int main(int argc, char *argv[])
{
    TargetProjectManager targetProjectManager;

    if ( !targetProjectManager.processParameters(argc, argv))
    {
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    return 0;
}

