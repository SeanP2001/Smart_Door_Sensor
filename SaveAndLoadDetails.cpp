
#include "SaveAndLoadDetails.h"

#define EEPROM_SIZE 512                     // Size of EEPROM memory available
int saveAddress = 0;                        //Location to save to and load from

struct deviceDetails {
  char wifiSSID[30];
  char wifiPassword[30];
  char deviceName[30];
  char emailAdd[30];
  char userName[15];
  bool setup;
};


// -------------------------------------------------------------------------------- S A V E   D E V I C E   D E T A I L S --------------------------------------------------------------------------------
void saveDetails(struct deviceDetails device)       
{ 
  EEPROM.begin(EEPROM_SIZE);                 // initialise the EEPROM memory
  
  EEPROM.put(saveAddress, device);           // save the device details

  EEPROM.commit();                           // commit the changes

  EEPROM.end();                              // release the RAM copy of the EEPROM contents
}

// -------------------------------------------------------------------------------- L O A D   D E V I C E   D E T A I L S --------------------------------------------------------------------------------
struct deviceDetails loadDetails()
{
  deviceDetails readDetails;                 // Create a struct to store all of the read data
  
  EEPROM.begin(EEPROM_SIZE);                 // initialise the EEPROM memory

  EEPROM.get(saveAddress, readDetails);      // retrieve the device details from EEPROM memory and store them in the deviceDetails struct
  
  EEPROM.end();                              // release the RAM copy of the EEPROM contents

  return readDetails;                        // return the details which have been loaded
}  

// ------------------------------------------------------------------------------- P R I N T   D E V I C E   D E T A I L S -------------------------------------------------------------------------------
void printDetails(struct deviceDetails device)
{
  Serial.println( "Device Details: " );
  Serial.print("WiFi SSID: ");
  Serial.println( device.wifiSSID );
  Serial.print("WiFi Password: ");
  Serial.println( device.wifiPassword );
  Serial.print("Device Name: ");
  Serial.println( device.deviceName );
  Serial.print("Email Address: ");
  Serial.println( device.emailAdd );
  Serial.print("Your Name: ");
  Serial.println( device.userName );
  Serial.println( "Setup: " );
  Serial.print( device.setup );
}
