#include "SPIFFS.h"

void setup() {
  Serial.begin(115200);
  if(!SPIFFS.begin(true)){
    Serial.println("Fallo al montar SPIFSS");
    return;
  }
  File file = SPIFFS.open("/mensaje.txt");
  if(!file){
    Serial.println("Fallo al abrir el archivo");
    return;
  }
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

void loop() {

}
