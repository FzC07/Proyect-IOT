#include <WiFi.h>

void setup() {
  Serial.begin(9600);
  WiFi.begin("MOVISTAR_78A8", "NS2ajtQJ7TtDt9m"); //inserta credenciales

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.gatewayIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
