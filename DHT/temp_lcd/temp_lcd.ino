#include <dht.h>
// include the library code:
#include <LiquidCrystal.h>

#define dht_dpin A1 //no ; here. Set equal to channel sensor is on

dht DHT;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup(){
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  
  Serial.begin(9600);
  delay(300);//Let system settle
  Serial.println("Humidity and temperature\n\n");
  delay(700);//Wait rest of 1000ms recommended delay before
  //accessing sensor
}//end "setup()"

void loop(){
  //This is the "heart" of the program.
  DHT.read11(dht_dpin);

    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
  delay(800);//Don't try to access too frequently... in theory
  //should be once per two seconds, fastest,
  //but seems to work after 0.8 second.
  lcd.home();
  lcd.print("humidity=");
  lcd.print(DHT.humidity);
  lcd.print("% ");
  lcd.setCursor(0,2);
    lcd.print("temp=");
    lcd.print(DHT.temperature); 
    lcd.println("C     ");
  
  
}// end loop()
