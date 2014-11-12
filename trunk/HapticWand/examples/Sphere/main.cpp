/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * Sphere
 *
 *
 */

#include <controlbase.h>
#include <hapticwand.h>
#include <hapticwand_utils.h>
#include <ColumnVector.hpp>
#include <Euler2DigitalFilter.hpp>

using namespace std;
using namespace Hardware;

class Sphere : public ControlBase
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
    ColumnVector<5, double> virtual_object( ColumnVector<3, double>& center,
        double radius, ColumnVector<5, double>& k_stiff, ColumnVector<5, double>& k_damp,
        ColumnVector<3, double>& w_xyz, ColumnVector<5, double>& w_dot );

    // ----- Log Variables -----
    double position[3]; // position of the wand
    double rotation[4]; // rotation of the wand
    ColumnVector<5, double> F;


    // ----- Control Variables -----



    // ----- Variables -----
    HapticWand hapticWand;
    Euler2DigitalFilter< ColumnVector<5> > digitalFilter;
};

/**
 * This function is called when the control program is loaded to zenom.
 * Use this function to register control parameters, to register log variables
 * and to initialize control parameters.
 *
 * @return Return non-zero to indicate an error.
 */
int Sphere::initialize()
{
    try
    {
        registerLogVariable( position, "position", 1, 3 );
        registerLogVariable( rotation, "rotation", 1, 4 );

        registerLogVariable( F.getElementsPointer(), "F", 1, 5 );

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
int Sphere::start()
{
    try
    {
        hapticWand.enableWand();

        // Filter Cutoff (rad/s)
        double wn_f = 150;

        // Filter Damping Ratio
        double zeta_f = 1;

        digitalFilter.setSamplingPeriod( period() );
        digitalFilter.setCutOffFrequencyRad( wn_f );
        digitalFilter.setDampingRatio( zeta_f );

        ColumnVector<5, double> resetValues;
        resetValues = 0;
        digitalFilter.reset( resetValues );

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
int Sphere::doloop()
{
    try
    {
        ColumnVector<5, double> worldCoordinates;
        double jointAngles[6];        // joint angles in radians
        hapticWand.jointAngles( jointAngles );
        hapticWand.forwardKinematics( jointAngles, worldCoordinates.getElementsPointer() );

        transformToOSG( worldCoordinates.getElementsPointer() , position, rotation ); // transform to osg coordinate system.

        //const double home[5] = { 0, 0.124, 0, 0, 0 };   // home position, in front of calibration position
        //double worldForces[5];         // world forces in N and world torques in N-m



        // Center of Object (m)
         ColumnVector<3, double> vo_c;
         vo_c = 0, 0.3, 0;

         // Radius of Object (m)
         double vo_r = 0.05;

         // Stiffness (N/m)
         ColumnVector<5, double> kp;
         kp = 500, 500, 500, 1000, 1000;

         // Damping (N.s/m, N.s/rad)
         ColumnVector<5, double> kd;
         kd = 5, 5, 5, 100, 100;

         ColumnVector<3, double> w_xyz;
         w_xyz.setElement(1, worldCoordinates(1));
         w_xyz.setElement(2, worldCoordinates(2));
         w_xyz.setElement(3, worldCoordinates(3));

         ColumnVector<5, double> w_dot = digitalFilter.integrate( worldCoordinates );

         F = virtual_object( vo_c, vo_r, kp, kd, w_xyz, w_dot );

         F.setElement( 1, F.getElement(1) );
         F.setElement( 2, F.getElement(2) );
         F.setElement( 3, F.getElement(3) );
         F.setElement( 4, F.getElement(4) / 1000 );
         F.setElement( 5, F.getElement(5) / 1000 );

         //hapticWand.generateForces( period(), jointAngles, F.getElementsPointer(), output );

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
int Sphere::stop()
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
int Sphere::terminate()
{
    hapticWand.close();
    
    return 0;
}

/*
% Inputs:
% center    = center of object (m)
% radius    = radius of object (m)
% k_stiff   = Stiffness gain (N/m)
% k_damp    = Damping gain (N.s/m)
% w         = world coordinates of wand (m,rad)
% w_dot     = world rate of wand (m/s,rad/s)
%
% Output:
% F = Output force (N)
%
*/
ColumnVector<5, double> Sphere::virtual_object( ColumnVector<3, double>& center,
    double radius, ColumnVector<5, double>& k_stiff, ColumnVector<5, double>& k_damp,
    ColumnVector<3, double>& w_xyz, ColumnVector<5, double>& w_dot )
{
    // Output Force (N)
    ColumnVector<5, double> F;

    // Vector from object to wand (m)
    ColumnVector<3, double> r = w_xyz - center;
    // Distance of r (m)
    double r_abs = r.norm();

    // Is wand inside object?
    if ( r_abs < radius )
    {
        // normalized direction vector
        ColumnVector<3, double> dir = r / r_abs;

        // stiffness force (N)
        ColumnVector<5, double> F_stiff;
        F_stiff.setElement(1, dir.getElement(1) * k_stiff.getElement(1) * (radius - r_abs) );
        F_stiff.setElement(2, dir.getElement(2) * k_stiff.getElement(1) * (radius - r_abs) );
        F_stiff.setElement(3, dir.getElement(3) * k_stiff.getElement(1) * (radius - r_abs) );
        F_stiff.setElement(4, 0 );
        F_stiff.setElement(5, 0 );

        // damping force (N)
        ColumnVector<5, double> F_damp = elementProduct( k_damp, w_dot );
        F_damp *= -1;

        // total force
        F = F_stiff + F_damp;
    }
    else
    {
        // Wand not touching object.
        F = 0;
    }

    return F;
}


/**
 * The main function starts the control program
 */
int main( int argc, char *argv[] )
{
    Sphere c;
    c.run( argc, argv );
    
    return 0;
}

