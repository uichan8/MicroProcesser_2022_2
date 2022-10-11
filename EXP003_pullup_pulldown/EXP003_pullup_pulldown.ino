//env setup
#define LED_1 26 //high on
#define LED_2 14 //low on

#define SW_1 37
#define SW_2 36

void setup() {
 pinMode(LED_1,OUTPUT);
 pinMode(LED_2,OUTPUT);

 pinMode(SW_1,INPUT_PULLUP);
 pinMode(SW_2,INPUT_PULLUP);
}

void loop() {
  //Read Data
  boolean sw1_state = digitalRead(SW_1);
  boolean sw2_state = digitalRead(SW_2);
  
  //change LED state
  if(sw1_state) digitalWrite(LED_1,HIGH);
  else digitalWrite(LED_1,LOW);
  
  if(sw2_state) digitalWrite(LED_2,HIGH);
  else digitalWrite(LED_2,LOW);

  
}
