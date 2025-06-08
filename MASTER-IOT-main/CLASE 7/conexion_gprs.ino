#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>

#define SerialMon Serial
#define SerialAT Serial2
TinyGsm modem(SerialAT);  //TinyGsm modem(port_serie_sim)
void setup() {
  setup_gprs();
}

void loop() {

}

void setup_gprs(){
  SerialMon.begin(9600);
  SerialAT.begin(9600,SERIAL_8N1,16,17); //TinyGsmAutoBaud(SerialAT,9600,115200);
  delay(6000);
  SerialMon.println("Iniciando modem...");
  modem.restart();//Reinicia el modem
  String modemInfo = modem.getModemInfo(); //Versión del firmware
  SerialMon.println(modemInfo);
  if(!modem.waitForNetwork()){
    SerialMon.println("Error");
    delay(1000);
    return;
  }
  if(modem.isNetworkConnected()){
    SerialMon.println("Conexion a la Red");
  }
}
