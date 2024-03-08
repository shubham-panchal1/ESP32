#include <Preferences.h>

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("Initialize System"));
  int boardId = 18; 
  float param = 26.5;
  
  //init preference
  preferences.begin("myfile", false);
  //preferences.clear(); // remove all preferences in namespace myfile
  //preferences.remove("varname");// remove varname in the namespace


  preferences.putUInt("boardId", boardId);
  preferences.putFloat("param", param);

  unsigned int readId = preferences.getUInt("boardId", 0); // get boardId or if key doesn't exist set variable to 0
  Serial.print("Read Id = ");
  Serial.println(readId);
  
  float readParam = preferences.getFloat("param", 0); //
  Serial.print("Read param = ");
  Serial.println(readParam);
  
  preferences.end();
    
}

void loop() {}
