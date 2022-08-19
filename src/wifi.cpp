#include "wifi.hpp"

char ssid[] = "BelongBFAD13";    // your network SSID (name)
char pass[] = "pw6ugc4bd2t7";    // your network password (use for WPA,
int status = WL_IDLE_STATUS;

WiFiServer server(80);        // port 3009

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
  // if (client) {
  //   Serial.println("new client");
  //   // an HTTP request ends with a blank line
  //   // boolean currentLineIsBlank = true;
  //   while (client.connected()) {
  //     Serial.println("sending to client");
  //     server.write("connect", 5);

      // if (client.available()) {
      //   char c = client.read();
      //   Serial.write(c);
      //   // if you've gotten to the end of the line (received a newline
      //   // character) and the line is blank, the HTTP request has ended,
      //   // so you can send a reply
      //   if (c == '\n' && currentLineIsBlank) {
      //     // send a standard HTTP response header
      //     client.println("HTTP/1.1 200 OK");
      //     client.println("Content-Type: text/html");
      //     client.println("Connection: close");  // the connection will be closed after completion of the response
      //     client.println("Refresh: 5");  // refresh the page automatically every 5 sec
      //     client.println();
      //     client.println("<!DOCTYPE HTML>");
      //     client.println("<html>");
      //     // output the value of each analog input pin
      //     for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
      //       int sensorReading = analogRead(analogChannel);
      //       client.print("analog input ");
      //       client.print(analogChannel);
      //       client.print(" is ");
      //       client.print(sensorReading);
      //       client.println("<br />");
      //     }
      //     client.println("</html>");
      //     break;
      //   }
      //   if (c == '\n') {
      //     // you're starting a new line
      //     currentLineIsBlank = true;
      //   } else if (c != '\r') {
      //     // you've gotten a character on the current line
      //     currentLineIsBlank = false;
      //   }
      // }
    //}
    // give the web browser time to receive the data
  //   delay(100);

  //   // close the connection:
  //   client.stop();
  //   Serial.println("client disconnected");
  // }
  // }

  if (client) {
    if (!alreadyConnected) {
      // clear out the input buffer:
      client.flush();
      alreadyConnected = true;
    }

    if (client.connected()) {
      Serial.write("Client found");
      server.write("knock", 5);
      Serial.write("Client found");
    }
  }
}
