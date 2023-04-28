#define PIR 0
#define PIR_THRESH 10000
 
void setup(){
  Serial.begin(115200);
  pinMode(PIR,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(50);
}
 
void loop(){
  int duration;
  duration = pulseIn(PIR, HIGH);
  Serial.println(duration);
  if(duration > PIR_THRESH){
    Serial.println("Motion Detected");
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(25);                       
    digitalWrite(LED_BUILTIN, LOW);   
    delay(25);
  }
  else{
    Serial.println("No Motion");
    delay(50);
  }
}
