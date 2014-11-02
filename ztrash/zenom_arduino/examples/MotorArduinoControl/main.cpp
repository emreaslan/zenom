
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
    double TotalError;
    double AverageError;


    // ----- Control Variables -----
    double CriticalProximity;
    double CriticalDistance;

};


int MotorArduinoControl::initialize()
{
    TotalError = 0;
    AverageError = 0;

    CriticalProximity = 15;
    CriticalDistance = 35;

    registerLogVariable(&Error, "Error");
    registerArduinoLogVariable(&Distance, "Distance");

    registerArduinoControlVariable(&CriticalProximity, "CriticalProximity");
    registerArduinoControlVariable(&CriticalDistance, "CriticalDistance");

    registerLogVariable(&TotalError, "TotalError");
    registerLogVariable(&AverageError, "AverageError");

    return 0;
}

int MotorArduinoControl::start()
{
    TotalError = 0;
    AverageError = 0;

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

    TotalError += Error;

    AverageError = TotalError / frequency();

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

