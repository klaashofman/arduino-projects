#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define PIN_ENC_DATA  32
#define PIN_ENC_CLK   31
#define PIN_ENC_SW    30 

Encoder myEnc(PIN_ENC_DATA, PIN_ENC_CLK);

volatile int selected = 0;
const char *list[] = { "one", "two", "three" };

void setup() {
  /* setup uart */
  Serial.begin(9600);
  Serial.println("Simple encoder select test");

  /* setup encoder pins */
  //pinMode(PIN_ENC_DATA, INPUT_PULLUP);
  //pinMode(PIN_ENC_CLK, INPUT_PULLUP);
  //pinMode(PIN_ENC_SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_SW), isr_select, FALLING);
  
  /* setup lcd */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE); // othewise nothing on screen
  display.setCursor(0,0);
  
  display.println("line1");
  display.println("line2");
  display.println("line3");
  display.println("line4"); // int his mode upto 4 lines are printed

  display.display();

  update_list(0);
}

long oldPosition  = -999;

void update_list(int s){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE); // othewise nothing on screen
  display.setCursor(0,0);
  
  for (int i=0 ; i < 3 ; i++){
    if (i == s)
      display.setTextColor(BLACK, WHITE); // 'inverted' text
     else
      display.setTextColor(WHITE);
      
    display.println(list[i]);
  }
  display.display();
}


void loop() {
  // put your main code here, to run repeatedly:
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
    if (newPosition > oldPosition)
      selected++;
    else
      selected--;
    selected %= 3;
    update_list(selected);
  }
}

void isr_select(){
  // code when rotary knob is pressed
  Serial.print("selected: ");
  Serial.println(selected, DEC);
}

