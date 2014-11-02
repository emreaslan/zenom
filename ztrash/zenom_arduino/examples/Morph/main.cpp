
#include <controlbase.h>
#include <math.h>

/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * Morph
 * We modify vertex coordinates of the block.
 *
 */
class Morph : public ControlBase
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
    double vertices[8][3];


    // ----- Control Variables -----
    double amplitude;

};


int Morph::initialize()
{
    registerLogVariable(vertices[0], "vertices", 8, 3);
    registerControlVariable(&amplitude, "amplitude");

    return 0;
}

int Morph::start()
{

    return 0;
}

int Morph::doloop()
{
    // TODO 50000hz 100s controlbase gidiyor. loglama ile ilgili bir problem olabilir.
    double constantCoords[8][3] =
    {
        { -1,  1,  1 },
        {  1,  1,  1 },
        {  1,  1, -1 },
        { -1,  1, -1 },
        { -1, -1,  1 },
        {  1, -1,  1 },
        {  1, -1, -1 },
        { -1, -1, -1 },
    };

    double variableCoords[8][3] =
    {
        {  1, -1,  0 },
        { -1, -1,  0 },
        {  0,  0,  0 },
        {  0,  0,  0 },
        {  1,  1,  0 },
        { -1,  1,  0 },
        {  0,  0,  0 },
        {  0,  0,  0 },
    };

    double val = amplitude * sin( M_PI * 2 * simTimeInSec() ) + 0.5;

    // Modifies vertex coordinates.
    for ( int i = 0; i < 8; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            vertices[i][j] = constantCoords[i][j] + variableCoords[i][j] * val;
        }
    }

    return 0;
}

int Morph::stop()
{

    return 0;
}

int Morph::terminate()
{

    return 0;
}


int main( int argc, char *argv[] )
{
    Morph c;
    c.run( argc, argv );

    return 0;
}
