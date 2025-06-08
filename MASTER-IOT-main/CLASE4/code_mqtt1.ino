#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  setup_wifi();
  client.setServer("18.226.98.151",1883);
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
  client.publish("canalx","Hola desde ESP32");
  delay(30000);
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
