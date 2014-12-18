#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

const int pinSensor = A0;

const int wait = 100; // In milliseconds
const int length = 8;

const int maxSens = 255;
const int minSens = 0;

void setup() {
  matrix.setIntensity(4); // Set brightness between 0 and 15
}

void loop() {
 static int step = 0;
 if ((++step % length) == 0) {
   step = 0;
 }
 int val = ( (maxSens-minSens) / (analogRead(pinSensor) + 1) ) * length;
 matrix.drawLine(step, 0, step, length - val, 0);
 matrix.write();
 delay(wait);
}

