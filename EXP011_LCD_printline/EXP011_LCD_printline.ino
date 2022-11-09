#include <LiquidCrystal.h>
int rs = 13, en = 12, d4 = 14, d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(20, 4);
  Serial.begin(9600);
}

int char_count = 0;
int line_count = 0;

void loop(){
    if(Serial.available()){
      char rcv_data = Serial.read();
      if(rcv_data == 10 || rcv_data == '*'){
        char_count = 0;
        line_count++;
      }
      
      else{
        if (char_count == 0){
          lcd.setCursor(0,line_count%4);
          lcd.print("                    ");
          lcd.setCursor(0,line_count%4);
          lcd.write(rcv_data);
          char_count ++;
        }
        else if(char_count == 21 ||char_count == 41 ||char_count == 61){
            line_count++;
            char_count = 1;
            lcd.setCursor(0,line_count%4);
            lcd.print("                    ");
            lcd.setCursor(0,line_count%4);
            lcd.write(rcv_data);
            char_count ++;
          }
        else{
          lcd.write(rcv_data);
          char_count ++;
          }
        }
      }
    }
  
