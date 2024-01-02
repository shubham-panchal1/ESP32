/*
https://www.cheers2engineering.com/guided-projects/advanced-grades-9-12/esp32-module/wifi-connect
ESP 32 connecting to Wifi network
*/
#include "WiFi.h"

const char* ssid = "yourNetworkName"; //enter your wireless ssid
const char* password =  "yourNetworkPass"; //enter your wireless password

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");  
  // Print local IP address
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //show ip address on serial monitor
} 

void loop() {}
