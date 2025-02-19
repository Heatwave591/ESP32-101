#include "Arduino.h"
#include "WiFi.h"

#define int n

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop(){
  Serial.println("Scanning");
  n = WiFi.scanNetworks();
  Serial.printf("Found %d networks");

  for (int i = 0; i < n; ++i){
    Serial.printf("(%2d) RSSI: %2d, Channel: %2d, SSID: %s \n", i,  WiFi.SSID(i), WiFi.RSSI(i));
  }
  
  WiFi.scanDelete();
  delay(5000);
}