/**********************************************************
ESP-NOW; Sending Motion Sensor data from Web to the Spider (Sender)

use sudo iwlist wlan0 scanning to check the channels of wifi
sudo iwlist wlan0 channel
iwlist --help

change wifi channel: 
sudo ifconfig wlan0 down
sudo iwconfig wlan0 channel 1
sudo ifconfig wlan0 up
***********************************************************/

/* Including the Libraries */
#include<espnow.h>
#include<ESP8266WiFi.h>
#include<time.h>

/* Variables */
unsigned long lastTime = 0;
unsigned long timerDelay = 8000; //eight seconds
const int PIRSensorOutPin = A0;
time_t t;

/* MAC Addresses */
//uint8_t broadcastAddress[] = {0x30, 0x83, 0x98, 0x80, 0x3A, 0xBF};
//uint8_t broadcastAddress[] = {0x98, 0xCD, 0xAC, 0x30, 0xF9, 0x06};
uint8_t broadcastAddress[] = {0xE8, 0xDB, 0x84, 0xE0, 0x4A, 0x6C};

/* Defining the Data Structure */
typedef struct struct_message{
  char a[32];
  //int b;
  char b[32];
}Message;

/* Create Message */
Message message;

/* CallBack function called when data is sent */
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus){
 Serial.print("\r\nLast Packet Sent Status:\t");
 Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail"); 
}

/* Run Once */
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

/* Runs in a loop */
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
