/*********************************************************************
 **  Description:                                                    **
 **  This file is a sample code for your reference.                  **
 **                                                                  **
 **  Copyright (C) 2011 ElecFreaks Corp.                             **
 **  Created by ElecFreaks Robi.W /29 Sep 2011                      **
 **                                                                  **
 **  http://www.elecfreaks.com                                       **
 *********************************************************************/
#include <SoftwareSerial.h>
#include <TimerOne.h>

#define rxPin 2
#define txPin 3


SoftwareSerial mySerial(rxPin, txPin);
// Switch settings bluetooth shield
// H: AT command mode (slow blinking led)
// L: RF-connection mode (fast blinking led)
// LED 2: ON : pairing successfull

// List of AT commands: 
http://elecfreaks.com/store/download/datasheet/Bluetooth/HC-0305%20serail%20module%20AT%20commamd%20set%20201104%20revised.pdf
// Warning: set terminal to "NO LINE ENDING"
#define AT  // enabled, set switch to 'H' else set switch to 'L'
/*
AT
OK

AT+VERSION
+VERSION:2.0-20100601

AT+ADDR
+ADDR:2013:5:90196

AT+NAME
+NAME:HC-05

AT+UART
+UART:38400,0,0
*/
 
void Callback()
{
   Serial.println("------->  Callback Send AT");
   mySerial.print("AT\r\n");
}
 
void setup()
{
   // define pin modes for tx, rx pins:
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   
#ifdef AT
   mySerial.begin(38400);
   Serial.begin(38400);
#else
   mySerial.begin(9600);
   Serial.begin(9600);
#endif
    
//   Timer1.initialize(2000000);             // setting callback is 2s
//   Timer1.attachInterrupt(Callback); 
}
 
void loop()
{
  int i = 0;
  char someChar[32] = {0};
  // when characters arrive over the serial port...
  if(Serial.available()) {
    do{
      someChar[i++] = Serial.read();
      //As data trickles in from your serial port you are grabbing as much as you can, 
      //but then when it runs out (as it will after a few bytes because the processor 
      //is much faster than a 9600 baud device) you exit loop, which then restarts, 
      //and resets i to zero, and someChar to an empty array.So please be sure to keep this delay 
      delay(3);                  
 
    }while (Serial.available() > 0);
 
    mySerial.println(someChar);
    Serial.println(someChar);
  }
 
  while(mySerial.available()) 
      Serial.print((char)mySerial.read());    
}
