#include "MPU6050_DMP6.h"

// ---------------------------------------------------------------- //
//                      ÇOKLU SENSÖR KULLANIMI                      //
// ---------------------------------------------------------------- //
  // MPU6050 Sensörü için default I2C adresi 0x68 dir.
  
  // Eğer birden fazla MPU6050 sensörü çalıştıracaksanız;
  // Okumak istediğiniz sensörün AD0 pinini LOW
  // Diğer sensörlerin AD0 pinlerini HIGH yapmanız yeterlidir.
  
  // AD0 == LOW  ise 0x68 adresi geçerlidir.
  // AD0 == HIGH ise 0x69 adresi geçerlidir.
  
  // Biz 0x68 adresini okuduğumuz için
  // 0x69 adresine sahip sensörler beklemede kalırlar.
  
  // Aşağıdaki tabloda bir örnek ile durum açıklanmıştır.
  
  // --------------------- ÖRNEK ------------------------ //
  
  // |  Sensör 1  |  Sensör 2  |  Sensör 3  |  Sensör 4  |
  // |   AD0 = 0  |   AD0 = 1  |   AD0 = 1  |   AD0 = 1  |
  // |    0x68    |    0x69    |    0x69    |    0x69    |
  // |   Aktif    |  Bekliyor  |  Bekliyor  |  Bekliyor  |
  
  // ----------------------------------------------------- //
  
  // Eğer 0x68 adresine sahip olanlar yerine 0x69 adresine sahip olanları
  // okumak istersek "MPU6050_DMP6.h" kütüphanesinin içindeki;
  // "MPU6050 mpu;" yerine "MPU6050 mpu(0x69);" yazmamız gerekir.
  // Bu durumda 0x68 ler beklemede 0x69 Aktif sensör olur.





// Açısal değerleri seriport ekranından takip etmek için bunu kullanın
//#define OUTPUT_READABLE_YAWPITCHROLL

// Simulasyon için bunu kullanın
#define OUTPUT_TEAPOT







void setup() {
  Serial.begin(115200);
  MPU_init();
}





void loop() {
    if (!dmpReady) return;  // Eğer programlama başarısız olduysa hiçbir şey yapma.

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Son gelen veriyi oku
      
        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // EULER hesaplamalarına göre dereceleri hesapla
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_TEAPOT
            // Quaternion hesaplamalarından bulunan değerleri simulasyon için hazırla.

            teapotPacket[2] = fifoBuffer[0];
            teapotPacket[3] = fifoBuffer[1];
            teapotPacket[4] = fifoBuffer[4];
            teapotPacket[5] = fifoBuffer[5];
            teapotPacket[6] = fifoBuffer[8];
            teapotPacket[7] = fifoBuffer[9];
            teapotPacket[8] = fifoBuffer[12];
            teapotPacket[9] = fifoBuffer[13];
            
            Serial.write(teapotPacket, 14);
            teapotPacket[11]++; // Gönderilen paket sayısını sayar, 0xFF de başa döner.
        #endif

        // Bir işlem olduğunda dahili led yanık ise söner sönük ise yanar.
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}
