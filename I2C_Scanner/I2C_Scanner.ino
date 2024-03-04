/*
  https://www.cheers2engineering.com/guided-projects/advanced-grades-9-12/esp32-module/i2c-scanner
   I2CScanner - to locate I2C devices, and display I2C  if a device is connected ESP32
   ON Board SDA - 23, SCL - 19
  */
#include <Wire.h>
 void setup() {
  Wire.begin(23,19); //sda - 23, scl - 19
  Serial.begin(115200);
  Serial.println("I2C Scanner");
}
 
void loop() {
  byte error, address;
  int connectedDevices;
  Serial.println("Scanning...");
  connectedDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {  //device found
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      connectedDevices++;
    }
    else if (error==4) {
      Serial.print("Unknown error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (connectedDevices == 0) {
    Serial.println("No I2C devices found");
  }
  else {
    Serial.println("done");
  }
  delay(5000);          
}
