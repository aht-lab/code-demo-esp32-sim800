//#include "SoftwareSerial.h"
//
//#define SIM800_RX_PIN 10
//#define SIM800_TX_PIN 11
//SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN);

#include <HardwareSerial.h>
#if defined(CONFIG_IDF_TARGET_ESP32) 
    #define mySerial Serial2
#elif defined(CONFIG_IDF_TARGET_ESP32S2)
    #define mySerial Serial1
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
   #define mySerial Serial2
#endif

void setup() 
{
  Serial.begin(115200);
  delay(500);
  #if defined(CONFIG_IDF_TARGET_ESP32) 
    mySerial.begin(115200);
 #elif defined(CONFIG_IDF_TARGET_ESP32S2)
    mySerial.begin(115200);
 #elif defined(CONFIG_IDF_TARGET_ESP32S3)
   mySerial.begin(115200, SERIAL_8N1, 18, 17);
 #endif
  delay(500);
  mySerial.println("ATI");
  delay(100);
  update_serial();
  mySerial.println("AT+CSQ");
  delay(100);
  update_serial();
  mySerial.println("AT+CIMI");
  delay(100);
  update_serial();
  pinMode(2,OUTPUT);digitalWrite(2,HIGH);
  sent_sms();
    
}
void loop() 
{     
  if (Serial.available()){
    char c = Serial.read();
    mySerial.write(c);
  }
 update_serial();
}

void update_serial()
{
    if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}

void sent_sms()
{
 mySerial.println("AT+CMGF=1");delay(500);
 mySerial.println("AT+CMGS=\"+84941732379\"");delay(500);
 mySerial.print("test sent sms from DevKit ESP32-SIM7600");delay(500);
 mySerial.write(26);delay(500);
}
