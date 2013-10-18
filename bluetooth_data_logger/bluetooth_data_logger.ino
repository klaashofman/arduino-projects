/*
Arduino pins
Digital:
0: serial RX 
1: serial TX
2: bluetooth RX
3: bluetooth TX
4:  
5: ~PWM
6: ~PWM
7:
8: SDD shielf LED1
9: SDD shield LED2
10: ~PWM: SD CS
11: ~PWM: SD MOSI
12: SD MISO
13: SD CLK
Analog
0: SENSOR1: temp
1: SENSOR2: 
2: SENSOR3
3: SENSOR4:
4: SDA/SCL RTC
5: SDA/SCL RTC
*/

#include <Wire.h>
#include <RTClib.h>
#include <dht.h>
#include <SoftwareSerial.h>
#include <SD.h>

// DHT
#define sensor_pin A0 //no ; here. Set equal to channel sensor is on

dht sensor;

// Bluetooth
#define rxBt 2
#define txBt 3

SoftwareSerial bluetooth(rxBt, txBt);

// SD
const int SD_chip_select = 10;
const int led_status1 = 8;
const int led_status2 = 9;

// RTC
RTC_DS1307 RTC;

void setup(){
   // bluetooth
   pinMode(rxBt, INPUT);
   pinMode(txBt, OUTPUT);  
   bluetooth.begin(38400);
   // usb port
   Serial.begin(38400);
   // led
   pinMode(led_status1, OUTPUT);
   pinMode(led_status2, OUTPUT);
   // rtc
   Wire.begin();
   RTC.begin();
   if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // uncomment it & upload to set the time, date and start run the RTC!
    RTC.adjust(DateTime(__DATE__, __TIME__));
   }
   // SD
   // make sure that the default chip select pin is set to
   // output, even if you don't use it:
    pinMode(SD_chip_select, OUTPUT);
    // see if the card is present and can be initialized:
    if (!SD.begin(SD_chip_select)) {
      Serial.println("Card failed, or not present");
      // don't do anything more:
      return;
    }
    Serial.println("card initialized.");
   
}

void loop(){
  sensor.read11(sensor_pin);
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
    DateTime now = RTC.now();
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(' ');
    dataFile.print(now.hour(), DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.print(':');
    dataFile.print(now.second(), DEC);
    dataFile.print(' ');
    dataFile.print(sensor.humidity);
    dataFile.print(",");
    dataFile.println(sensor.temperature);
    dataFile.close();
    
    digitalWrite(led_status2, 1);
    delay(100);
    digitalWrite(led_status2, 0);    
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
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
    digitalWrite(led_status1, 1);
  } 
  if (cmd == "LED0"){
    digitalWrite(led_status1, 0);
  }
  if (cmd == "SENS"){
    bluetooth.print(sensor.humidity);
    bluetooth.print(",");
    bluetooth.println(sensor.temperature);
  }
 digitalWrite(led_status1, 1);
 delay(100);
 digitalWrite(led_status1, 0);      
}

