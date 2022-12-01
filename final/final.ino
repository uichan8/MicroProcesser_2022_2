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
const int line_r = 32;
const int line_l = 33; 
                                                         
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
  }
  if(forced_stop && !check_distance()){
  
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
//   if(line_mode){
//    serial.print();
//    }
    
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
  ledcWrite(PWM_CH1,pow(2,res)*left);
  ledcWrite(PWM_CH2,pow(2,res)*right);
  }
  
//우선회
void TurnRight(){
  light_off();
  SetWheelSpeed(0.8,0.8);
  delay(10);
  SetWheelSpeed(0.8,0.4);
  fr = YELLOW;
  br = YELLOW;
  }
  
//좌선회
void TurnLeft(){
  light_off();
  SetWheelSpeed(0.8,0.8);
  delay(10);
  SetWheelSpeed(0.4,0.8);
  fl = YELLOW;
  bl = YELLOW;
  }
  
//직진
void forward(){
  SetWheelSpeed(0.7,0.7);
  light_off();
  }
  
//정지
void stop_(){
  SetWheelSpeed(0,0);
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
