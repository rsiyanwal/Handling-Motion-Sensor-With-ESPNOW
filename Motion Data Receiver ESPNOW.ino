/*
ESP Now Demostration on Two ESPs
This one is for the Receiver
*/

/* Including the libraries */
#include<espnow.h>
#include<ESP8266WiFi.h>

/* Receiver data: Must match the sender structure */
typedef struct struct_message{
  char a[32];
  int b;
  float c;
}Message;

/* Create a message */
Message message;

/* Callback function that will be executed when data is received */
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len){
  memcpy(&message, incomingData, sizeof(message));
  Serial.print("Bytes Received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(message.a);
  Serial.print("Int: ");
  Serial.println(message.b);
  Serial.print("Float: ");
  Serial.println(message.c);
}

/* Run once */
void setup() {
  // Initialize Serial monitor
  Serial.begin(115200);

  // Set Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESPNOW
  if(esp_now_init() != 0){
    Serial.println("Error initializing ESPNOW");
    return;
  }

  // Registering Receiver for recv packer
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

/* Runs in a loop */
void loop() {

}
