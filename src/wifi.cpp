#include "wifi.hpp"

char ssid[] = "MTRX3700-IoT";    // your network SSID (name)
char pass[] = "MTRX3700";    // your network password (use for WPA,
int status = WL_IDLE_STATUS;

WiFiServer server(3009);        // port 3009

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
    server.begin();

    // you're connected now, so print out the status:
    printWifiStatus();
  }

}

void sendMessage(char message) {
  Serial.write("Attempting to send message");
  WiFiClient client = server.available();

  if (client) {
    if (!alreadyConnected) {
      // clear out the input buffer:
      client.flush();
      alreadyConnected = true;
    }

    if (client.connected()) {
      Serial.write("Client found");
      server.write("knock", 5);
    }
  }
}
