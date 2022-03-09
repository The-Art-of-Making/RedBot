/*
  Line Follower
  Controls a RedBot's motors so that they follow a line.

  The code uses the IR sensor reading from the leads to detect when to turn so
  that it can stay on the line. Note that button D12 needs to be pushed before 
  the robot will start following the line.

  This example code is in the public domain and made adapted for
  ENGR 0716/1716 The Art of Making: An Introduction to Hands-On System Design and Engineering
  at the University of Pittsburgh, taught by Joseph Samosky, PhD.

  Major rewrite Sept. 3-8, 2019 Joseph Samosky
  Original AoM version (modified from SParkFun code) 14 Jan 2015 by Zachary Barnes and Ian McIntyre
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

// Instantiate the sensors. Left IR sensor is connected to pin A3; middle to A6; right to A7.
RedBotSensor lSen = RedBotSensor(A3);
RedBotSensor mSen = RedBotSensor(A6);
RedBotSensor rSen = RedBotSensor(A7);

// Instantiate a servo- this is outside of the RedBot library!
Servo servo;

// Create an alias for our pin that the buzzer board is connected to, for ease of use.
#define BUZZER 9

// Create an alias for the onboard pushbutton.
#define BUTTON_PIN 12

// Create an alias for the onboard LED.
#define LED_PIN 13

// Constants for the sensor output levels that determine detection of the line.
// Note: the line sensors shine IR light on a surface and measure how much reflects back.
// They output a value between 0 and 1023.
// *Lower* values = *more* IR is refleced back.
// So, for a fixed height above a surface, over a light-colored background they will output
// lower values.(Typically in the range of 30 - 750) and over a dark color they will output
// *higher* values (around 900 to 1000.)
// If there is no reflection (like at the edge of a table) the output level will be maximum,
// typically in the range of 1010-1023.

const int lineLevel = 850; // Below this level = light. Above this level = dark.
const int offLevel = 1005; // Above this level = no reflection: you're at the edge of an abyss!

// Variables to hold the values read from the left, middle and right IR lne sensors
int left;
int middle;
int right;

// Flag to start line following when D12 button is pressed.
boolean start_following = false;

void setup()
{
  //  We *probably* won't see the hardware serial data; what good is a robot
  //  that has to be tethered to a computer?
  //  But we'll enable serial communication in case you'd like to do something
  //  like stream the line sensor output values to the serial window so you can
  //  see how their output changes when they're over white vs dark areas. 
  Serial.begin(9600);  //Turn on serial communication
  Serial.println("Hello world!");
  
  // Set up our two built-in IO devices- the button and the LED.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  // Play a 3-note "tune" to audibly signal reset
  tone(BUZZER, 523, 250); // Play a 523Hz (C5 on a piano) square wave for 250ms
  delay(250);
  tone(BUZZER, 784, 250); // Play a 584Hz (G5) square wave for 250ms
  delay(250);
  tone(BUZZER, 1047, 250); // Play a 1047Hz (C6) square wave for 250ms
  delay(250);
}

void loop()
{
  // Wait for the D12 button to be pressed, then turn on the start_following flag
  // to continue with the rest of the loop. 
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    start_following = true;
  }

  
  if (start_following)
  {

    // Read the IR line sensor values
    left = lSen.read();
    middle = mSen.read();
    right = rSen.read();
    
    // Open the serial monitor window (n the Arduino IDE: selecting Tools-->Serial Monitor)
    // to see the real-time values of the sensors:
    
      Serial.print("L = ");
      Serial.print(left);
      Serial.print("\t");  // tab character
      Serial.print("M  = ");
      Serial.print(middle);
      Serial.print("\t");  // tab character
      Serial.print("R  = ");
      Serial.print(right); 
      Serial.println();

    // Line following code:

    // Case 1: Both L and R are over white. M is over dark. RedBot is on a line: drive forward!
    if (left < lineLevel && middle > lineLevel && right < lineLevel)
    {
      motors.drive(120);
    }
    // Case 1: L, M and R are over white. RedBot is off the track: drive forward slowly to find track!
    if (left < lineLevel && middle < lineLevel && right < lineLevel)
    {
      motors.drive(60);
    }
    // Case 2: Right sensor is on black, left is on white. Recenter by turning right.
    if (right > lineLevel && left < lineLevel) 
    {
      motors.leftDrive(80); // Left motor drives forward.
      motors.rightDrive(-80); // Right motor drives backward. --> RedBot turns toward rght.
    }
    // Case 3: Left sensor is on black, right is on white. Recenter by turning left.
    if (left > lineLevel && right < lineLevel) 
    {
      motors.rightDrive(80);
      motors.leftDrive(-80);
    }
    // Case 4: All 3 sensors are on black, indicating sensor array is parallel to a line. Or all 3 are over an edge!
    // (I.e., low reflectance seen by all 3 sensors.)
    // Back up and turn slightly for 0.5s to reorient RedBot.
    if (left > lineLevel && middle > lineLevel && right > lineLevel)
    {
      motors.rightDrive(-120);
      motors.leftDrive(-50);
      delay(500);
    }

  }
  else motors.brake();
}
