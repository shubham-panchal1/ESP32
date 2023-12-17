void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Touch: ");
  Serial.println(touchRead(4));  // get touch value on GPIO 4
  delay(1000);
}
