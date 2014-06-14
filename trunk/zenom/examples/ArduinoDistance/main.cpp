
#include <controlbasearduino.h>


/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * ArduinoDistance
 * This example simulates a bouncing ball from floor.
 *
 */
class ArduinoDistance : public ControlBaseArduino
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

    double Distance;
    double Check;
    double controlVar;
};


int ArduinoDistance::initialize()
{
    controlVar = -1;

    registerArduinoLogVariable(&Distance, "Distance");
    registerArduinoLogVariable(&Check, "Check");
    registerArduinoControlVariable(&controlVar, "controlVar", CONTROL_VARIABLE);
    return 0;
}

int ArduinoDistance::start()
{
    return 0;
}

int ArduinoDistance::doloop()
{
    /* Your Code Here*/
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

