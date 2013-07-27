


#include <sys/mman.h>
#include <fltk/run.h>
#include "zenom.h"

using namespace fltk;

void timeout_callback(void* v)
{
    Zenom* sw = (Zenom*)v;
    sw->redraw();
    fltk::redraw();
   
    fltk::repeat_timeout(1.0/20,timeout_callback,v);
}


int main( int argc, char *argv[] )
{
    argc = argc;
    argv = argv;
    mlockall(MCL_CURRENT|MCL_FUTURE);
    
    Zenom zenom(400,310,"Zenom");
    zenom.size_range(400,310,400,800);
    
    zenom.show();
    add_timeout(1.0/20,timeout_callback,&zenom);
/*

    
    double variable;
    LogVariable logvar(variable,"variable","Example",5,2);   
    WatchWindow watchWindow( &logvar ); */

    
    return run();
}
