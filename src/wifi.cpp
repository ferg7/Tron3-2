#include "wifi.hpp"
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include<string.h>  

char ssid[] = "BelongBFAD13";    // your network SSID (name)
char pass[] = "pw6ugc4bd2t7";    // your network password (use for WPA,
int status = WL_IDLE_STATUS;

unsigned int localPort = 2390; 

WiFiUDP Udp;

boolean alreadyConnected = false;

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void wifiSetup() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);

    // start the server:
    Udp.begin(localPort);

    printWifiStatus();

    connectToSocket();
  }

}

void connectToSocket(){
  char packetBuffer[256]; //buffer to hold incoming packet
 // if there's data available, read a packet
  
  boolean connection = false;
  while (connection==false) {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    int value =strcmp(packetBuffer,"connection established");  
    Serial.println(value);
    delay(1000);
    if (value == 0){
      connection = true;
    }

    // send a reply, to the IP address and port that sent us the packet we received
    char  ReplyBuffer[] = "connection established"; 
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    delay(2000);
    Udp.endPacket();
  }
}
}



void sendMessage(char message){
 
    char  ReplyBuffer[] = "Knock Knock bitches";
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
    delay(1000);
}
