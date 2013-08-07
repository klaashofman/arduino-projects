// wrapper for arduino
#include <LiquidCrystal.h>
#include <Servo.h>

static int debug = 1;

static void serial_setup()
{
  Serial.begin(9600);
}

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

static void lcd_setup()
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("lcd is setup");
  //lcd.autoscroll();
}

static void lcd_set(String d)
{
  // assume 1 lcd line per call
  static int row = 0;
  lcd.setCursor(0, row);
  lcd.print(d);
  row ^= 1;
  if (debug){
    Serial.print("lcd_set:");
    Serial.print(d);
    Serial.println(row, DEC);
  }
}

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
                
static void servo_setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

static void servo_set(int pos)
{
  myservo.write(pos);
  delay(15);      // waits 15ms for the servo to reach the position
  if (debug) { 
    Serial.print("servo_set:");
    Serial.println(pos, DEC);  
  }
}

const int led_pin = 13;

static void led_setup()
{
  pinMode(led_pin, OUTPUT);
}

static void led_set(int s)
{
  digitalWrite(led_pin, s);
  if (debug) {
    Serial.print("led_set:");
    Serial.println(s);
  }
}

void setup()
{
  serial_setup();
  lcd_setup();
  servo_setup();
  led_setup();
}

const int cmd_size = 128;
char cmd[cmd_size];

void loop()
{
  if (Serial.available())
  {
      if (Serial.readBytes(cmd, cmd_size) > 0)
      {
        switch (cmd[0])
        {
          // lcd control command 
          case 'L':
          {
            String lcd_d = String(cmd);
            lcd_d.trim();
            lcd_set(lcd_d.substring(1));
          }         
          break;
          
           // servo control command
           case 'S':
           {
             String servo_d = String(cmd);
             servo_d.trim();
             servo_d = servo_d.substring(1);              
             servo_set(servo_d.toInt());
           }
           break;
           
           // LED control command
           case 'E':
           {
             String led_d = String(cmd);
             led_d.trim();
             led_d = led_d.substring(1);
             led_set(led_d.toInt());
           }
        } // switch   
      } // serial read
            
  } // serial data avaliable
  
  
}
