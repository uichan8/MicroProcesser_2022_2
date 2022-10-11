//set pin
#define LM35  GPIO_NUM_38

//def func
float ValToTemp(int val){
  float temp = (val * 100 * 5)/4096.0 ;
  return temp;
}

void setup() {
  Serial.begin(9600);
}

double MEMORY = 0;
void loop() {
  //read from pin
  unsigned int value = analogRead(LM35);

  //convert to temp
  int temp = ValToTemp(value);

  //print
  if(MEMORY != temp){
    Serial.print("temp = ");
    Serial.print(temp);
    Serial.println("'C");
    MEMORY = temp;
  }

  //delay
  delay(2000);
}
