#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

String uid;

char *ssid = "LUCAS FR";
char *pwd = "fateclegal";

char *mqttServer = "test.mosquitto.org";

char *ntpServer = "br.pool.ntp.org";
long gmtOffset = -3;
int daylight = 0;
time_t now;
struct tm timeinfo;

WiFiClient wclient;
PubSubClient mqttClient(wclient);

void connectWiFi()
{
  Serial.print("Conectando ");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado com sucesso, com o IP ");
  Serial.println(WiFi.localIP());
}

void connectMqtt()
{
  if (!mqttClient.connected())
  {
    if (mqttClient.connect(uid.c_str()))
    {
      Serial.println("Conectou no MQTT");
    }
    else
    {
      Serial.println("MQTT offline");
      delay(500);
    }
  }
}

void setup() {
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":", "");
  WiFi.begin(ssid, pwd);
  connectWiFi();
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Erro ao acessar o servidor NTP"); 
  }
  else
  {
    Serial.print("A hora agora eh ");
    Serial.println(time(&now));
  }
  mqttClient.setServer(mqttServer, 1883);
}

void sincronizaTempo(void)
{
  //Configurando o tempo
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Erro ao acessar o servidor NTP"); 
  }
  else
  {
    Serial.print("Configurado Data/Hora ");
    Serial.println(time(&now));
  }
}

void loop() {
  if (!mqttClient.connected())
  {
    connectMqtt();  
  }
  
  if ((time(&now) % 120) == 0)
  {
    sincronizaTempo();
    Serial.println("Enviar dados pelo MQTT");
    mqttClient.publish("fatec/lucas/","@oie");
  }
  
  mqttClient.loop();
}
