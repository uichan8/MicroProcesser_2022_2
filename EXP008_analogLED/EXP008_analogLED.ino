#define LED_PIN   25
#define INPUT_PIN 38
#define PWM_CH    0    // 0~15

#define freq 5000
#define res  12

void setup() {  
  ledcSetup(PWM_CH, freq, res);   // PWM 채널을 하나 고른 뒤에 주파수와 해상도를 설정합니다.
  ledcAttachPin(LED_PIN,PWM_CH);  // PWM 채널을 LED핀에 연결시켜 줍니다.
  Serial.begin(9600);
}

void loop() {
  unsigned int value = analogRead(INPUT_PIN);
  float duty = value/(pow(2,12));              // duty = 가변저항 현재 값 / 가변저항 최댓값
  int level = pow(2,res)*duty                  // LED에 써야 하는 값 = PWM_level
  ledcWrite(PWM_CH,level);     
  Serial.println(level));
}
