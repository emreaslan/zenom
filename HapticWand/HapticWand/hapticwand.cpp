#include "hapticwand.h"

using namespace Hardware;

#define PI          (3.1415926535897932384626433832795)

#define L1          (5.670       * 0.0254)  /* length of link 1 in meters */
#define L2          (7.717       * 0.0254)  /* length of link 2 in meters */
#define L3          (8.32232120  * 0.0254)  /* length of link 3 in meters */
#define L4          (1.417202685 * 0.0254)  /* length of link 4 in meters */
#define L5          (1.750       * 0.0254)  /* length of link 5 in meters */
#define L6          (7.000       * 0.0254)  /* length of link 6 in meters */
#define L7          (2.078363285 * 0.0254)  /* length of link 7 in meters */

/* Link lengths of the haptic wand links in meters */
const double HapticWand::l[7] = { L1, L2, L3, L4, L5, L6, L7 };

/* analog output channels driving the haptic wand motors */
const unsigned int HapticWand::analogChannels[6] = { 0, 1, 2, 3, 4, 5 };

/* encoder input channels for the haptic wand joint encoders */
const unsigned int HapticWand::encoderChannels[6] = { 0, 1, 2, 3, 4, 5 };

/* digital output channels driving the amplifier enable lines */
const unsigned int HapticWand::digitalOutputChannels[6] = { 0, 1, 2, 3, 16, 17 };

HapticWand::HapticWand()
{

}

void HapticWand::open(const char *cardType, const int cardIdentifier)
{
    HIL::open( cardType, cardIdentifier );

    // Configures digital I/O lines as outputs.
    setDigitalOutputDirection( digitalOutputChannels, NUM_DIGITAL_OUTPUT );
}

void HapticWand::enableWand()
{
    // enable amplifiers
    const bool amplifiers[NUM_DIGITAL_OUTPUT] = { 1, 1, 1, 1, 1, 1 };
    writeDigital( digitalOutputChannels, amplifiers, NUM_DIGITAL_OUTPUT );
}

void HapticWand::disableWand()
{
    // disable amplifiers
    const bool amplifiers[NUM_DIGITAL_OUTPUT] = { 0, 0, 0, 0, 0, 0 };
    writeDigital( digitalOutputChannels, amplifiers, NUM_DIGITAL_OUTPUT );

    // drive the motors with 0 V
    const double torques[NUM_JOINTS] = { 0, 0, 0, 0, 0, 0 };
    writeAnalog( analogChannels, torques, NUM_JOINTS );
}

void HapticWand::calibrateWand()
{
    disableWand();
    resetEncoders();
}

void HapticWand::resetEncoders()
{
    // reset the encoders to zero
    resetEncoder( encoderChannels, NUM_JOINTS );
}

void HapticWand::readEncoders(int *counts)
{
    HIL::readEncoder( encoderChannels, counts, NUM_JOINTS );
}

void HapticWand::writeAnalogs(const double *voltages)
{
    HIL::writeAnalog( analogChannels, voltages, NUM_JOINTS );
}

void HapticWand::jointAngles(double* jointAngles)
{
    const double offsets[] = { 0.12760527954869, 3.0139873740411, 0.12760527954869, 3.0139873740411, 0.0000, 0.0000 };
    const double factors[] = { 2*PI/20000, 2*PI/20000, -2*PI/20000, -2*PI/20000, 2*PI/20000, 2*PI/20000 };

    // convert counts to radians and rearrange channels appropriately
    for( int i = 0; i < NUM_JOINTS; ++i )
    {
        jointAngles[i] = HIL::readEncoder( encoderChannels[i] ) * factors[i] + offsets[i];
    }
}

void HapticWand::forwardKinematics(double *worldCoordinates)
{
    double theta[ NUM_JOINTS ];

    // convert the encoder counts to joint angles in radians.
    jointAngles( theta );

    // compute joint angles to world co-ordinates
    //worldCoordinates[0] = l[4] / 0.2e1 + cos(theta[2]) * l[0] / 0.2e1 + cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1] / 0.2e1 + cos(theta[0]) * l[0] / 0.2e1 + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] / 0.2e1;
    //worldCoordinates[1] = cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1 - sin(theta[5]) * (-l[6] + l[3]) / 0.2e1 + cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) / 0.2e1 - sin(theta[4]) * (l[6] - l[3]) / 0.2e1;
    //worldCoordinates[2] = sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1 + cos(theta[5]) * (-l[6] + l[3]) / 0.2e1 + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) / 0.2e1 + cos(theta[4]) * (l[6] - l[3]) / 0.2e1;
    worldCoordinates[3] = -atan((cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])));
    worldCoordinates[4] = atan((cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])));


    /*
    worldCoordinates[0] =
            l[4] / 0.2e1 +
            cos(theta[2]) * l[0] / 0.2e1 +
            cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1] / 0.2e1 +
            cos(theta[0]) * l[0] / 0.2e1 +
            cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] / 0.2e1;

    worldCoordinates[1] =
            cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1 -
            sin(theta[5]) * (-l[6] + l[3]) / 0.2e1 +
            cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) / 0.2e1 -
            sin(theta[4]) * (l[6] - l[3]) / 0.2e1;

    worldCoordinates[2] =
            sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1 +
            cos(theta[5]) * (-l[6] + l[3]) / 0.2e1 +
            sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) / 0.2e1 +
            cos(theta[4]) * (l[6] - l[3]) / 0.2e1;
    */

    worldCoordinates[0] =
            l[4] +
            cos(theta[2]) * l[0] +
            cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1] +
            cos(theta[0]) * l[0] +
            cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1];

    worldCoordinates[1] =
            cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) -
            sin(theta[5]) * (-l[6] + l[3]) +
            cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) -
            sin(theta[4]) * (l[6] - l[3]);

    worldCoordinates[2] =
            sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) +
            cos(theta[5]) * (-l[6] + l[3]) +
            sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) +
            cos(theta[4]) * (l[6] - l[3]);
}
