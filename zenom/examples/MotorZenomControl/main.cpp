
#include "controlbasearduino.h"

/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * MotorZenomControl
 * -- Description --
 *
 */
class MotorZenomControl : public ControlBaseArduino
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
    double MotorDirection;
    double CriticalProximity;
    double CriticalDistance;

};


int MotorZenomControl::initialize()
{
    MotorDirection = 0;
    CriticalProximity = 15;
    CriticalDistance = 35;

    registerLogVariable(&Error, "Error");

    registerArduinoLogVariable(&Distance, "Distance");

    registerArduinoControlVariable(&MotorDirection, "MotorDirection", LOG_VARIABLE);

    registerControlVariable(&CriticalProximity, "CriticalProximity");
    registerControlVariable(&CriticalDistance, "CriticalDistance");

    return 0;
}

int MotorZenomControl::start()
{

    return 0;
}

int MotorZenomControl::doloop()
{
    if ( Distance < CriticalProximity )
    {
        MotorDirection = 1;
        Error = CriticalProximity - Distance;
    }
    else if ( Distance > CriticalDistance)
    {
        MotorDirection = 2;
        Error = Distance -CriticalDistance;
    }
    else
    {
        MotorDirection = 0;
        Error = 0;
    }

    return 0;
}

int MotorZenomControl::stop()
{

    return 0;
}

int MotorZenomControl::terminate()
{

    return 0;
}


int main( int argc, char *argv[] )
{
    MotorZenomControl c;
    c.run( argc, argv );

    return 0;
}

