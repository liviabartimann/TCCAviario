//------------------------------------------------------------------------------------
// Libraries Needed For This Project
//------------------------------------------------------------------------------------
#include <EEPROM.h>         // To Be Able To Store & Read Data Between Power Off
#include <ESP8266WiFi.h>    // The Basic Function Of The ESP NOD MCU
#define ID "1"
//------------------------------------------------------------------------------------
// WIFI Authentication Variables
//------------------------------------------------------------------------------------
char*         ssid;           // Wifi Name
char*         password;       // Wifi Password
//------------------------------------------------------------------------------------
// WIFI Module Role & Port
//------------------------------------------------------------------------------------
/* This WIFI Module Code Works As A Client
   That Will Connect To A Server WIFI Modul With (IP ADDress 192.168.4.1)
*/
int contador = 1;
int             ESPServerPort  = 80;
IPAddress       ESPServer(192, 168, 4, 1);
WiFiClient      ESPClient;
//====================================================================================
void setup()
{
  // Setting The Serial Port ----------------------------------------------
  Serial.begin(9600);         // Computer Communication
  // Print Message Of I/O Setting Progress --------------------------------
  Serial.println("\nI/O Carregando...");
  WiFi.mode(WIFI_AP);              // To Avoid Broadcasting An SSID
  WiFi.begin("AVIARIO", "");      // The SSID That We Want To Connect To
  // Printing Message For User That Connetion Is On Process ---------------
  Serial.println("!--- Conectando ao WIFI " + WiFi.SSID() + " ---!");
  Serial.println("!--CLIENTE CONECTADO --!");
  // Printing IP Address --------------------------------------------------
  Serial.println("CONECTADO EM      : " + String(WiFi.SSID()));
  Serial.println("FORÇA DO SINAL   : " + String(WiFi.RSSI()) + " dBm");
  Serial.print  ("IP DO SERVIDOR : ");
  Serial.println(ESPServer);
  Serial.print  ("PORTA DO SERVIDOR   : ");
  Serial.println(ESPServerPort);
  // Printing MAC Address
  Serial.print  ("ENDEREÇO MAC DO DISPOSITIVO : ");
  Serial.println(String(WiFi.macAddress()));
  // Printing IP Address
  Serial.print  ("IP DO DISPOSITIVO : ");
  Serial.println(WiFi.localIP());
}
//====================================================================================
void loop()
{
  ESPRequest();
}
//====================================================================================
void ESPRequest()
{
  // First Make Sure You Got Disconnected
  ESPClient.stop();
  // If Sucessfully Connected Send Connection Message
  if (ESPClient.connect(ESPServer, ESPServerPort))
  {
    Serial.print (contador);
    Serial.print (String(ID)+";"+getTemperatura()+";"+getUmidade()+";"+getPressao()+";"+getLuminosidade()+";"+getGas());
    
    ESPClient.print (String(ID)+";"+getTemperatura()+";"+getUmidade()+";"+getPressao()+";"+getLuminosidade()+";"+getGas());
    contador++;
    delay(5000);
  }
}
String getTemperatura(){
	return "30";
}
String getUmidade(){
	return "80";
}
String getPressao(){
	return "800";
}
String getLuminosidade(){
	return "300";
}
String getGas(){
	return "500";
}
