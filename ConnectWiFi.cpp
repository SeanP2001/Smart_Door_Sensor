
#include "ConnectWiFi.h"

// ------------------------------------------------------------------------------ S E T U P   W I F I ------------------------------------------------------------------------------
void setupWiFi(const char* ssid, const char* password) 
{
  Serial.println();
  Serial.println(ssid);
  Serial.println(password);
  Serial.print("Connecting to Access Point");
  WiFi.begin(ssid, password);                     // Connect to Wi-Fi using the provided credentials
  
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

// ---------------------------------------------------------------------- S E T U P   A C C E S S   P O I N T ----------------------------------------------------------------------
void setupWiFiAP(const char* ssid, IPAddress local_ip, IPAddress gateway, IPAddress subnet) 
{
  WiFi.mode(WIFI_AP);                                // set to access point mode
  WiFi.softAP(ssid);                                 // create and open network with the provided SSID
  WiFi.softAPConfig(local_ip, gateway, subnet);      // configure access point

  IPAddress IP = WiFi.softAPIP();                    // get the ip address
  
  Serial.println();                                  // and print it to the console
  Serial.print("IP Address: ");                       
  Serial.println(IP);
}

// ---------------------------------------------------------- C H E C K   I F   A   D E V I C E   I S   C O N N E C T E D ----------------------------------------------------------
bool isClientConnected()
{
  if (WiFi.softAPgetStationNum() == 1)                // if a device is connected
  {
    Serial.println("\nDevice Connected");             // print to the console
    return true;                                      // and return true (a device is connected)
  } 
  else                                                // otherwise
  {
    return false;                                     // return false (no devices are conncted)
  }  
}
