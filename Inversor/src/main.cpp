#include <Arduino.h>
#include <WiFi.h>

#define SSID "ESP32"
#define PASS "123456"
#define PORT 1280

#define BAUDRATE 115200

#define IS_SERVER

#ifdef IS_SERVER

WiFiServer servidor(PORT);
WiFiClient cliente;

int cont=0;

void setup() 
{
  Serial.begin(BAUDRATE);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID,PASS);

  servidor.begin();

  Serial.println("Start Servidor");

}

void loop() 
{
  cliente = servidor.available();

  if(cliente)
  {
    Serial.println("Cliente");
    cliente.write(cont);
    Serial.println(cont);
    cont++;
    if (cont > 254) cont=0;
    if (cliente.available())
    {
        String req = "";
        while (cliente.available() > 0)//Armazena cada Byte (letra/char) na String para formar a mensagem recebida.
        {
            char z = cliente.read();
            req += z;
        }
        Serial.println(req);        
    }
  }
}
#endif