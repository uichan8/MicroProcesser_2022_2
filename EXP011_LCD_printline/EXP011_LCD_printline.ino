//--------------------------func--------------------------
#include <LiquidCrystal.h>
int rs = 13, en = 12, d4 = 14, d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int char_count = 0; //현재 줄에 몇글자가있는지
int line_count = 0; //현제 몇번 째 줄인지
//--------------------------------------------------------

//--------------------------func--------------------------
void clear_line(int line);
//--------------------------------------------------------

//--------------------------main--------------------------
void setup() {
  lcd.begin(20, 4);
  Serial.begin(9600);
}

void loop(){
    if(Serial.available()){
      char rcv_data = Serial.read();
      if(rcv_data == 10 || rcv_data == '*'){
        char_count = 0;
        line_count++;
      }
      
      else{
        if (char_count == 0){
          clear_line(line_count%4);
          lcd.write(rcv_data);
          char_count ++;
        }
        else if(char_count == 21 ||char_count == 41 ||char_count == 61){
            line_count++;
            char_count = 1;
            clear_line(line_count%4);
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
//--------------------------------------------------------

void clear_line(int line){
  lcd.setCursor(0,line);
  lcd.print("                    ");
  lcd.setCursor(0,line);
  }
  
