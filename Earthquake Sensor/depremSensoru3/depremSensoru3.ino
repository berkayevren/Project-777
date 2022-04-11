#define PIN_SOUND   4
#define PIN_SENSOR  A0


unsigned long sound_frequency = 500000;
bool          sound_direction = 0;
unsigned long sound_timer     = millis();

bool          alarmStatus     = 0;

int           sensor_Old      = analogRead(PIN_SENSOR);
unsigned long sensor_timer    = millis();

unsigned long serial_timer    = millis();




void setup() {
  Serial.begin(9600);
  pinMode(PIN_SOUND, OUTPUT);
}

void loop() {
  sensor_Handle();
  alarm_Handle();
  serial_Handle();
}





void sensor_Handle(){
  if(sensor_Old - analogRead(PIN_SENSOR) > 50){
    alarmStatus = 1;
  }
  else {
    //alarmStatus = 0;
    //digitalWrite(PIN_SOUND, LOW);
  }
  if(sensor_timer + 10 < millis()){
    sensor_Old = analogRead(PIN_SENSOR);
    sensor_timer = millis();
  }
}

void alarm_Handle(){
  if(alarmStatus == 1){
    if(digitalRead(PIN_SOUND) == HIGH){
      if(sound_timer + (sound_frequency/100) < micros()){
        digitalWrite(PIN_SOUND, LOW);
        sound_timer = micros();
      }
    }
    else {
      if(sound_timer + (sound_frequency/100) < micros()){
        digitalWrite(PIN_SOUND, HIGH);
        sound_timer = micros();
      }
    }
  
    if(sound_frequency < 10000 || sound_frequency > 500000){
      sound_direction = !sound_direction;
    }
    
    if(sound_direction == 0){
      if(sound_frequency < 12000){
        sound_frequency -= 100;
      }
      else {
        sound_frequency -= 200;
      }
    }
    else {
      if(sound_frequency < 12000){
        sound_frequency += 100;
      }
      else {
        sound_frequency += 200;
      }
    }
  }
}

void serial_Handle(){
  if(serial_timer + 100 < millis()){
    Serial.println(analogRead(PIN_SENSOR));
    serial_timer = millis();
  }
}
