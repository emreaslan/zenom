
#include <controlbase.h>
#include <math.h>
#include <iostream>
using namespace std;

/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * Sine
 * A simple example of a control program
 * Does not require any hardware, just generates a sine signal
 */
class Sine : public ControlBase
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
    double sine;

    // ----- Control Parameters -----
    double amplitude;
};


int Sine::initialize()
{
    // ----- Initializes log and control variables -----
    // ----- Register the log variables -----
    registerLogVariable(&sine, "sine");

    // ----- Register the control paramateres -----
    registerControlVariable(&amplitude, "amplitude");
    amplitude = 3;

    // ----- Prints message in screen -----
    cout
        << "This is a simple control program that generates "
        << "a sine wave and doesn't access any hardware."
        << "Use the amplitude control parameter to change "
        << "the amplitude of the sine wave" << endl << endl;

    return 0;
}


int Sine::start()
{
    return 0;
}


int Sine::doloop()
{
    // ----- Generates sine wave -----
    sine = amplitude * sin( simTimeInSec() );
    return 0;
}

int Sine::stop()
{
    return 0;
}

int Sine::terminate()
{
    return 0;
}


int main( int argc, char *argv[] )
{
    Sine c;
    c.run( argc, argv );

    return 0;
}
