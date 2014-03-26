
#include <controlbase.h>


/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * ArduinoDistance
 * This example simulates a bouncing ball from floor.
 *
 */
class ArduinoDistance : public ControlBase
{
public:

    /**
     * Initializes and registers the log variables and control variables.
     * @return
     */
    virtual int initialize();

    /**
     *
     * @return
     */
    virtual int start();

    /**
     *
     * @return
     */
    virtual int doloop();

    /**
     *
     * @return
     */
    virtual int stop();

    /**
     *
     * @return
     */
    virtual int terminate();

private:

};


int ArduinoDistance::initialize()
{
    initArduino("ino/ArduinoDistance.ino");

    return 0;
}

int ArduinoDistance::start()
{

    return 0;
}

int ArduinoDistance::doloop()
{
    return 0;
}

int ArduinoDistance::stop()
{

    return 0;
}

int ArduinoDistance::terminate()
{

    return 0;
}


int main( int argc, char *argv[] )
{
    ArduinoDistance c;
    c.run( argc, argv );

    return 0;
}

