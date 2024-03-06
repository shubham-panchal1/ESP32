#include <Wire.h>

void eepromSize() {
  Serial.println("Discovering eeprom sizes 0x50..0x57");
  uint8_t adr = 0x50, i;
  uint16_t size;
  char buf[64];
  while (adr < 0x58) {
    i = 0;
    size = 0x1000;  // Start at 4k
    i += sprintf_P(&buf[i], PSTR("0x%02X: "), adr);
    if (i2cReady(adr)) {  // EEPROM success
      uint8_t zeroByte;
      Wire.beginTransmission(adr);
      Wire.write((uint8_t)0);
      Wire.write((uint8_t)0);
      uint8_t err = Wire.endTransmission();
      if (err == 0) {  // no error
        err = Wire.requestFrom(adr, (uint8_t)1);
        if (err == 1) {  // got the value of the byte at address 0
          zeroByte = Wire.read();
          uint8_t saveByte, testByte;
          do {
            if (i2cReady(adr)) {
              Wire.beginTransmission(adr);
              Wire.write(highByte(size));
              Wire.write(lowByte(size));
              Wire.endTransmission();
              err = Wire.requestFrom(adr, (uint8_t)1);
              if (err == 1) {
                saveByte = Wire.read();
                Wire.beginTransmission(adr);
                Wire.write(highByte(size));
                Wire.write(lowByte(size));
                Wire.write((uint8_t)~zeroByte);
                err = Wire.endTransmission();
                if (err == 0) {
                  if (!i2cReady(adr)) {
                    i += sprintf_P(&buf[i], PSTR(" notReady.\n"));
                    Serial.print(buf);
                    adr++;
                    break;
                  }
                  Wire.beginTransmission(adr);
                  Wire.write((uint8_t)0);
                  Wire.write((uint8_t)0);
                  err = Wire.endTransmission();
                  if (err == 0) {
                    err = Wire.requestFrom(adr, (uint8_t)1);
                    if (err == 1) {
                      testByte = Wire.read();
                    } else {
                      testByte = ~zeroByte;
                    }
                  } else {
                    testByte = ~zeroByte;
                  }
                } else {
                  testByte = ~zeroByte;
                }
                if (!i2cReady(adr)) {
                  i += sprintf_P(&buf[i], PSTR(" notReady.\n"));
                  Serial.print(buf);
                  adr++;
                  break;
                }

                Wire.beginTransmission(adr);
                Wire.write(highByte(size));
                Wire.write(lowByte(size));
                Wire.write((uint8_t)saveByte);
                Wire.endTransmission();
              } else testByte = ~zeroByte;
            } else testByte = ~zeroByte;
            if (testByte == zeroByte) {
              size = size << 1;
            }
          } while ((testByte == zeroByte) && (size > 0));
          if (size == 0) {
            i += sprintf_P(&buf[i], PSTR("64k Bytes"));
          } else {
            i += sprintf_P(&buf[i], PSTR("%dk Bytes"), size / 1024);
          }
          if (!i2cReady(adr)) {
            i += sprintf_P(&buf[i], PSTR(" notReady3.\n"));
            Serial.print(buf);
            adr++;
            continue;
          }
          Wire.beginTransmission(adr);
          Wire.write((uint8_t)0);
          Wire.write((uint8_t)0);
          Wire.write(zeroByte);
          err = Wire.endTransmission();
        } else i += sprintf_P(&buf[i], PSTR("Read 0 Failure"));
      } else i += sprintf_P(&buf[i], PSTR("Write Adr 0 Failure"));

    } else i += sprintf_P(&buf[i], PSTR("Not Present."));
    Serial.println(buf);
    adr++;
  }
}

bool i2cReady(uint8_t adr) {
  uint32_t timeout = millis();
  bool ready = false;
  while ((millis() - timeout < 100) && (!ready)) {
    Wire.beginTransmission(adr);
    ready = (Wire.endTransmission() == 0);
  }
  return ready;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(23, 19);  //sda - 23, scl - 19
  Serial.println("EEPROM size");
  eepromSize();
}

void loop() {}
