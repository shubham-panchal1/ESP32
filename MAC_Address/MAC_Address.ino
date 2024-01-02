/*
  https://www.cheers2engineering.com/guided-projects/advanced-grades-9-12/esp32-module/mac-address
   Read MAC Address of ESP32
  */
#include <WiFi.h>

void setup(){
  Serial.begin(115200);
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
} 
void loop(){ }
