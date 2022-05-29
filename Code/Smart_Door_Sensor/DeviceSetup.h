
#ifndef _DEVICE_SETUP_H_
#define _DEVICE_SETUP_H_

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

void notFound(AsyncWebServerRequest *request);

struct deviceDetails getCredsViaWebAP();


#endif // _DEVICE_SETUP_H_
