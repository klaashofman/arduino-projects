// calibration routine for 'red PCB sensors'

// Arduino pin numbers
const int DO_pin = 2;
const int AO_pin = 0;

void setup() {
  pinMode(DO_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(digitalRead(DO_pin));
  Serial.print("-");
  Serial.println(analogRead(AO_pin));
  delay(5);
}
