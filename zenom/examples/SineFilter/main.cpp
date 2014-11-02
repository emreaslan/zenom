#include <controlbase.h>
#include <math.h>
#include <ButterworthFilter.hpp>
#include <iostream>
using namespace std;


/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * SineFilter
 * Generates a noisy sinus signal and filter it.
 *
 */
class SineFilter : public ControlBase
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
    double noisySignal;
    double filteredSignal;

    // ----- Control Parameters -----
    double amplitude;
    double cutOffFrequency;
    double dampingRatio;

    // ----- Other variables -----
    ButterworthFilter<double> filter;
};


int SineFilter::initialize()
{
    // ----- Initializes log and control variables -----
    // ----- Register the log variables -----
    registerLogVariable(&sine, "sine");
    registerLogVariable(&noisySignal, "noisySignal");
    registerLogVariable(&filteredSignal, "filteredSignal");

    // ----- Register the control paramateres -----
    registerControlVariable(&amplitude, "amplitude");
    registerControlVariable(&cutOffFrequency, "cutOffFrequency");
    registerControlVariable(&dampingRatio, "dampingRatio");

    cout
        << "This example program generates a noisy sine wave "
        << "and uses a Butterworth filter to remove the noise." << endl;

    return 0;
}


int SineFilter::start()
{
    // ----- Initializes filter attributes -----
    filter.setSamplingTime(period());
    filter.setAutoInit();

    return 0;
}



int SineFilter::doloop()
{
    // ----- Sets filter attributes online.
    filter.setCutOffFrequency(cutOffFrequency);
    filter.setDampingRatio(dampingRatio);

    // ----- Geneates a noisy sine signal and uses filter -----
    double time = simTimeInSec();
    double noise = amplitude / 40 * sin(20 * time) + (rand() % 3) / 10.0;
    sine = amplitude * sin(2 * M_PI * time);

    // ----- Create a noisy signal -----
    noisySignal = sine + noise;

    // ----- Now filter it -----
    filteredSignal = filter.filter(noisySignal);

    return 0;
}

int SineFilter::stop()
{
    return 0;
}

int SineFilter::terminate()
{
    return 0;
}


int main( int argc, char *argv[] )
{
    SineFilter c;
    c.run( argc, argv );

    return 0;
}
