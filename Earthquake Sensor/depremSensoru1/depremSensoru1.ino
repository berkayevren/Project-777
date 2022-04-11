#define PIN_SENSOR  A0





void setup() {
  Serial.begin(9600);
}

void loop() {
  serial_Handle();
}





void serial_Handle(){
  Serial.println(analogRead(PIN_SENSOR));
  delay(10);
}
