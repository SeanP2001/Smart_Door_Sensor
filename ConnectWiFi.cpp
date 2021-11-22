
#include "ConnectWiFi.h"

 
void setupWiFi(const char* ssid, const char* password) 
{
  Serial.println();
  Serial.println(ssid);
  Serial.println(password);
  Serial.print("Connecting to Access Point");
  WiFi.begin(ssid, password);                     // Connect to the provided wifi network
  
  while (WiFi.status() != WL_CONNECTED)           // while not connected
  {          
    Serial.print(".");                            // print dots
    delay(200);
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");              // once connected
  Serial.println("IP address: ");                 // print the IP address to the serial monitor
  Serial.println(WiFi.localIP());
  Serial.println();
}
