#include <WiFi.h>

IPAddress local_ip(192,168,1,140);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(9600);
  WiFi.config(local_ip,gateway,subnet);
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

//bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
//IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
