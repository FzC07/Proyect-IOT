#include <Tinyfox.h>

Tiny<HardwareSerial,HardwareSerial> wisol(&Serial2,&Serial);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600,SERIAL_8N1,16,17);
}

void loop() {
  uint16_t temp = 24;
  uint16_t humi = 70;
  char msg[12] = "";
  sprintf(msg,"%04lx%04lx",temp,humi);
  wisol.SEND(msg);
  delay(120000);
}
