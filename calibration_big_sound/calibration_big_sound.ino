// calibration routine for 'red PCB sensors'

// Arduino pin numbers
// sound detector sensor
const int DO_pin = 2;
const int AO_pin = 0;

// buzzer
const int buz = 3;

void setup() {
  pinMode(DO_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available())
  {  
    analogWrite(buz, Serial.read() - '0');
  }
  
  static int last = 0;
  if ( last == 0 && digitalRead(DO_pin)){
    Serial.print("0 -> 1 \n");
    last = 1;
  }
  if ( last == 1 && !digitalRead(DO_pin))
  {
    Serial.print("1 -> 0 \n");
    last = 0;
  }
  /*
  Serial.print(digitalRead(DO_pin));
  Serial.print("-");
  Serial.println(analogRead(AO_pin));
  */
  delay(5);
}
