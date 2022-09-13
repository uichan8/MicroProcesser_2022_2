int pin = 4;

void setup() {
  pinMode(pin,OUTPUT);

}

void loop() {
  digitalWrite(pin,HIGH);
  delay(900);
  digitalWrite(pin,LOW);
  delay(100);
}
