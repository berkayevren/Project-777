#define PIN_SENSOR  A0


int           sensor_Old    = analogRead(PIN_SENSOR);
unsigned long sensor_timer  = millis();

unsigned long serial_timer  = millis();





void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  sensor_Handle();
  serial_Handle();
}





void sensor_Handle(){
  if(sensor_Old - analogRead(PIN_SENSOR) > 50){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  
  if(sensor_timer + 10 < millis()){
    sensor_Old = analogRead(PIN_SENSOR);
    sensor_timer = millis();
  }
}

void serial_Handle(){
  if(serial_timer + 100 < millis()){
    Serial.println(analogRead(PIN_SENSOR));
    serial_timer = millis();
  }
}
