/***********************************************************************
"La RedBotRacha" 
  to the tune of La Cucaracha

Melody credit http://www.8notes.com/scores/13311.asp

***********************************************************************/

#include <RedBot.h> // This line "includes" the RedBot library into your sketch.
                    // Provides special objects, methods, and functions for the RedBot.

#include "notes.h"
// This header file enables you to refer to notes by their note names rather
// than frequencies. Open notes.h in a text editor to see all the definitions.
// noteC4 = middle C
// noteAb3 = the A flat below middle C
// noteFs4 = the F sharp above mildde C
// etc.
// These definitions are not used in this program: the notes are defined below
// so you can see the explicit mappings of note names to frequencies.

RedBotMotors motors; // Instantiate the motor control object. 
                     // This only needs to be done once.

// Create an alias for the pin (pin 9) that the BUZZer board is connected to, for ease of use.
#define BUZZ 9

// Create an alias for the onboard pushbutton D12.
#define BUTTON_PIN 12

const int l = 500; // tone length multiplier, millisec
const int ts = 150; // turn speed
const int spin = ts * 1; // full spin speed

const int C = 261.6; // middle C (C4)
const int Cs = 277.2; // C4 sharp
const int D = 293.7;
const int Eb = 311.1; // E4 flat
const int E = 329.6;
const int F = 349.2;
const int Fs = 370.0;
const int G = 392.0;
const int Gs = 415.3;
const int A = 440.0;
const int Bb= 466.2;
const int B = 493.9;
const int hC = 523.3; // "high C" (C5)
const int hD = 587.3;
const int hEb = 622.3;
const int hE = 659.3; 

void setup()
{  
  pinMode(BUZZ, OUTPUT); // configures the buzzer pin as an OUTPUT
  pinMode(BUTTON_PIN, INPUT_PULLUP); // configures the button D12 as an INPUT
                                    // INPUT_PULLUP defaults it to HIGH.
}

void loop()
{
  if ( digitalRead(BUTTON_PIN) == LOW ) // if the button D12 is pushed (LOW)
  {
    // Part 1
    motors.rightMotor(ts); // half-turn left forward while first 3 notes play
    tone(BUZZ, C); delay(l*0.5); // Play middle C for l*0.5 millisecons. 
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5); 
    motors.rightMotor(-ts); // half-turn left backward while 4th note (F) plays
    tone(BUZZ, F); delay(l*1.5);
    motors.brake();
    tone(BUZZ, A); delay(l*1);

    motors.leftMotor(-ts); // half-turn right forward
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5);
    motors.leftMotor(ts); // half-turn back forward
    tone(BUZZ, F); delay(l*1.5);
    motors.brake();
    tone(BUZZ, A); delay(l*2.5);
  
    // Part 2
    delay(l*1);
    motors.rightMotor(spin); motors.leftMotor(spin); //ccw jig
    tone(BUZZ, F); delay(l*0.5);
    motors.rightMotor(-spin); motors.leftMotor(-spin); //cw jig
    tone(BUZZ, F); delay(l*0.5);
    motors.rightMotor(spin); motors.leftMotor(spin); 
    tone(BUZZ, E); delay(l*0.5);
    motors.rightMotor(-spin); motors.leftMotor(-spin); 
    tone(BUZZ, E); delay(l*0.5);
    motors.rightMotor(spin); motors.leftMotor(spin); 
    tone(BUZZ, D); delay(l*0.5);
    motors.rightMotor(-spin); motors.leftMotor(-spin);  
    tone(BUZZ, D); delay(l*0.5);
    motors.rightMotor(spin); motors.leftMotor(spin); 
    tone(BUZZ, C); delay(l*0.5); // split to two notes
    motors.rightMotor(-spin); motors.leftMotor(-spin); 
    motors.brake();
    tone(BUZZ, C); delay(l*2);
    
    // Part 3
    motors.rightMotor(ts); // half-turn left forward
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5);
    motors.rightMotor(-ts); // half-turn left backward
    tone(BUZZ, E); delay(l*1.5);
    motors.brake(); 
    tone(BUZZ, G); delay(l*1);
    
    motors.leftMotor(-ts); // half-turn right forward
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5);
    motors.leftMotor(ts); // half-turn right backward
    tone(BUZZ, E); delay(l*1.5);
    motors.brake();
    tone(BUZZ, G); delay(l*2.5);
  
    // Part 4
    delay(l*1);
    motors.rightMotor(spin); motors.leftMotor(spin); //ccw jig
    tone(BUZZ, hC); delay(l*0.5);
    motors.rightMotor(-spin); motors.leftMotor(-spin); //cw jig
    tone(BUZZ, hD); delay(l*0.5);
    motors.rightMotor(spin); motors.leftMotor(spin);
    tone(BUZZ, hC); delay(l*0.5);
    motors.rightMotor(-spin); motors.leftMotor(-spin); 
    tone(BUZZ, hC); delay(l*0.5);
    motors.rightMotor(spin); motors.leftMotor(spin); 
    tone(BUZZ, A); delay(l*0.5);
    motors.rightMotor(-spin); motors.leftMotor(-spin); 
    tone(BUZZ, G); delay(l*0.5);
    motors.rightMotor(spin); motors.leftMotor(spin); 
    tone(BUZZ, F); delay(l*0.5); 
    motors.brake(); delay(l*3.5);
    
    // Part 5
    delay(l*1);
    motors.rightMotor(spin); motors.leftMotor(spin); //ccw spin
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, C); delay(l*0.5);
    tone(BUZZ, F); delay(l*0.5);
    tone(BUZZ, F); delay(l*0.5);
    tone(BUZZ, A); delay(l*0.5);
    tone(BUZZ, A); delay(l*0.5);
    tone(BUZZ, hC); delay(l*1.5);
    tone(BUZZ, A); delay(l*2.5);
    delay(l*1);
    
    // Part 6
    motors.rightMotor(-spin); motors.leftMotor(-spin); //cw spin
    tone(BUZZ, hC); delay(l*0.5);
    tone(BUZZ, hD); delay(l*0.5);
    tone(BUZZ, hC); delay(l*0.5);
    tone(BUZZ, Bb); delay(l*0.5);
    tone(BUZZ, A); delay(l*0.5);
    tone(BUZZ, hC); delay(l*0.5);
    tone(BUZZ, Bb); delay(l*1.5);
    tone(BUZZ, G); delay(l*2.5);
    delay(l*1);
    
    // Part 7
    motors.rightMotor(spin); motors.leftMotor(spin); //ccw spin
    tone(BUZZ, hC); delay(l*0.5);
    tone(BUZZ, hC); delay(l*0.5);
    tone(BUZZ, E); delay(l*0.5);
    tone(BUZZ, E); delay(l*0.5);
    tone(BUZZ, G); delay(l*0.5);
    tone(BUZZ, G); delay(l*0.5);
    tone(BUZZ, Bb); delay(l*1.5); 
    tone(BUZZ, G); delay(l*2.5);
    delay(l*1);
    
    // Part 8
    motors.rightMotor(-spin); motors.leftMotor(-spin); //cw spin
    tone(BUZZ, hC); delay(l*0.5);
    tone(BUZZ, hD); delay(l*0.5);
    tone(BUZZ, hC); delay(l*0.5);
    tone(BUZZ, Bb); delay(l*0.5);
    tone(BUZZ, A); delay(l*0.5);
    tone(BUZZ, G); delay(l*0.5);
    motors.brake();
    tone(BUZZ, F); delay(l*4);
    noTone(BUZZ); // Turn off last note.
  }
    
  else  // If button D12 is not pushed, do nothing.
  { 
  }
  
}
