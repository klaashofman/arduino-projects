/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  //initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

//int toggle = LOW;

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    if (inputString[0] == '1'){
        digitalWrite(led, 1);
        Serial.println("led ON");
    }
    if(inputString[0] == '0') {
        digitalWrite(led, 0);
        Serial.println("led OFF");
    }
    Serial.println(inputString); 
    // clear the string:
    inputString = "";
    stringComplete = false;
    
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    //digitalWrite(led, toggle);
    //toggle^=1;
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}


