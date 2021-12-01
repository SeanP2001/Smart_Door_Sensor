
#ifndef _SAVE_AND_LOAD_DETAILS_H_
#define _SAVE_AND_LOAD_DETAILS_H_

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512

void saveDetails(struct deviceDetails device);

struct deviceDetails loadDetails();

void resetDetails(); 

void printDetails(struct deviceDetails device);


#endif // _SAVE_AND_LOAD_DETAILS_H_
