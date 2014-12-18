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
 1: SENSOR2: LDR
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
#include <stdlib.h> // dtostrf

// DHT
#define sensor_pin A0 //no ; here. Set equal to channel sensor is on

dht sensor;

const int rxBt = 2;
const int txBt = 3;
SoftwareSerial bluetooth(rxBt, txBt);

// SD
const int SD_chip_select = 10;
const int led_green = 8;
const int led_red = 9;
File dataFile;

// RTC
RTC_DS1307 RTC;

static void setup_bt(){
  pinMode(rxBt, INPUT);
  pinMode(txBt, OUTPUT);  
  bluetooth.begin(38400);
}

static void setup_led() {
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT); 
}

static void setup_rtc() {
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // uncomment it & upload to set the time, date and start run the RTC!
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }  
}

static int setup_sd(){
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SD_chip_select, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(SD_chip_select)) {
    Serial.println("Card failed, or not present");
    return 0;
  }
  Serial.println("card initialized.");
  return 1;
}

void setup(){
  //setup_bt(); 
  Serial.begin(38400);
  Serial.println("A");
  setup_led();
  Serial.println("B");
  setup_rtc();
  Serial.println("C");
  setup_sd();
  Serial.println("Bluetooth data logger");
}

static void toggle_led(int led)
{
  //  int s = digitalRead(led);
  //  s ^= 1;
  //  digitalWrite(led, s);
  digitalWrite(led, digitalRead(led) == 0 ? 1 : 0);
}

const String get_fmt_date()
{
  DateTime now = RTC.now();
  String d = String(now.year(), DEC);
  d += '/';
  d += String(now.month(), DEC);
  d += '/';
  d += String(now.day(), DEC);
  d += ' ';
  d += String(now.hour(), DEC);
  d += ':';
  d += String(now.minute(), DEC);
  d += ':';
  d += String(now.second(), DEC);
  return d;
}

const String get_sensor()
{
  String s;
  char tmp[20];
  tmp[0] = '\0';
  dtostrf(sensor.humidity, 2, 0, tmp);
  s = tmp;
  s += " ";
  tmp[0] = '\0';
  dtostrf(sensor.temperature, 2, 0, tmp);
  s += tmp;
  return s;
}

static int tick = 0;

void loop(){
  // sample sensor each second
  if (tick == 0 || !(tick % 100) ){
    sensor.read11(sensor_pin);
    String status = get_fmt_date();
    status += ' ';
    status += get_sensor();
    Serial.println(status);
    // open the dataFile. note that only one dataFile can be open at a time,
    // so you have to close this one before opening another.
    dataFile = SD.open("datalog.txt", FILE_WRITE);
    // if the dataFile is available, write to it:
    if (dataFile) {
      dataFile.println(status);
      dataFile.close();
    } 
    else {
      Serial.println("error writing datalog.txt");
    }
  } // tick

  delay(10);
  toggle_led(led_green);
  tick++; 
}


