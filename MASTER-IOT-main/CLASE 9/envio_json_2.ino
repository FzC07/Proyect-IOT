#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);
char msg[30];
unsigned long t = 0;
void setup() {
  setup_wifi();
  client.setServer("18.224.38.115",1883);
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
  if(millis()-t>= 30000){
    int id = 1234;
    int temp = 14;
    int humi = 70;
    snprintf(msg,40,"{\"ID\": %d , \"Temp\": %d , \"Humi\":%d }",id,temp,humi);
    client.publish("canalx",msg);
    t = millis();
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
