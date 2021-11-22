/*
 * S.P.U.D Smart System - Door Sensor
 *
 * Works with LOLIN32 Lite, after installation of ESP32 Arduino Core:
 * In Arduino IDE set:
 * Set Board to "WEMOS LOLIN32"
 * Set Upload Speed 115200
 */

#include "ConnectWiFi.h"
#include "SendEmail.h"
#include "SaveAndLoadDetails.h"

struct deviceDetails {
  char wifiSSID[30];
  char wifiPassword[30];
  char deviceName[30];
  char emailAdd[30];
  char userName[15];
  bool setup;
};

deviceDetails device{
  "Not Set",
  "Not Set",
  "Not Set",
  "Not Set",
  "Not Set",
  false
};

/* EMAIL ALERT*/
const char* emailSubject = "Door Open";
const char* messageText = "Your room door has been opened";

int ledPin = 22;                       // onboard led is on pin 22
int switchPin = 19;                    // door reed switch on pin 19

enum State {CLOSED, OPEN};             // the state of the door is either closed or open

bool currentState = CLOSED;            // variable storing the current state of the door
bool previousState = CLOSED;           // variable storing the previous state of the door

int switchTime = 0;                    // varaible storing the last time that the state changed
int debounceDelay = 200;               // how long to wait to cancel out switch bounce (false inputs)


// ------------------------------------------------------------------------------------- S E T U P -------------------------------------------------------------------------------------
void setup()
{
  pinMode(ledPin, OUTPUT);                             // set the LED pin as an output
  pinMode(switchPin, INPUT);                           // set the reed switch as an input
  Serial.begin(115200);                                // start serial communication

  device = loadDetails();                              // load the device details 
  printDetails(device);                                // print the details which have been loaded

  if (device.setup){                                   // if the device has been setup
    setupWiFi(device.wifiSSID, device.wifiPassword);   // Connect to the WiFi
  }
    
  digitalWrite(ledPin, HIGH);                          // turn the LED off (ACTIVE LOW) 
}


// -------------------------------------------------------------------------------------- M A I N --------------------------------------------------------------------------------------
void loop()
{
  if (!device.setup)                                                                      // If the device has not been setup
  {
    // Activate WiFi Network
    // Wait for a connection
    // Take the user to the Setup Portal, return 1 if successful
    device.setup = true;                                                           // Flag that the device has now been setup
    // Save the device details  
  }

  else                                                                                    // If the device has been setup
  {
    currentState = digitalRead(switchPin);                                                // Set the current state of the door based on the reading from the reed switch
  
    if ((currentState != previousState) && ((millis() - switchTime) >= debounceDelay))    // if the door has changed state and the debounce delay time has passed
    {
      switchTime = millis();                                                              // log the time when the door state changed
      
      if (currentState == OPEN)                                                           // if the door is open
      {
        digitalWrite(ledPin, LOW);                                                        // turn the LED on (ACTIVE LOW)
        Serial.println("Door Open");                                                      // print "Door Open" to the serial monitor
        previousState = OPEN;                                                             // set the previous state to OPEN ready for the next loop
        sendEmail(device.emailAdd, device.userName, emailSubject, messageText);              // send the user an email
      }
      
      if (currentState == CLOSED)                                                         // if the door is closed
      {
        digitalWrite(ledPin, HIGH);                                                       // turn the LED off (ACTIVE LOW)           
        Serial.println("Door Closed");                                                    // print "Door Open" to the serial monitor
        previousState = CLOSED;                                                           // set the previous state to CLOSED ready for the next loop
      }
    }
  }  
}
