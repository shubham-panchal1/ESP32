/*
https://www.cheers2engineering.com/guided-projects/advanced-grades-9-12/esp32-module/sd-card
  SD Card Interface code for ESP32
  SPI Pins of ESP32 SD card as follows:
  CS    = 5;
  MOSI  = 23;
  MISO  = 19;
  SCK   = 18; 
*/

#include <SPI.h>
#include <SD.h>

File myFile;
const int CS = 5;
//WriteFile
void WriteFile(const char * path, const char * message){
  // open the file.
  // Note - only one file can be open at a time
  // close the opened file before opening another file
  myFile = SD.open(path, FILE_WRITE);
  // if the file open fine, then write to the file
  if (myFile) {
    myFile.println(message);
    myFile.close(); // close the file
    Serial.println("completed.");
  } 
  // if the file didn't open then print an error
  else {
    Serial.println("error opening file ");
    Serial.println(path);
  }
}

//ReadFile
void ReadFile(const char * path){
  // open the file for reading:
  myFile = SD.open(path);
  if (myFile) {
     Serial.printf("Reading file from %s\n", path);
     // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close(); // close the file
  } 
  else {
    // if the file didn't open then print an error
    Serial.println("error opening test.txt");
  }
}

void setup() {
  Serial.begin(9600);
  delay(500);
  while (!Serial) { ; }  // wait for serial port to connect
  Serial.println("Initializing SD card...");
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  WriteFile("/test.txt", "Cheers 2 Engineering - SD Card test");
  ReadFile("/test.txt");
}

void loop() {
  // nothing happens after setup
}
