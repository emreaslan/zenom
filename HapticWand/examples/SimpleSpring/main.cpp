/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * SimpleSpring
 * This example demonstrates how to do force control using the HapticWand
 * class. It is designed to control Quanser's 5DOF Haptic Wand.
 *
 */

#include <controlbase.h>
#include <hapticwand.h>
#include <hapticwand_utils.h>

using namespace std;
using namespace Hardware;

class SimpleSpring : public ControlBase
{
public:
    
    // ----- User Functions -----
    // This functions need to be implemented by the user.
    int initialize();
    int start();
    int doloop();
    int stop();
    int terminate();
    
private:
    // ----- Log Variables -----
    double position[3]; // position of the wand
    double rotation[4]; // rotation of the wand
    
    
    // ----- Control Variables -----
    double k[5];    // set elements to get springs in different world coordinates
    
    
    // ----- Variables -----
    HapticWand hapticWand;
};

/**
 * This function is called when the control program is loaded to zenom.
 * Use this function to register control parameters, to register log variables
 * and to initialize control parameters.
 *
 * @return Return non-zero to indicate an error.
 */
int SimpleSpring::initialize()
{
    try
    {
        registerLogVariable( position, "position", 1, 3 );
        registerLogVariable( rotation, "rotation", 1, 4 );

        registerControlVariable( k, "k", 1, 5 );

        k[0] = k[1] = k[2] = k[3] = k[4] = 5;   // initial values

        hapticWand.open();              // Open the q8 card
        hapticWand.calibrateWand();     // Calibrate the haptic wand
    }
    catch( HILException& ex )
    {
        cerr << "Exception occured: " << ex.what() << "." << endl;
        return -1;
    }
    catch(...)
    {
        cerr << "Unknown exception occured." << endl;
        return -2;
    }
    
    return 0;
}

/**
 * This function is called when the START button is pushed from zenom.
 *
 * @return If you return 0, the control starts and the doloop() function is
 * called periodically. If you return nonzero, the control will not start.
 */
int SimpleSpring::start()
{
    try
    {
        hapticWand.enableWand();
    }
    catch( HILException& ex )
    {
        cerr << "Exception occured: " << ex.what() << endl;
        return -1;
    }
    catch(...)
    {
        cerr << "Unknown exception occured." << endl;
        return -2;
    }

    
    return 0;
}


/**
 * This function is called periodically (as specified by the control frequency).
 * The useful functions that you can call used in doloop() are listed below.
 *
 * frequency()          returns frequency of simulation.
 * period()             returns period of simulation.
 * duration()           returns duration of simulation.
 * simTicks()           returns elapsed simulation ticks.
 * simTimeInNano()      returns elapsed simulation time in nano seconds.
 * simTimeInMiliSec()   returns elapsed simulation time in miliseconds.
 * simTimeInSec()       returns elapsed simulation time in seconds.
 * overruns()           returns the count of overruns.
 *
 * @return If you return 0, the control will continue to execute. If you return
 * nonzero, the control will abort and stop() function will be called.
 */
int SimpleSpring::doloop()
{
    try
    {
        double worldCoordinates[5];     // world coordinates X, Y, Z in m and roll (about X) and pitch (about Y) in radians
        double jointAngles[6];        // joint angles in radians
        hapticWand.jointAngles( jointAngles );
        hapticWand.forwardKinematics( jointAngles, worldCoordinates );

        // transform to osg coordinate system.
        transformToOSG( worldCoordinates, position, rotation );

        const double home[5] = { 0, 0.124, 0, 0, 0 };   // home position, in front of calibration position
        double worldForces[5];         // world forces in N and world torques in N-m

        // Compute forces in world coordinates (simple spring in this example)
        for (int i = 0; i < 5; i++)
            worldForces[i] = k[i] * (worldCoordinates[i] - home[i]);

        // Drive the motors to produce the desired world-space forces and torques
        hapticWand.generateForces( period(), jointAngles, worldForces );
    }
    catch( HILException& ex )
    {
        cerr << "Exception occured: " << ex.what() << endl;
        return -1;
    }
    catch(...)
    {
        cerr << "Unknown exception occured." << endl;
        return -2;
    }

    return 0;
}


/**
 * Called when a timed run ends or the STOP button is pushed from zenom.
 *
 * @return Return non-zero to indicate an error.
 */
int SimpleSpring::stop()
{
    hapticWand.disableWand();
    
    return 0;
}


/**
 * This function is called when the control is unloaded. It happens when
 * the user loads a new control program or exits.
 *
 * @return Return non-zero to indicate an error.
 */
int SimpleSpring::terminate()
{
    hapticWand.close();     // Close the q8 card.
    
    return 0;
}


/**
 * The main function starts the control program
 */
int main( int argc, char *argv[] )
{
    SimpleSpring c;
    c.run( argc, argv );
    
    return 0;
}

