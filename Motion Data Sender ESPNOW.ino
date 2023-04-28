/*
This is a code for ESP8266-based microcontrollers that sends motion sensor data from the web to the Spider using ESP-NOW protocol. 
The program includes the necessary libraries for ESP-NOW and ESP8266WiFi.

The code sets up the ESP8266 module as a Wi-Fi station and initializes the ESP-NOW protocol. 
It registers a send callback function and adds a peer with a specific MAC address.

The code defines a data structure named Message, which consists of two elements: a character array of size 32 to store the current date and time, 
and another character array of size 32 to store the motion sensor value.

In the loop, the code checks the analog output of a PIR motion sensor connected to pin A0. 
If the analog output is above a certain threshold, the program sets the LED pin D0 to HIGH, 
populates the message structure with the current date and time and a string "E7", which represents the motion sensor data, 
and sends the message via ESP-NOW to the registered peer with a specific MAC address. 
If the analog output is below the threshold, the program sets the LED pin D0 to LOW.

The program also includes a callback function named OnDataSent, which prints the status of the last packet sent by the ESP-NOW protocol.
*/

// Including the Libraries
#include<espnow.h>
#include<ESP8266WiFi.h>
#include<time.h>

/* 
Variables 
*/
unsigned long lastTime = 0;
unsigned long timerDelay = 8000; //eight seconds
const int PIRSensorOutPin = A0;
time_t t;

/*
BROADCAST ADDRESS is the MAC address of the NodeMCU receiver and can be obtained using the algorithm described in https://github.com/rsiyanwal/NodeMCU-MAC-Address. 
MESSAGE is a variable that holds the message to be sent when motion is detected. We have used structures in the C++ programming language for this purpose. 
The variable SIZE specifies the size of the message to be sent. It is important to note that for ESP-NOW, the message size should not exceed 250 bytes.
*/
// Receiver's MAC Address
uint8_t broadcastAddress[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

// Defining the Data Structure
typedef struct struct_message{
  char a[32];
  char b[32];
}Message;

// Create Message
Message message;

/* 
CallBack function called when data is sent 
*/
// Checking if the message is successfully delivered or not.
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus){
 Serial.print("\r\nLast Packet Sent Status:\t");
 Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail"); 
}

/*
The process involves the following steps:
- Set up Serial monitor
- Set WiFi mode
- Initialize ESP-NOW protocol
- Register callback function
- Register peer using its MAC address.
*/
void setup(){
  // Serial Monitor
  Serial.begin(115200);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP_NOW
  if(esp_now_init() != 0){
    Serial.println("Error initializing ESP_NOW");
    return;
  }

  // Register the send CallBack
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Register Peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 6, NULL, 0);

  // Pinmode
  pinMode(PIRSensorOutPin, INPUT);
  pinMode(D0, OUTPUT);

}

/*
Sending Motion Sensor Data
*/
void loop(){
  time(&t);
  if((millis() - lastTime) > timerDelay){
    if(analogRead(PIRSensorOutPin) > 1000){
      // Setting LED High
      digitalWrite(D0, HIGH);
      
      // Setting values to send
      strcpy(message.a, ctime(&t));                 // Date and Time
      //message.b = analogRead(PIRSensorOutPin);      // Motion Sensor Value
      strcpy(message.b, "E7");
      
      // Send message via ESP-NOW
      esp_now_send(broadcastAddress, (uint8_t *) &message, sizeof(message));
    }else{
      // Setting LED Low
      digitalWrite(D0, LOW);
    }
    lastTime = millis();
  }
}
