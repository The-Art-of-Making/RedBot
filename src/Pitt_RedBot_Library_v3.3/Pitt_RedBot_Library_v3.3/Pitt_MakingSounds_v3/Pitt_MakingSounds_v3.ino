/***********************************************************************
 * Pitt_MakingSounds_v3
 *
 * After uploading this sketch, push the D12 button on the RedBot Mainboard 
 * to make some noise and start running!
 *
 * Hardware setup:
 * Plug the included RedBot Buzzer board into the Servo header labeled 9.
 *
 * This sketch was written by SparkFun Electronics, with lots of help from 
 * the Arduino community. Modifications were made by the staff of ENGR 0716
 * at the University of Pittsburgh. This code is completely free for any use.
 * 
 * 23 Sept 2013 N. Seidle/M. Hord
 * 29 Oct 2014 B. Huang
 * 14 Jan 2015 Zach Patterson: Modifications and save as Pitt_MakingSounds
 * 24 Jan 2015 Joseph Samosky: Edits and save as Pitt_MakingSounds_v2
 * 10 Sept 2015 Joseph Samosky: Edited comments and saved as Pitt_MakingSounds_v3
 *
 ***********************************************************************/

#include <RedBot.h>
RedBotMotors motors;

// Create a couple of constants for our pins.
const int buzzerPin = 9;
const int buttonPin = 12;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP); // configures the button as an INPUT
  // INPUT_PULLUP defaults it to HIGH.
  pinMode(buzzerPin, OUTPUT);  // configures the buzzerPin as an OUTPUT
}

void loop()
{ 
  if ( digitalRead(buttonPin) == LOW ) // if the button is pushed (LOW)
  { 

    // Play a 1kHz tone on the pin number held in the variable "buzzerPin". 
    tone(buzzerPin, 1000);
    delay(500);   // Wait for 500 ms. 
    noTone(buzzerPin);   // Stop playing the tone.
    
    // The above code plays a tome of a specified duration using the delay() function.
    // Note that program execution pauses until the delay interval is finished.
    
    //Below is an alternative way of controlling tone length: by using
    // a third parameter in the function argument list (here: 500) to specify the
    // tone’s duration in milliseconds. Note that program execution *continues* 
    // while the tone is playing, so we can activate the RedBot's motors during 
    // the tone.

    // Play a 2kHz tone on the buzzer pin for 500 ms.
    tone(buzzerPin, 2000, 500);  

    delay(1000);           // Delay for 1000 ms. For first 500 ms, the tone is playing.
    motors.drive(255);     // Start the motors.
    delay(1000);           // Delay for 1 second.

    motors.brake();        // Stop the motors.
  }

  else  // Otherwise, do this (nothing).
  { 
  }
}
