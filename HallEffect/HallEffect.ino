int value = 0;
void setup() {
  // put your setup code here, to run once
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
value = hallRead();
Serial.println("Hall Sensor - " + String(value));
delay(100);
}
