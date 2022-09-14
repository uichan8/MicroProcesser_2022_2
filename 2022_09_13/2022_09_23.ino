//setup
int pin  = 25;

void setup() {
 //init
 pinMode(pin,OUTPUT);
}

void loop() {
   digitalWrite(pin,HIGH);
   delay(100);
   digitalWrite(pin,LOW);
   delay(100);
}
