int pin = 4;

void setup() {
  pinMode(pin,OUTPUT);

}

void loop() {
  delay(1000);
  digitalWrite(pin,HIGH);
  delay(1000);
  digitalWrite(pin,LOW);
}
