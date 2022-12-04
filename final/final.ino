   //--------------------------init--------------------------
//bluetooth
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

//neopixel
#include <NeoPixelBus.h>
const int neo_pin = 2;
const int neo_count = 4;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(neo_count,neo_pin);

const int bright = 100;
RgbColor RED(bright,0,0);
RgbColor YELLOW(bright*0.5,bright*0.5,0);
RgbColor WHITE(bright*0.33,bright*0.33,bright*0.33);
RgbColor High(255,255,255);
RgbColor OFF(0,0,0);

//HC-SR04P
const int trig_pin = 5;
const int echo_pin = 20;

//Moter
#define PWM_CH1 1
#define PWM_CH2 2
#define freq 5000
#define res  12

const int in_1 = 21;
const int en_1 = 22;
const int in_2 = 19;
const int in_3 = 4;
const int en_2 = 8;
const int in_4 = 7;          

//line tracker
const int line_1 = 39;
const int line_2 = 34;
const int line_3 = 35;
const int line_4 = 32;

#define LINE_1  GPIO_NUM_39
#define LINE_2  GPIO_NUM_34
#define LINE_3  GPIO_NUM_35
#define LINE_4  GPIO_NUM_32
                                                         
//--------------------------------------------------------



//--------------------------func--------------------------
bool check_distance(void);
void SetWheelSpeed(float left, float right);
void hazard_light();
void TurnRight();
void TurnLeft();
void forward();
void stop_();
void light_off();
//--------------------------------------------------------



//--------------------------main--------------------------
void setup() {
  //Serial moniter
  Serial.begin(9600);
  
  //bluetooth
  SerialBT.begin("uichan_20172099"); 
  Serial.println("The device started, now you can pair it with bluetooth!");
  
  //neopixel
  strip.Begin();

  //HC-SR04P
  pinMode(trig_pin, OUTPUT);   
  pinMode(echo_pin, INPUT);

  //moter
  ledcSetup(PWM_CH1, freq, res);//right
  ledcAttachPin(en_1,PWM_CH1);
  pinMode(in_1, OUTPUT); 
  pinMode(in_2, OUTPUT);
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);

  ledcSetup(PWM_CH2, freq, res);//left
  ledcAttachPin(en_2,PWM_CH2);
  pinMode(in_3, OUTPUT); 
  pinMode(in_4, OUTPUT);
  digitalWrite(in_3,LOW);
  digitalWrite(in_4,HIGH);

//  digitalWrite(in_1,HIGH);
//  digitalWrite(in_2,LOW);
//  digitalWrite(in_3,LOW);
//  digitalWrite(in_4,HIGH);
  
  stop_();
   
  strip.SetPixelColor(0, OFF);//오후
  strip.SetPixelColor(1, OFF);//왼후
  strip.SetPixelColor(2, OFF);//오전
  strip.SetPixelColor(3, OFF);//왼전
  strip.Show();

  //line tracker
  
}

int butten_state = 0;
bool led_state = 0;
bool forced_stop = 0;
char moter_steate = 's';
unsigned long past_time = millis();
unsigned long led_timer = 0;
RgbColor fr = OFF;
RgbColor fl = OFF;
RgbColor br = OFF;
RgbColor bl = OFF;
int line_mode = 1; // 1 -> track line

void loop() {
  unsigned long timer = millis();

  //led

  led_timer += (timer - past_time);
  if (led_timer > 500){
    led_timer = 0;
    if (led_state){
      led_state = 0;
      strip.SetPixelColor(0, OFF);//오후
      strip.SetPixelColor(1, OFF);//왼후
      strip.SetPixelColor(2, OFF);//오전
      strip.SetPixelColor(3, OFF);//왼전
      strip.Show();
      }
    else{
      strip.SetPixelColor(0, fr);//오후
      strip.SetPixelColor(1, fl);//왼후
      strip.SetPixelColor(2, br);//오전
      strip.SetPixelColor(3, bl);//왼전
      strip.Show();
      led_state = 1;
    }
    }

  if(check_distance()){
    forced_stop = 1;
    stop_();
    light_off();
    hazard_light();
    line_mode = 0;
  }
  if(forced_stop && !check_distance()){
    line_mode = 1;
    forced_stop = 0;
    forward();
    }
  
   if (SerialBT.available()){
    char rcv_data = SerialBT.read();
    if (rcv_data == 's') stop_();
    if (rcv_data == 'w') forward();
    if (rcv_data == 'd') TurnRight();
    if (rcv_data == 'a') TurnLeft();
    if (rcv_data == 'm') line_mode = abs(line_mode - 1);
   }

   int bright = 100;
   if(line_mode){
    if (analogRead(LINE_1) > bright and analogRead(LINE_2) > bright and analogRead(LINE_3) > bright and analogRead(LINE_4) > bright)forward();
    else if (analogRead(LINE_1) < bright and analogRead(LINE_2) < bright and analogRead(LINE_3) < bright and analogRead(LINE_4) < bright)forward();
    else if (analogRead(LINE_2) < bright and analogRead(LINE_3) < bright)forward();
    else if (analogRead(LINE_1) < bright)TurnLeft();
    else if (analogRead(LINE_4) < bright)TurnRight();
    else if (analogRead(LINE_2) < bright){
      forward();
      SetWheelSpeed(0.6,0.4);
    }
    else if (analogRead(LINE_3) < bright){
      forward();
      SetWheelSpeed(0.4,0.6);
    }
    else forward();
    }
    
   past_time = timer;
}
//--------------------------------------------------------




//--------------------------func--------------------------
void UpdateWheelSpeed(int left, int right);
void UpdateLightState(int left, int right);

//거리측정
bool check_distance(void){
  long duration, distance; 
  digitalWrite(trig_pin, LOW);            
  delayMicroseconds(10);                  
  digitalWrite(trig_pin, HIGH);            
  delayMicroseconds(10);                  
  digitalWrite(trig_pin, LOW);             
  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 170.0 / 1000;
  return distance < 200 and distance != 0;
}

//바퀴 속도 설정
void SetWheelSpeed(float left, float right){
  if (left > 0){
    digitalWrite(in_1,HIGH);
    digitalWrite(in_2,LOW);
  }   
  if (right > 0){
    digitalWrite(in_3,LOW);
    digitalWrite(in_4,HIGH);
    }
  if (left < 0){
    digitalWrite(in_1,LOW);
    digitalWrite(in_2,HIGH);
  }   
  if (right < 0){
    digitalWrite(in_3,HIGH);
    digitalWrite(in_4,LOW);
    }
    
  ledcWrite(PWM_CH1,pow(2,res)*left);
  ledcWrite(PWM_CH2,pow(2,res)*right);
  }
  
//우선회
void TurnRight(){
  if(moter_steate != 'r'){
    moter_steate = 'r';;
    SetWheelSpeed(0.0,0.55);
    fr = YELLOW;
    br = YELLOW;
  }
}
  
//좌선회
void TurnLeft(){
  if(moter_steate != 'l'){
    moter_steate = 'l';
    light_off();
    SetWheelSpeed(0.55,0.0);
    fl = YELLOW;
    bl = YELLOW;
  }
  }
  
//직진
void forward(){
  if(moter_steate != 'f'){
    moter_steate = 'f';
    digitalWrite(in_1,HIGH);
    digitalWrite(in_2,LOW);
    digitalWrite(in_3,LOW);
    digitalWrite(in_4,HIGH);
    SetWheelSpeed(0.5,0.5);
    
    light_off();
  }
  }
  
//정지
void stop_(){
  if(moter_steate != 's'){
    moter_steate = 's';
    SetWheelSpeed(0,0);
  }
}

//비상등
void hazard_light(){
    fr = YELLOW;
    fl = YELLOW;
    br = YELLOW;
    bl = YELLOW;
  }

 //전원끔
 void light_off(){
    fr = OFF;
    fl = OFF;
    br = OFF;
    bl = OFF;
  }

 //깜빡이
 
//--------------------------------------------------------
