
#ifndef _CONNECT_WIFI_H_
#define _CONNECT_WIFI_H_

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

void setupWiFi(const char* ssid, const char* password);

void setupWiFiAP(const char* ssid, IPAddress local_ip, IPAddress gateway, IPAddress subnet);

bool isClientConnected();

#endif // _CONNECT_WIFI_H_
