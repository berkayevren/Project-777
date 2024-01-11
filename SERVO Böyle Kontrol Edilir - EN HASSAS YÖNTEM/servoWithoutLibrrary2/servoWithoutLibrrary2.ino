
#define PIN_SERVO 3

#define HIZ_MAX 10 //MAX 40
#define HIZ_MIN 1
#define HIZLANMASINIRI HIZ_MAX*15

float angle;
int pwm;

void setup(){
  Serial.begin(9600);
  pinMode(PIN_SERVO, OUTPUT);
}

void loop (){
  dereceyeGit(180.0);
  delay(1000);
  dereceyeGit(0.0);
  delay(1000);
}

void dereceyeGit(float derece){
  uint16_t _newPwm = mapFloat(derece, 0, 180, 500, 2460);
  uint16_t _oldPwm = pwm;
  
  if(_newPwm > pwm){
    while(_newPwm > pwm) {
      
      // İlk kalkışta ivmeli hareket yapması sağlanıyor 
      if(pwm - _oldPwm < HIZLANMASINIRI){
        pwm += map((pwm - _oldPwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX);
        servoPulse(PIN_SERVO, pwm, map((pwm - _oldPwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX));
      }
      // Son duruşta ivmeli hareket yapması sağlanıyor 
      else if(_newPwm - pwm < HIZLANMASINIRI){
        pwm += map((_newPwm - pwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX);
        servoPulse(PIN_SERVO, pwm, map((_newPwm - pwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX));
      }
      else{
        pwm += HIZ_MAX;
        servoPulse(PIN_SERVO, pwm, HIZ_MAX);
      }
      
      Serial.println(pwm);
    }
  }
  else{
    while(_newPwm < pwm) {

      // Başlangıç anı
      if(_oldPwm - pwm < HIZLANMASINIRI){
        pwm -= map((_oldPwm - pwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX);
        servoPulse(PIN_SERVO, pwm, map((_oldPwm - pwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX));
      }
      // Bitiş anı
      else if(pwm - _newPwm  < HIZLANMASINIRI){
        pwm -= map((pwm - _newPwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX);
        servoPulse(PIN_SERVO, pwm, map((pwm - _newPwm), 1, HIZLANMASINIRI, HIZ_MIN, HIZ_MAX));
      }
      // Maksimum hız
      else{
        pwm -= HIZ_MAX;
        servoPulse(PIN_SERVO, pwm, HIZ_MAX);
      }
      
      Serial.println(pwm);
    }
  }
  
}

void servoPulse (int servo, int pwm, int newPwm){
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(servo, LOW);
  delayMicroseconds(map(pwm, 500, 2460, 2000, 100));
}

int mapFloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
