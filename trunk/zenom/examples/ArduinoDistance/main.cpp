
#include <controlbase.h>
#include <zenomarduinomanager.h>


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

    double Distance;
    ZenomArduinoManager mArduinoManager;

};


int ArduinoDistance::initialize()
{
    mArduinoManager.initArduino(this);
    mArduinoManager.registerArduinoLogVariable(&Distance, "Distance");

    mArduinoManager.start();
    return 0;
}

int ArduinoDistance::start()
{
    return 0;
}

int ArduinoDistance::doloop()
{
    mArduinoManager.doLoopPreProcess();

    /* Your Code Here*/

    mArduinoManager.doLoopPostProcess();
    return 0;
}

int ArduinoDistance::stop()
{
    return 0;
}

int ArduinoDistance::terminate()
{
    mArduinoManager.stop();
    return 0;
}


int main( int argc, char *argv[] )
{
    ArduinoDistance c;
    c.run( argc, argv );

    return 0;
}

