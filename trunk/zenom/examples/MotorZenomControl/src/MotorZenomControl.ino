#define USE_MOTOR

#include "zenomarduinomanager.h"

ZenomArduinoManager zenomManager;

#define echoPin 12
#define led 11
#define led2 10

// Log Variables
double Distance;

// Control Variables
double MotorDirection = 0;

void setup()
{
    // Log Variable Register
    zenomManager.registerLogVariable(&Distance, "Distance");
    
    // Control Variable Register
    zenomManager.registerControlVariable(&MotorDirection, "MotorDirection");

    Serial.begin (9600);
    
    // User Code
    initMotor();
    pinMode(statpin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT); 
}

void loop()
{
    zenomManager.loopPreProcess();
    
    // User Code Begin
    long duration;
  
    digitalWrite(statpin, LOW);  // Adde
    delayMicroseconds(2); // Added this line
    digitalWrite(statpin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(statpin, LOW);
    duration = pulseIn(echoPin, HIGH);
    Distance = (duration/2) / 29.1;
    if (Distance > 200)
    {
	Distance = 200;
    }
    
    if ( (int)MotorDirection == 0 )
    {
	motorOff(0);
	motorOff(1);
    }
    else if ( (int)MotorDirection == 1 )
    {
	motorGo(0, CW, 1023);
	motorGo(1, CW, 1023);
    }
    else if ( (int)MotorDirection == 2 )
    {
	motorGo(0, CCW, 1023);
	motorGo(1, CCW, 1023);
    }    
    
    // User Code End
    
    zenomManager.loopPostProcess();
    //delay(500); // delay time editable
}
