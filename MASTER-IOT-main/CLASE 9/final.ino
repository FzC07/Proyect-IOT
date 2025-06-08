#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "SPIFFS.h"

WiFiClientSecure espClient;
PubSubClient client(espClient);
//Credenciales WiFi
const char *ssid = "MOVISTAR_78A8";
const char *pass = "NS2ajtQJ7TtDt9m";
char msg[40];
unsigned long t = 0;
/***************************/
String Read_rootca;
String Read_cert;
String Read_privatekey;
/***************************/

void setup() {
  setup_wifi();
  /*************************************/
  if(!SPIFFS.begin(true)){
    Serial.println("Fallo al montar SPIFSS");
    return;
  }
  /******Root CA********************/
  File file1 = SPIFFS.open("/AmazonRootCA1.pem","r");
  if(!file1){
    Serial.println("Fallo al abrir el archivo");
    return;
  }
  while(file1.available()){
    Read_rootca = file1.readString();
  }
  /*******Cer*******************/
  File file2 = SPIFFS.open("/e9270000-certificate.pem.crt","r");
  if(!file2){
    Serial.println("Fallo al abrir el archivo");
    return;
  }
  while(file2.available()){
    Read_cert = file2.readString();
  }
  /*******Private Key****************/
  File file3 = SPIFFS.open("/e9270000-private.pem.key","r");
  if(!file3){
    Serial.println("Fallo al abrir el archivo");
    return;
  }
  while(file3.available()){
    Read_privatekey = file3.readString();
  }
  /**********************************************/
  char *pRead_rootca;
  pRead_rootca = (char*)malloc(sizeof(char)*(Read_rootca.length()+1));
  strcpy(pRead_rootca,Read_rootca.c_str());

  char *pRead_cert;
  pRead_cert = (char*)malloc(sizeof(char)*(Read_cert.length()+1));
  strcpy(pRead_cert,Read_cert.c_str());
  
  char *pRead_privatekey;
  pRead_privatekey = (char*)malloc(sizeof(char)*(Read_privatekey.length()+1));
  strcpy(pRead_privatekey,Read_privatekey.c_str());
  /**********************************************/
  Serial.println("===========================================================");
  Serial.write(pRead_rootca);
  Serial.println();
  Serial.println("===========================================================");
  Serial.write(pRead_cert);
  Serial.println();
  Serial.println("===========================================================");
  Serial.write(pRead_privatekey);
  Serial.println();   
  /*********Añadimos certificados****************/
  espClient.setCACert(pRead_rootca);
  espClient.setCertificate(pRead_cert);
  espClient.setPrivateKey(pRead_privatekey);
  /**********************************************/
  client.setServer("a1iejirb60zb0-ats.iot.us-east-2.amazonaws.com",8883);
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
  if(millis()-t > 20000){
    int id = 1;
    int temp = 25;
    int humi = 70;
    snprintf(msg,40,"{\"ID\":%d,\"Temp\":%d,\"Humi\":%d}",id,temp,humi);
    client.publish("canalx",msg);
    t = millis();
  }
}

void setup_wifi(){
  Serial.begin(9600);
  WiFi.begin(ssid,pass); //SSID, PASS
  while(WiFi.status() != WL_CONNECTED){
    delay(300);
    Serial.print(".");
  }
  Serial.println( WiFi.localIP());
}
