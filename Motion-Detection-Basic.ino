/*
The given code is an example of how to use a PIR sensor with an Arduino board. 
It starts by defining the pin number of the PIR sensor and the threshold value for detecting motion. 
In the setup function, the serial communication is initialized, and the pins are defined as inputs and outputs. 
Then, in the loop function, the duration of the high signal is measured using the pulseIn function. 
If the duration is greater than the threshold value, it indicates that motion has been detected, and the built-in 
LED is turned on for 25 milliseconds and then turned off for another 25 milliseconds. 
The serial monitor also displays a message indicating that motion has been detected. If the duration is less than the threshold value, 
it indicates that no motion has been detected, and the LED remains off while the serial monitor displays a "No Motion" message. 
The delays in the code are used to debounce the signal and avoid false positives.
*/

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
