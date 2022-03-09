/*
  Line Follower
  Controls a RedBot's motors so that they follow a line.

  The code uses the IR sensor reading from the leads to detect when to turn so
  that it can stay on the line. Note that button D12 needs to be pushed before 
  the robot will start following the line.

  This example code is in the public domain and made adapted for ENGR 0716
  at the University of Pittsburgh, taught by Joseph Samosky, PhD.

  modified 14 Jan 2015
  by Zachary Barnes and Ian McIntyre
*/
 
 
// Include the library.
#include <RedBot.h>
#include <Servo.h>
#include "notes.h"

// Instantiate the motors.
RedBotMotors motors;

// Instantiate the accelerometer. It can only be connected to pins A4
//  and A5, since those are the I2C pins for this board.
RedBotAccel xl;

// Instantiate our encoder. 
RedBotEncoder encoder = RedBotEncoder(A2, A3); // left, right

// Instantiate the sensors. Sensors can only be created for analog input
//  pins; the accelerometer uses pins A4 and A5. Also, since A6 and A7
//  can *only* be used as analog inputs, that's a good place for these.
RedBotSensor lSen = RedBotSensor(A3);
RedBotSensor mSen = RedBotSensor(A6);
RedBotSensor rSen = RedBotSensor(A7);

// Instantiate a software serial port. Note that the regular Arduino
//  SoftwareSerial won't work! It steals resources that the sensor
//  inputs on the RedBot need. Also note that the RedBot version has
//  no input options- it automatically connects to the pins used for
//  the onboard XBee header.
RedBotSoftwareSerial swsp;

// Instantiate a servo- this is outside of the RedBot library!
Servo servo;

// Create an alias for our beeper pin, for ease of use.
#define BEEPER 9

// Create an alias for the onboard pushbutton.
#define BUTTON_PIN 12

// Create an alias for the onboard LED.
#define LED_PIN 13

// Constants for the levels that determine detection of the line.
const int bgLevel = 600;
const int lineLevel = 650;
const int offLevel = 1000;

// Flag for bumpers to send the signal that something's wrong and the motors should
//  be disabled for now. Set in the bump functions, volatile so the change is sure
//  to propagate to the loop() function.
volatile boolean bumped = true;

void setup()
{
  // We *probably* won't see the hardware serial data; what good is a robot
  //  that has to be tethered to a computer?
  Serial.begin(9600);
  Serial.println("Hello world!");
  
  // Set up our two built-in IO devices- the button and the LED.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  // Play a tone for audible reset detection.
  tone(BEEPER, 2600, 750);
  delay(750);
  
  // Send out a hello via the XBee, if one is present.
  swsp.begin(9600);
  swsp.print("Hello, world");
  servo.attach(3);
}

void loop()
{
  // These static variables will be initialized once, then remain valid
  //  through each iteration of the loop.

  // Wait for the button to be pressed, then turn off the "bumped" flag
  //  so the motors can run. Also, clear the encoders, so we can track
  //  our motion.
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    bumped = false;
    encoder.clearEnc(BOTH);
  }
  
  
  if (!bumped)
  {
    // Line following code: turn away from any sensor that is above the line
    //  threshold.
    
    // Case 1: both white. Drive forward!
    if (lSen.read() < lineLevel && rSen.read() < lineLevel) motors.drive(80);
    
    // Case 2: right sensor is on black. Must recenter.
    if (rSen.read() > lineLevel && lSen.read() < lineLevel) 
    {
      motors.leftDrive(70);
      motors.rightDrive(-20);
    }
    // Case 3: left sensor is on black. Must recenter.
    if (lSen.read() > lineLevel && rSen.read() < lineLevel) 
    {
      motors.rightDrive(70);
      motors.leftDrive(-20);
    }
    // Case 4: both sensors see dark
    if (lSen.read() > lineLevel && rSen.read() > lineLevel)
    {
      motors.rightDrive(80);
      motors.leftDrive(80);
    }
    if (lSen.read() > offLevel && rSen.read() > offLevel && mSen.read() > offLevel)
    {
      motors.rightDrive(-80);
      motors.leftDrive(-80);
      delay(500);
    }
  }
  else motors.brake();
}
