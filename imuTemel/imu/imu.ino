/*
 * Not: Gyro titreşimlerden az etkileniyor
 *      Gyro zamanla kayma yapıyor
 *      ----
 *      İvme titreşimden çok etkileniyor
 *      İvme değerlerinin ortalamasını alınca değerler düzgün fakat gecikmeli oluyor
 */

#include<Wire.h>
 
const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;    // Sensörden gelen değerlerin kaydedileceği değişkenler

void setup(){
  Wire.begin();                         // I2C Wire haberleşmesi başlatılıyor
  Wire.beginTransmission(MPU);          // Haberleşmenin yapılacağı cihazın ID si haberleşme hattına gönderiliyor.
  Wire.write(0x6B);                     // Başlangıç ayarlamalarını yöneten yazmaca (register'a) erişildi. (Cihaz, uyku modu, sıcaklık takibi...)
  Wire.write(0x00);                        // Başlangıç ayarlamaları sıfırlandı.
  Wire.endTransmission(true);           // Ayarlar tamamlandı ve bağlantı kesildi. (Her okuma yapılacağında yeniden bağlanılır. Hat sürekli açık kalmaz.)

  Serial.begin(9600);
}
void loop(){
  verileriOku();
  
  Serial.print("ivmeX = "); Serial.print(AcX);
  Serial.print(" | ivmeY = "); Serial.print(AcY);
  Serial.print(" | ivmeZ = "); Serial.print(AcZ);
  Serial.print(" | Sicaklik = "); Serial.print(Tmp/340.00+36.53);  
  Serial.print(" | GyroX = "); Serial.print(GyX);
  Serial.print(" | GyroY = "); Serial.print(GyY);
  Serial.print(" | GyroZ = "); Serial.println(GyZ);
  
  delay(333);
}

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
}
