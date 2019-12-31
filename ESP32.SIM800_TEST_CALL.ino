//#include "SoftwareSerial.h"
//
//#define SIM800_RX_PIN 10
//#define SIM800_TX_PIN 11
//SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN);

#define MODEM_RX 16
#define MODEM_TX 17

#define mySerial Serial2

#define CALL_TIME 15*1000
#define CALL_TIMEOUT 10*1000
unsigned long lastTimeCall = 0;
unsigned long lastTimeHandup = 0;
bool isCalling = false;
bool firstCall = true;

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

  if (isCalling == false && (firstCall || millis() - lastTimeHandup > CALL_TIMEOUT)) {
    mySerial.println("ATD0799042802;");
    delay(100);
    lastTimeCall = millis();
    isCalling = true;
    firstCall = false;
  }
  
  if (isCalling == true && millis() - lastTimeCall > CALL_TIME) {
    mySerial.println("ATH");
    delay(100);
    lastTimeHandup = millis();
    isCalling = false;
  }
}
