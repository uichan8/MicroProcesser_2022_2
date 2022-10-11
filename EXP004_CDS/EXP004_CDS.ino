//set pin
#define CDS      GPIO_NUM_38
#define LEDPIN 26

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
}

bool led_state = false;
void loop() {
  //read from pin
  unsigned int value = analogRead(CDS);

  //control led
  if (value < 300 && led_state == false){
    digitalWrite(LEDPIN,HIGH);
    led_state = true;
  }
  if(value > 450 && led_state == true){
    digitalWrite(LEDPIN,LOW);
    led_state = false;
  }


  //print
  Serial.print("value = ");
  Serial.println(value);

  //delay
  delay(100);
}
