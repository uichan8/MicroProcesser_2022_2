//set pin
#define LM35       GPIO_NUM_37
#define CDS        GPIO_NUM_38
#define LEDPIN     26
#define BUTTENPIN  22

//init
double temp_mem          = 0;
bool   led_state         = false;
int    past_butten_state = 0;

unsigned long past_time = millis();


//func
void Mode_A(); //온도변화 감지 하는 함수
void Mode_B(); //CDS 동작하는 친구

//______________________main_________________________
void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTENPIN, INPUT);
}

void loop() {
  int butten_state = digitalRead(BUTTENPIN);
  Serial.println("Mode_A");
  while(true){
    Mode_A();
    butten_state = digitalRead(BUTTENPIN);
    if(past_butten_state == 0 && butten_state == 1) break;
    past_butten_state = butten_state;
    }
    delay(200);
    Serial.println("Mode_B");
  while(true){
    Mode_B();
    digitalRead(BUTTENPIN);
    butten_state = digitalRead(BUTTENPIN);
    if(past_butten_state == 0 && butten_state == 1) break;
    past_butten_state = butten_state;
    }
    delay(200);
}
//______________________main_________________________

//def func
float ValToTemp(int val){
  float temp = (val * 100 * 5)/4096.0 ;
  return temp;
}

//온도변화 감지 하는 함수
void Mode_A(){ 
  //read from pin
  unsigned int value = analogRead(LM35);

  //convert to temp
  int temp = ValToTemp(value);
  //print
  if(temp_mem != temp && millis() - past_time > 1000){
    Serial.print("temp = "); 
    Serial.print(temp);
    Serial.println("'C");
    temp_mem = temp;
    past_time = millis();
  }

  //delay
  

  //debug
  //Serial.print("temp = ");
  //Serial.print(temp);
  //Serial.println("'C");
}

//CDS 동작하는 친구
void Mode_B(){
    //read from pin
  unsigned int value = analogRead(CDS);

  //control led
  if (value < 750 && led_state == false){
    digitalWrite(LEDPIN,HIGH);
    led_state = true;
  }
  if(value > 500 && led_state == true){
    digitalWrite(LEDPIN,LOW);
    led_state = false;
  }

  //print
  Serial.print("value = ");
  Serial.println(value);

  //delay
  delay(100);
}
