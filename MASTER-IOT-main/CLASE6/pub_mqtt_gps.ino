#include <WiFi.h>
#include <PubSubClient.h>
/************* GPS  ****************/
#include <TinyGPSPlus.h>
TinyGPSPlus gps;
/***********************************/
WiFiClient espClient;
PubSubClient client(espClient);
char msg[30];

void setup() {
  setup_wifi();
  client.setServer("18.224.38.115",1883);
  /************** SERIAL2 *******************/
  Serial2.begin(9600,SERIAL_8N1,16,17);
  /******************************************/
}

void reconnect(){
  if(client.connect("ESP32")){
    Serial.println("MQTT OK");
  }
}

void loop() {
  if(!client.connected()){
      reconnect();
    }
  /*******************************/
    if(Serial2.available()){
      char c = Serial2.read();
      if (gps.encode(c)){
          float lati = gps.location.lat();
          float longi = gps.location.lng();
          snprintf(msg,30,"%f,%f",lati,longi);
          client.publish("canalx",msg);
          delay(4000);
        }
   }
  }


void setup_wifi(){
  Serial.begin(9600);
  WiFi.begin("MOVISTAR_78A8","NS2ajtQJ7TtDt9m"); //SSID, PASS
  while(WiFi.status() != WL_CONNECTED){
    delay(300);
    Serial.print(".");
  }
  Serial.println( WiFi.localIP());
}
