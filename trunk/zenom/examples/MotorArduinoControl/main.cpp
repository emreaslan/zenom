
#include "controlbasearduino.h"

/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * MotorArduinoControl
 * -- Description --
 *
 */
class MotorArduinoControl : public ControlBaseArduino
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
    // ----- Log Variables -----
    double Distance;
    double Error;


    // ----- Control Variables -----
    double CriticalProximity;
    double CriticalDistance;

};


int MotorArduinoControl::initialize()
{
    CriticalProximity = 15;
    CriticalDistance = 35;

    registerLogVariable(&Error, "Error");
    registerArduinoLogVariable(&Distance, "Distance");

    registerArduinoControlVariable(&CriticalProximity, "CriticalProximity");
    registerArduinoControlVariable(&CriticalDistance, "CriticalDistance");


    return 0;
}

int MotorArduinoControl::start()
{

    return 0;
}

int MotorArduinoControl::doloop()
{
    if ( Distance < CriticalProximity )
    {
        Error = CriticalProximity - Distance;
    }
    else if ( Distance > CriticalDistance)
    {
        Error = Distance -CriticalDistance;
    }
    else
    {
        Error = 0;
    }

    return 0;
}

int MotorArduinoControl::stop()
{

    return 0;
}

int MotorArduinoControl::terminate()
{

    return 0;
}


int main( int argc, char *argv[] )
{
    MotorArduinoControl c;
    c.run( argc, argv );

    return 0;
}

