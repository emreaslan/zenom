#include <controlbase.h>
#include <iostream>
using namespace std;

/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * HelloWorld
 * This program prints function messages in screen.
 *
 */

class HelloWorld : public ControlBase
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
    int counter;

};


int HelloWorld::initialize()
{
    cout << " Hello! program has been  Initialized and ready to start!" << endl;
    counter = 0;
    return 0;
}

int HelloWorld::start()
{
    cout << "Hello program has been started!" << endl;
    return 0;
}

int HelloWorld::doloop()
{
    counter++;
    if(counter==1)
        cout << "Doing Calculations now!" << endl;
    return 0;
}

int HelloWorld::stop()
{
    cout << " Have to Stop now :( " <<"\n"<< endl;
    cout << " please Start me again " << endl;
    return 0;
}

int HelloWorld::terminate()
{
    return 0;
}


int main( int argc, char *argv[] )
{
    HelloWorld c;
    c.run( argc, argv );

    return 0;
}
