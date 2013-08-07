/*
  Blink
  Turns on an buz on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an buz connected on most Arduino boards.
// give it a name:
int buz = 3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(buz, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(buz, HIGH);   // turn the buz on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(buz, LOW);  // turn the buz on (HIGH is the voltage level)
  delay(10);               // wait for a second
  digitalWrite(buz, HIGH);   // turn the buz on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(buz, LOW);  // turn the buz on (HIGH is the voltage level)
  delay(10);               
  digitalWrite(buz, LOW);    // turn the buz off by making the voltage LOW
  delay(1000);               // wait for a second
}
