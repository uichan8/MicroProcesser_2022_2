#define LED_PIN   25
#define INPUT_PIN 38
#define PWM_CH    0

#define freq 5000
#define res  12

void setup() {  
  ledcSetup(PWM_CH, freq, res);
  ledcAttachPin(LED_PIN,PWM_CH);
  Serial.begin(9600);
}

void loop() {
  unsigned int value = analogRead(INPUT_PIN);
  float duty = value/(pow(2,12));
  ledcWrite(PWM_CH, int(pow(2,res)*duty));  
  Serial.println(int(pow(2,res)*duty));
}
