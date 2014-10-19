


#include <sys/mman.h>
#include "zenom.h"


int main( int argc, char *argv[] )
{
    argc = argc;
    argv = argv;
    mlockall(MCL_CURRENT|MCL_FUTURE);
    
    Zenom zenom;
    zenom.show();

    return fltk::run();
}
