#include <WiFi.h>
#include "BluetoothSerial.h"
#define LED 2

String uid;
BluetoothSerial SerialBLE;
char c;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":", "");
  Serial.println(uid);
  SerialBLE.begin(uid);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SerialBLE.available())
  {
    c = SerialBLE.read();
    digitalWrite(LED, HIGH);
    Serial.print(c);
  }
  digitalWrite(LED, LOW);

}
