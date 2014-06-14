#define USE_MOTOR

#include "zenomarduinomanager.h"

ZenomArduinoManager zenomManager;

#define echoPin 12
#define led 11
#define led2 10


// Log Variables
double Distance;

// Control Variables
double CriticalProximity = 15;
double CriticalDistance = 35;

void setup()
{
    // Log Variable Register
    zenomManager.registerLogVariable(&Distance, "Distance");
    
    // Control Variable Register
    zenomManager.registerControlVariable(&CriticalProximity, "CriticalProximity");
    zenomManager.registerControlVariable(&CriticalDistance, "CriticalDistance");

    Serial.begin (9600);
    
    // User Code
    pinMode(statpin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);    

    CriticalProximity = 15;
    CriticalDistance = 35; 
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

	motorGo(0, CCW, 1023);
	motorGo(1, CCW, 1023);    
        digitalWrite(led, LOW);
	digitalWrite(led2, HIGH);
    
    if ( Distance < CriticalProximity )
    {
	motorGo(0, CW, 1023);
	motorGo(1, CW, 1023);
        digitalWrite(led, HIGH);
	digitalWrite(led2, LOW);
    }
    else if ( Distance > CriticalDistance )
    {
	motorGo(0, CCW, 1023);
	motorGo(1, CCW, 1023);    
        digitalWrite(led, LOW);
	digitalWrite(led2, HIGH);
    }
    else
    {
	motorOff(0);
	motorOff(1);
	digitalWrite(led, LOW);
	digitalWrite(led2, LOW);
    }        
    
    // User Code End
    
    zenomManager.loopPostProcess();
    delay(100); // delay time editable
}
