//#include "SoftwareSerial.h"
//
//#define SIM800_RX_PIN 10
//#define SIM800_TX_PIN 11
//SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN);

#define MODEM_RX 16
#define MODEM_TX 17

#define mySerial Serial2


void setup() 
{
  Serial.begin(115200);
  delay(500);
  mySerial.begin(115200);
  delay(500);
}
void loop() 
{
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  if (Serial.available())
  {
    char c = Serial.read();
    Serial.write(c);
    mySerial.write(c);
  }

  
}
