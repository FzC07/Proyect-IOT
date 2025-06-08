#include <DHT.h>

DHT dht(25, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  Serial.print(temp);
  Serial.print("    ");
  Serial.println(humi);
}
