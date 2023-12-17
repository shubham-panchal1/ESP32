int LED_BUILTIN = 2;
void setup() {
  //esp32 dev module
pinMode (LED_BUILTIN, OUTPUT);
}
void loop() {
digitalWrite(LED_BUILTIN, HIGH); 	// turn on the LED
delay(1000); // wait for one second
digitalWrite(LED_BUILTIN, LOW); 	// turn off the LED
delay(500); // wait for half a second or 500 milliseconds
}
