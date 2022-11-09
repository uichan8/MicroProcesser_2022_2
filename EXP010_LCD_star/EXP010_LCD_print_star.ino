#include <LiquidCrystal.h>
int rs = 13, en = 12, d4 = 14, d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(20, 4);
  Serial.begin(9600);
}

int count = 0;
void loop() {
  int  star = 2;
  lcd.setCursor((20-star)/2, 1);
  for(int i = 0; i < star; i++){
    if(count%2)lcd.write('*');
    else lcd.write(' ');
  }
    
  lcd.setCursor((20-star)/2, 2);
  for(int i = 0; i < star; i++){
    if(count%2)lcd.write(' ');
    else lcd.write('*');
  }

  delay(1000);
  count++;
}
