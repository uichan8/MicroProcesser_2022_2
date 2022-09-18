//pin setup
int pin_1 = 25;
int pin_2 = 26;

void setup() {
  pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);

}

void loop() {
  digitalWrite(pin_1,HIGH);
  digitalWrite(pin_2,HIGH);
  delay(1000);
  digitalWrite(pin_1,LOW);
  digitalWrite(pin_2,LOW);
  delay(1000);

}
