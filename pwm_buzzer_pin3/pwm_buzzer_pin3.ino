/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int ledPin = 3;    // buzzer connected to analog out pin 3

void setup()  { 
  // nothing happens in setup 
} 

int i_delay  = 1;
int i_step = 50;

void loop()  { 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue += i_step) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(i_delay);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -= i_step) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(i_delay);                            
  } 
}


