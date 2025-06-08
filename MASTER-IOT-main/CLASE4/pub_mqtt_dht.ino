#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

DHT dht(25, DHT11);//DHT
WiFiClient espClient;
PubSubClient client(espClient);
char msg[30];
unsigned long t = 0;
void setup() {
  setup_wifi();
  dht.begin();//DHT
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
  if(millis()-t>= 30000){
    float temp = dht.readTemperature();//DHT
    float humi = dht.readHumidity();//DHT
    snprintf(msg,30,"%.2f,%.2f",temp,humi);
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
