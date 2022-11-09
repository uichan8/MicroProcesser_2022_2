#define TRIG 26    
#define ECHO 27   
#define LED  25 

float check_distance(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);          
  pinMode(TRIG, OUTPUT);   
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  long distance; 
  distance = check_distance();
  Serial.println(distance);
  int b_time = distance; 
  if (distance < 30) digitalWrite(LED,HIGH);
  else if (distance > 300) digitalWrite(LED,LOW);
  else{
    digitalWrite(LED,HIGH);
    delay(b_time);
    digitalWrite(LED,LOW);
    delay(b_time);
  }
  

}

float check_distance(void){
  long duration, distance; 
  digitalWrite(TRIG, LOW);            
  delayMicroseconds(10);                  
  digitalWrite(TRIG, HIGH);            
  delayMicroseconds(10);                  
  digitalWrite(TRIG, LOW);             
  duration = pulseIn(ECHO, HIGH);   
  distance = duration * 170.0 / 1000;
  return distance;
}
