#pragma once

#include <SPI.h>
#include <WiFiNINA.h>

void printWifiStatus();
void wifiSetup();
void sendMessage(char  message);
void connectToSocket();