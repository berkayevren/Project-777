// ---------------------- SERVO ---------------------- //
#define PIN_SERVO 3

#define HIZ_MAX 5 //MAX 40
#define HIZ_MIN 1
#define HIZLANMASINIRI HIZ_MAX*20

#define BUFFER_MAXLEN 200

int sonYazilanBufferSirasi = 0;
int32_t toplamBuffer = 0;

int16_t buffer_AcX[BUFFER_MAXLEN];

unsigned long pwmTimeOut = 0;

float angle;
int pwm=500;

// ----------------------- IMU ----------------------- //
#include<Wire.h>
const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

#include "Servo.h"
Servo myservo;

void setup(){
  //Serial.begin(9600);

  // ---------------------- SERVO ---------------------- //
  //pinMode(PIN_SERVO, OUTPUT);
  myservo.attach(3);

  // ----------------------- IMU ----------------------- //
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); /* MPU-6050 çalıştırıldı */
  Wire.endTransmission(true);

  for(int i = 0; i < BUFFER_MAXLEN+1; i++){
    buffer_AcX[BUFFER_MAXLEN] = 0;
  }
  
}

void loop (){
 
  verileriOku();
  //Serial.println(AcX);
  
  //analogWrite(PIN_SERVO, map(AcX, -16300, 16300, 40, 255)); //17700
  //servoPulse(PIN_SERVO, map(AcX, -16300, 16300, 500, 2460));
  myservo.write(map(AcX, -16300, 16300, 0, 180));
  //delay(5);
}


// ---------------------- SERVO ---------------------- //


void servoPulse (int servo, int pwm){
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(servo, LOW);
}

// ----------------------- IMU ----------------------- //
void verileriOku(){
  Wire.beginTransmission(MPU);
  /* I2C haberleşmesi yapılacak kart seçildi */
  Wire.write(0x3B); 
  /* 0x3B adresindeki register'a ulaşıldı */
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);
  /* 14 BYTE'lık veri istendi */
  
  AcX=Wire.read()<<8|Wire.read();   
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  Tmp=Wire.read()<<8|Wire.read(); 
  GyX=Wire.read()<<8|Wire.read(); 
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();
  /* 
  * Sırası ile okunan her iki byte birleştirilerek sırası ile değişkenlere yazdırıldı
  * Böylece IMU'dan tüm değerler okunmuş oldu
  * 0X3B adresi imu değerlerinden ilk sensörün değerine denk gelmektedir.
  * IMU'dan tüm değerlerin okunabilmesi için bu adresten başlandı
  */


/*
  int32_t _sum = 0;
  for(int i = 0; i < BUFFER_MAXLEN; i++){
    buffer_AcX[i] = buffer_AcX[i+1];
    _sum += int32_t(buffer_AcX[i]);
  }
  
  buffer_AcX[BUFFER_MAXLEN-1] = AcX;
  _sum += int32_t(buffer_AcX[BUFFER_MAXLEN-1]);

  AcX = int16_t(_sum / int32_t(BUFFER_MAXLEN));*/

  

  toplamBuffer -= buffer_AcX[sonYazilanBufferSirasi];
  buffer_AcX[sonYazilanBufferSirasi] = AcX;
  toplamBuffer += buffer_AcX[sonYazilanBufferSirasi];
  
  sonYazilanBufferSirasi++;
  if(sonYazilanBufferSirasi == BUFFER_MAXLEN)
    sonYazilanBufferSirasi = 0;
  //delay(1);
  AcX = toplamBuffer / BUFFER_MAXLEN;
}
