#include <Tinyfox.h>

Tiny<HardwareSerial,HardwareSerial> wisol(&Serial2,&Serial);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600,SERIAL_8N1,16,17);
}

void loop() {
  String id = wisol.ID();
  Serial.println(id);
  delay(10000);
}
