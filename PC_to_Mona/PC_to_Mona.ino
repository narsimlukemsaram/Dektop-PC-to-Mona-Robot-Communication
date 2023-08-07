//Include the Mona_ESP library
#include "Mona_ESP_lib.h"

// using VSPI SPI
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define PACKET_SIZE 1460 //Can increase this with kconfig
#define UDP_PORT 54007

// WiFi network name and password:
const char* networkName = "MonaNetwork"; // replace with your network id
const char* networkPswd = "MonaRobot"; // replace with your network password

// IP address to send UDP data to:
// either use the ip address of the server or
// a network broadcast address
const int udpPort = UDP_PORT;

// Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;
char packet[PACKET_SIZE];

void setup() {
  //Initialize the MonaV2 robot
	Mona_ESP_init();
	//Turn LEDs to show that the Wifi connection is not ready
	Set_LED(1,20,0,0);
	Set_LED(2,20,0,0);
  //Initialize serial port
  Serial.begin(115200);
  // connect to network
  connectToWiFi(networkName, networkPswd);
  Serial.print("Connecting to Wifi");
}

void loop() {
  if (connected) {
    int packetSize = udp.parsePacket();

    // Received packets go to buffer
    if (packetSize > 0) {
      int len = udp.read(packet, packetSize);
      Serial.println(packet);
      for(int i = 0; i < len; i++){
        // Decode and execute the obtained message
        Serial.print("Read command: ");
        Serial.print(packet[i]);
        if(packet[i] == 'F'){
          Motors_forward(150);
          delay(500);
          Motors_stop();
        }
        if(packet[i] == 'B'){
          Motors_backward(150);
          delay(500);
          Motors_stop();
        }
        if(packet[i] == 'R'){
          Motors_spin_right(150);
          delay(500);
          Motors_stop();
        }
        if(packet[i] == 'L'){
          Motors_spin_left(150);
          delay(500);
          Motors_stop();
        }
      }
    }
  }
}

void connectToWiFi(const char* ssid, const char* pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  // register event handler
  WiFi.onEvent(WiFiEvent);

  // Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
}

// Wifi event handler
void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      // Initializes the UDP state
      // This initializes the transfer buffer
      udp.begin(WiFi.localIP(), udpPort);
      connected = true;
      WiFi.setTxPower(WIFI_POWER_19_5dBm);
      // When connected set
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      udp.stop();
      connected = false;
      break;
    default: break;
  }
}