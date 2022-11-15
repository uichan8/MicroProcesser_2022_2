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

//상수
RgbColor RED(30,0,0),BLUE(0,0,30),OFF(0,0,0);
//--------------------------------------------------------


//--------------------------main--------------------------
void setup() {
  lcd.begin(20, 4);
  strip.Begin();
  Serial.begin(9600);
  strip.SetPixelColor(0, OFF);
  strip.Show();
}

int state = 0;
void loop() {
  if(Serial.available()){
    int rcv_data = Serial.read();
    if (rcv_data >= 'a') rcv_data = rcv_data - 'a' + 'A';
    if (rcv_data == 'R'){
      if (state == 0) state = 1;
      else state = 0;
      }
    else if (rcv_data == 'E'){
      if (state == 1) state = 2;
      else if (state == 6) state = 7; //blue out
      else state = 0;
      }
    else if (rcv_data == 'D'){
      if (state == 2) state = 3; //red out
      else state = 0;
      }
    else if (rcv_data == 'B'){
      if (state == 0) state = 5;
      else state = 0;
      }
    else if (rcv_data == 'L'){
      if (state == 5) state = 6;
      else state = 0;
      }
    else state = 0;
    lcd.write(state + '0');
    }

  if(state == 3){
    strip.SetPixelColor(0, RED);
    strip.Show();
    delay(1000);
    strip.SetPixelColor(0, OFF);
    strip.Show();
    state = 0;
    }
  if(state == 7){
    strip.SetPixelColor(0, BLUE);
    strip.Show();
    delay(1000);
    strip.SetPixelColor(0, OFF);
    strip.Show();
    state = 0;
    }
  }
//--------------------------------------------------------
