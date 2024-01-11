#include <Servo.h>

Servo myservo;                              // Servo kütüphanesindeki Servo objesinin myservo ismiyle kullanılacağı belirtiliyor.
                                            // Birçok kart için 12 servo objesi oluşturulabiliyor.

int pos = 0;                                // Servo açısını tutan değişken

void setup() {
  myservo.attach(3);                        // Servonun 3.pine bağlı olduğu kütüphaneye bildiriliyor.
}

void loop() {
  
  myservo.write(45);                        // Açı değeri servoya gönderiliyor
  delay(1500);                              // Servonun açıya gitmesi bekleniyor
  myservo.write(135);                       // Açı değeri servoya gönderiliyor
  delay(1500);                              // Servonun açıya gitmesi bekleniyor
}

  
