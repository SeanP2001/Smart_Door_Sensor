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
#include "RGBLED.h"

#include <ESP32Servo.h>  // only needed for tone

// ----------------------------------------------------------------- D E V I C E   D E T A I L S   V A R I A B L E S -----------------------------------------------------------------
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

// ------------------------------------------------------------------------------ E M A I L   A L E R T S ------------------------------------------------------------------------------
const char* emailSubject = "Door Open";
const char* messageText = "Your room door has been opened";

// ------------------------------------------------------------------------------ D E C L A R E   P I N S ------------------------------------------------------------------------------
int ledPin = 22;                                            // onboard led is on pin 22
int buzzerPin = 14;                                         // buzzer connected to pin 14

// ----------------------------------------------------------------------------- R G B   L E D   S E T U P -----------------------------------------------------------------------------
int redLEDPin = 25;                                         // RGB LED red leg on pin 25 
int greenLEDPin = 26;                                       // RGB LED green leg on pin 26
int blueLEDPin = 27;                                        // RGB LED blue leg on pin 27

RGBLED indicatorLED(redLEDPin, greenLEDPin, blueLEDPin);    // instantiate an RGB LED

// ---------------------------------------------------------------------------- S E T U P   S W I T C H E S ----------------------------------------------------------------------------
int emailSwitchPin = 23;                                    // switch to enable or disable email notifications on pin 23
int buzzerSwitchPin = 18;                                   // switch to enable or disable the buzzer on pin 23

bool emailAlert;                                            // a boolean variable to store whether email notifications are enabled or disabled
bool buzzerAlert;                                           // a boolean variable to store whether the buzzer is enabled or disabled

// ------------------------------------------------------------------------- D O O R   S E N S O R   S E T U P -------------------------------------------------------------------------
int doorSwitchPin = 19;                                     // door reed switch on pin 19

enum State {CLOSED, OPEN};                                  // the state of the door is either closed or open

bool currentState = CLOSED;                                 // variable storing the current state of the door
bool previousState = CLOSED;                                // variable storing the previous state of the door

int switchTime = 0;                                         // varaible storing the last time that the state changed
int debounceDelay = 200;                                    // how long to wait to cancel out switch bounce (false inputs)



// ------------------------------------------------------------------------------------- S E T U P -------------------------------------------------------------------------------------
void setup()
{
  pinMode(ledPin, OUTPUT);                                    // set the LED pin as an output
  pinMode(doorSwitchPin, INPUT);                              // set the reed switch as an input
  pinMode(emailSwitchPin, INPUT);                             // set the email notification switch as an input
  pinMode(buzzerSwitchPin, INPUT);                            // set the buzzer switch as an input
  pinMode(buzzerPin, OUTPUT);                                 // set the buzzer as an output 
  
  Serial.begin(115200);                                       // start serial communication

  device = loadDetails();                                     // load the device details 
  printDetails(device);                                       // print the details which have been loaded

  if (device.setup){                                          // if the device has been setup
    setupWiFi(device.wifiSSID, device.wifiPassword);          // Connect to the WiFi
  }

  emailAlert = digitalRead(emailSwitchPin);                   // set the email alerts to be enabled or disable based on the current position of the email switch
  buzzerAlert = digitalRead(buzzerSwitchPin);                 // set the buzzer to be enabled or disabled based on the current position of the buzzer switch
  
  digitalWrite(ledPin, HIGH);                                 // turn the LED off (ACTIVE LOW) 
}


// -------------------------------------------------------------------------------------- M A I N --------------------------------------------------------------------------------------
void loop()
{
  if (!device.setup)                                                                      // If the device has not been setup
  {
    // Activate WiFi Network
    // Wait for a connection
    // Take the user to the Setup Portal, return 1 if successful
    device.setup = true;                                                                  // Flag that the device has now been setup
    // Save the device details  
  }

  else                                                                                    // If the device has been setup
  {  
    currentState = digitalRead(doorSwitchPin);                                            // Set the current state of the door based on the reading from the reed switch
  
    if ((currentState != previousState) && ((millis() - switchTime) >= debounceDelay))    // if the door has changed state and the debounce delay time has passed
    {
      switchTime = millis();                                                              // log the time when the door state changed
      
      if (currentState == OPEN)                                                           // if the door is open
      {
        digitalWrite(ledPin, LOW);                                                        // turn the LED on (ACTIVE LOW)
        Serial.println("Door Open");                                                      // print "Door Open" to the serial monitor
        

        if(buzzerAlert)                                                                   // If the buzzer is enabled
        {
            tone(buzzerPin, 2000);                                                        // sound the buzzer
            delay(500);
            noTone(buzzerPin);
        }
        if(emailAlert)                                                                    // If email alerts are enabled
        {
          sendEmail(device.emailAdd, device.userName, emailSubject, messageText);         // send the user an email
        }
        previousState = OPEN;                                                             // set the previous state to OPEN ready for the next loop
      }
      
      if (currentState == CLOSED)                                                         // if the door is closed
      {
        digitalWrite(ledPin, HIGH);                                                       // turn the LED off (ACTIVE LOW)           
        Serial.println("Door Closed");                                                    // print "Door Open" to the serial monitor
        previousState = CLOSED;                                                           // set the previous state to CLOSED ready for the next loop
      }
    }
    
    if(digitalRead(emailSwitchPin) != emailAlert)                                         // if the email alerts switch has changed states
    {
      if(digitalRead(emailSwitchPin) == HIGH)                                             // and emails have been enabled
      {
        indicatorLED.flashLED(RGBLED::GREEN, 500);                                        // flash green
        emailAlert = true;                                                                // and set the email alerts to enabled
      }
      if(digitalRead(emailSwitchPin) == LOW)                                              // if the email alerts have been disabled
      {
        indicatorLED.flashLED(RGBLED::RED, 500);                                          // flash red
        emailAlert = false;                                                               // and set the email alerts to disabled
      } 
    }
    
    if(digitalRead(buzzerSwitchPin) != buzzerAlert)                                       // if the buzzer switch has changed states           
    {
      if(digitalRead(buzzerSwitchPin) == HIGH)                                            // and it has been enabled
      {
        indicatorLED.flashLED(RGBLED::BLUE, 500);                                         // flash blue
        buzzerAlert = true;                                                               // and set the buzzer to enabled
      }
      if(digitalRead(buzzerSwitchPin) == LOW)                                             // if the buzzer has been disabled
      {
        indicatorLED.flashLED(RGBLED::YELLOW, 500);                                       // flash yellow
        buzzerAlert = false;                                                              // and set the buzzer alerts to disabled
      } 
    }
  }   
}
