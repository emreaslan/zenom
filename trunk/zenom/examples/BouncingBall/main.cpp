
#include <controlbase.h>
#include <Integrator.hpp>

/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * BouncingBall
 * This example simulates a bouncing ball from floor.
 *
 */
class BouncingBall : public ControlBase
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
    Integrator< double > mVelocityIntegrator;   // velocity integrator
    Integrator< double > mPositionIntegrator;   // position integrator

    // ----- Log Variables -----
    double velocity;    // velocity of ball
    double position[3]; // position of ball

    // ----- Control Variables -----
    double g;       // gravity
    double cor;     // coefficient of restitution
};


int BouncingBall::initialize()
{
    registerLogVariable(&velocity, "velocity");
    registerLogVariable(position, "position", 1, 3);

    registerControlVariable(&g, "g");
    registerControlVariable(&cor, "cor");

    g = -9.81;   // m/s^2
    cor = -0.8;  // coefficient of restitution

    position[0] = 0;
    position[1] = 0;

    return 0;
}

int BouncingBall::start()
{
    mVelocityIntegrator.setSamplingPeriod( period() );
    mVelocityIntegrator.reset( 0 );  // initial speed 0 m/s

    mPositionIntegrator.setSamplingPeriod( period() );
    mPositionIntegrator.reset( 15.0 );  // initial height 15 m

    return 0;
}

int BouncingBall::doloop()
{
    double ballRadius = 1;

    velocity = mVelocityIntegrator.integrate( g );
    position[2] = mPositionIntegrator.integrate( velocity );   // position of ball

    // saturation
    if ( position[2] <= ballRadius )
    {
        position[2] = ballRadius;
    }

    // Hits the floor
    if ( position[2] == ballRadius )
    {
        mVelocityIntegrator.reset( velocity * cor );
        mPositionIntegrator.reset( ballRadius );
    }

    return 0;
}

int BouncingBall::stop()
{

    return 0;
}

int BouncingBall::terminate()
{

    return 0;
}


int main( int argc, char *argv[] )
{
    BouncingBall c;
    c.run( argc, argv );

    return 0;
}

