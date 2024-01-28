/*

 * ESP32 LED Blink Example

 * Board WEMOS LOLIN32 LITE

 */

void setup() {

  // Set pin mode

  pinMode(LED_BUILTIN,OUTPUT);

}


void loop() {

  delay(500);

  digitalWrite(LED_BUILTIN,HIGH);

  delay(500);

  digitalWrite(LED_BUILTIN,LOW);

}
