//--------------------------init--------------------------
#include <LiquidCrystal.h>
int rs = 13, en = 12, d4 = 14, d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char color[5] = "red";
//--------------------------------------------------------



//--------------------------main--------------------------
void setup() {
  lcd.begin(20, 4);
  Serial.begin(9600); 
}

boolean q = true;
void loop() {
  if(q){
    Serial.write('\n');
    Serial.print("What color do you like?");
    q = false;
  }

  if(Serial.available()){
    delay(10);
    boolean is_ans = true;
    
    for(int i = 0; i < 3; i++){
      char rcv_data = Serial.read();
      if(color[i] != rcv_data) is_ans = false;
      }

    if(is_ans) lcd.print("red");
    else lcd.print("????");

    while(Serial.available())
      Serial.read();
    q = true;
  }

}
