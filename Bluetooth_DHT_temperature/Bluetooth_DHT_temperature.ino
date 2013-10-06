#include <dht.h>
#include <SoftwareSerial.h>

#define sensor_pin A1 //no ; here. Set equal to channel sensor is on

dht sensor;

#define rxBt 2
#define txBt 3

SoftwareSerial bluetooth(rxBt, txBt);

const int led_pin = 13;

void setup(){
   // bluetooth
   pinMode(rxBt, INPUT);
   pinMode(txBt, OUTPUT);  
   bluetooth.begin(38400);
   // usb port
   Serial.begin(38400);
   // led
   pinMode(led_pin, OUTPUT);
}

void loop(){
  
  sensor.read11(sensor_pin);
  
  char c[32] = {0};
  int i = 0;
  while (bluetooth.available()){
    c[i++] = bluetooth.read();
  }
  String cmd = c;
  if (cmd == "HELP"){
    bluetooth.println("Boinkers");
  }  
  if (cmd == "LED1"){
    digitalWrite(led_pin, 1);
  } 
  if (cmd == "LED0"){
    digitalWrite(led_pin, 0);
  }
  if (cmd == "SENS"){
    bluetooth.print(sensor.humidity);
    bluetooth.print(",");
    bluetooth.println(sensor.temperature);
  }
    
}
