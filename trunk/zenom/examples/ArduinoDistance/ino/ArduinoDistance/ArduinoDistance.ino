#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
#define periodicLed 8


#include "ArduinoManager.h"


ZenomArduinoManager zenomManager;
double distance;
double controlVar;
double check;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(periodicLed, OUTPUT);
  
  controlVar = -1;
  
  zenomManager.registerLogVariable(&distance, "distance");
  zenomManager.registerLogVariable(&check, "check");
  zenomManager.registerControlVariable(&controlVar, "controlVar");
}

bool periodicLight = false;
void loop() 
{
  zenomManager.loopPreProcess();
  check = controlVar;
  
  long duration;
  
  digitalWrite(trigPin, LOW);  // Adde
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 5) 
  {
    // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
  }
  else
  {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  
  if (periodicLight)
  {
    digitalWrite(periodicLed, LOW);
    periodicLight = false;
  }
  else
  {
    digitalWrite(periodicLed, HIGH);
    periodicLight = true;
  }
  
  zenomManager.loopPostProcess();
  delay(500);
}
