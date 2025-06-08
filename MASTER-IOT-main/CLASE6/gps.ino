#include <TinyGPSPlus.h>
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600,SERIAL_8N1,16,17);
}

void loop() {
 if(Serial2.available()){
  char c = Serial2.read();
  if (gps.encode(c)){
    Serial.print(gps.location.lat(),6);
    Serial.print("   ");
    Serial.println(gps.location.lng(),6);
  }
 }
}
