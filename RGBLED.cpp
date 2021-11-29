
#include "RGBLED.h"
// ------------------------------------------------------------------------------------- S E T U P -------------------------------------------------------------------------------------
RGBLED::RGBLED(int _redPin, int _greenPin, int _bluePin)        // RGB LED constructor
{
  this->redPin = _redPin;                                       // setup the R,G & B pins
  this->greenPin = _greenPin;
  this->bluePin = _bluePin;

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

// --------------------------------------------------------------------------------- F L A S H   L E D ---------------------------------------------------------------------------------
void RGBLED::flashLED(enum RGBLED::Colour LEDColour, int timeOn)
{
  switch(LEDColour)                                    // go to the function for the specified colour             
  {
    case RED: LEDRed(); break;
    case YELLOW: LEDYellow(); break;
    case GREEN: LEDGreen(); break;
    case CYAN: LEDCyan(); break;
    case BLUE: LEDBlue(); break;
    case MAGENTA: LEDMagenta(); break;    
  }
  delay(timeOn);                                       // leave the LED on for the specified time
  LEDOff();                                            // and then turn off the LED
}

// --------------------------------------------------------------------------------------- R E D ---------------------------------------------------------------------------------------
void RGBLED::LEDRed()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

// ------------------------------------------------------------------------------------ Y E L L O W ------------------------------------------------------------------------------------
void RGBLED::LEDYellow()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

// ------------------------------------------------------------------------------------- G R E E N -------------------------------------------------------------------------------------
void RGBLED::LEDGreen()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

// -------------------------------------------------------------------------------------- C Y A N --------------------------------------------------------------------------------------
void RGBLED::LEDCyan()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

// -------------------------------------------------------------------------------------- B L U E --------------------------------------------------------------------------------------
void RGBLED::LEDBlue()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

// ----------------------------------------------------------------------------------- M A G E N T A -----------------------------------------------------------------------------------
void RGBLED::LEDMagenta()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

// --------------------------------------------------------------------------------------- O F F ---------------------------------------------------------------------------------------
void RGBLED::LEDOff()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}
