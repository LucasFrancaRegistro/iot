#include <WiFi.h>
#include "time.h"
String uid;
char *ssid = "LUCAS FR";
char *pwd = "fateclegal";

char *ntpServer = "br.pool.ntp.org";
long gmtOffset = -3;
int daylight = 0;
time_t now;
struct tm timeinfo;

void connectWifi() {
  Serial.print("conectando ");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("conectado com sucesso, com o IP ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":", "");
  WiFi.begin(ssid, pwd);
  connectWifi();
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo)) {
    Serial.println(" erro ao acessar o servidor ntp");
  } else {
    Serial.print("a hora eh ");
    Serial.println(time(&now));
  }
}
int jaentrei = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (((time(&now) % 60) == 0) && (!jaentrei)){
    jaentrei = 1;
    Serial.print("hora de transmitir ");
    Serial.println(time(&now));
  }
  else {
    jaentrei = 0;
  }
  
}
