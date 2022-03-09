/***********************************************************************
 * BlinkNBoogie -- RedBot Expiriment 1
 * 
 * Developed for Art of Making course from SparkFun and community code
 * 
 * This code should blink the on-board LED 
 * and drive forward when the on-board button is pressed.
 * 
 * 23 Sept 2013 N. Seidle/M. Hord
 * 04 Oct 2014 B. Huang
 * 13 Jan 2018 T. Driscoll
 ***********************************************************************/

#include <RedBot.h>  // This line "includes" the RedBot library into your sketch.
// Provides special objects, methods, and functions for the RedBot.

RedBotMotors motors; // Instantiate the motor control object. This only needs
// to be done once.


void setup() {
  // setup() function runs once at the very beginning

  // The RedBot has an LED connected to pin 13.
  pinMode(13, OUTPUT); //We have to first configure it as an OUTPUT using this command
  
  //Pin 12 is where the on-board button is located
  //We will make pin 12 an input that has an internal pull-up resistor 
  pinMode(12, INPUT_PULLUP); //It will be LOW (0) when pressed and HIGH (1) when unpressed
  
} // end of setup() function



void loop() {
  // loop() function repeats over and over... forever!
  
  digitalWrite(13, HIGH); // Turns LED ON -- HIGH puts 5V on pin 13. 
  delay(100);             // delay(500) "pauses" the program for 500 milliseconds

  //We are going to 'read' the digital signal from the button 
  int buttonPress = digitalRead(12); 
  
  if (buttonPress == LOW) { // 'if' the button is LOW (pressed)
    motors.drive(100);      // Turn on Left and right motors to drive forward
    delay(1000);
    motors.stop();          // Stops both motors        
  }

  digitalWrite(13, LOW);    // Turn LED OFF -- LOW puts 0V on pin 13
  delay(100);

} // end of loop() function

// end of code
