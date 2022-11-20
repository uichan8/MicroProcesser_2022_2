//--------------------------init--------------------------
#include <LiquidCrystal.h>
#include <NeoPixelBus.h>

//lcd
int rs = 13, en = 12, d4 = 14, d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//led
const uint16_t PixelC = 4;
const uint8_t PixelPin = 20;
const uint8_t bright = 80;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelC,PixelPin);

//button
const int buttonPin = 15;

//상수
RgbColor RED(30,0,0),BLUE(0,0,30),GREEN(0,30,0),WHITE(30,30,30), OFF(0,0,0); //빨파초흰
//--------------------------------------------------------


//--------------------------func--------------------------
int UpdateStringState(int current_state); //문자열을 받고 string의 상태를 업데이트 합니다. 오류일시 -1을 반환.
void LEDOn(int code); //off100 RED101 BLE102 GRE103 WHI104
//--------------------------------------------------------



//--------------------------main--------------------------
void setup() {
  //장치 초기화
  lcd.begin(20, 4);
  strip.Begin();
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);

  //상태 초기화
  strip.SetPixelColor(0, OFF);
  strip.Show();
  
  for(int i = 0; i < 80; i++) lcd.write(' ');
  lcd.setCursor(0,0);
  Serial.println("--------------------------start--------------------------");
}

//global
int step_state = 0;
boolean debug_mode = false;

void loop() {
  //state_0 버튼 상태 탐지
  while(step_state == 0){
    if(debug_mode) {Serial.print("butten state:");Serial.println(digitalRead(buttonPin));}
    if(digitalRead(buttonPin)){
      strip.SetPixelColor(0, OFF);
      strip.Show();
      Serial.print("what color do you want?");
      step_state = 1;
      }
    }

  //state_1 키 입력 감지
  int string_state = 0;
  while(step_state == 1){
    if(debug_mode) {Serial.print("string_state:");Serial.println(string_state);}
    if(Serial.available()) string_state = UpdateStringState(string_state);
    if(string_state == -1){Serial.println("wrong color"); step_state = 0; break;}
    if(string_state >= 100) step_state = 2;
    }

  //state_2 led 켜기
  while(step_state == 2){
    LEDOn(string_state);
    step_state = 0;
    Serial.println("Done");
    }
}
//--------------------------------------------------------



//--------------------------fdef--------------------------
//off100 RED101 BLE102 GRE103 WHI104
//RED12 BLE34 GRE56 WHI78
int UpdateStringState(int current_state){
  int rcv_data = Serial.read();
  if (rcv_data >= 'a') rcv_data = rcv_data - 'a' + 'A';
  
  if (rcv_data == 'R'){
    if (current_state == 0) current_state = 1;
    else if (current_state == 5) current_state = 6;
    else current_state = -1;
    }
  else if (rcv_data == 'E'){
    if (current_state == 1) current_state = 2;
    else if (current_state == 4) current_state = 102; //blue out
    else if (current_state == 6) current_state = 103; //green out
    else current_state = -1;
    }
  else if (rcv_data == 'D'){
    if (current_state == 2) current_state = 101; //red out
    else current_state = -1;
    }
  else if (rcv_data == 'B'){
    if (current_state == 0) current_state = 3;
    else current_state = -1;
    }
  else if (rcv_data == 'L'){
    if (current_state == 3) current_state = 4;
    else current_state = -1;
    }
  else if (rcv_data == 'G'){
    if (current_state == 0) current_state = 5;
    else current_state = -1;
    }
  else if (rcv_data == 'W'){
    if (current_state == 0) current_state = 7;
    else current_state = -1;
    }
  else if (rcv_data == 'H'){
    if (current_state == 7) current_state = 8;
    else current_state = -1;
    }
  else if (rcv_data == 'I'){
    if (current_state == 8) current_state = 104;
    else current_state = -1;
    }
  else current_state = -1;
  return current_state;
  }
  
//off100 RED101 BLE102 GRE103 WHI104
  void LEDOn(int code){
    if(code == 100)strip.SetPixelColor(0, OFF);
    if(code == 101)strip.SetPixelColor(0, RED);
    if(code == 102)strip.SetPixelColor(0, BLUE);
    if(code == 103)strip.SetPixelColor(0, GREEN);
    if(code == 104)strip.SetPixelColor(0, WHITE);
    strip.Show();
    }

//--------------------------------------------------------
