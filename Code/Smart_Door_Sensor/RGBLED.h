
#ifndef _RGBLED_H_
#define _RGBLED_H_

#include <Arduino.h>

class RGBLED{
public:

  enum Colour{
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,  
    MAGENTA
  };

  int redPin;
  int greenPin;
  int bluePin;

  RGBLED(int _redPin, int _greenPin, int _bluePin);

  void flashLED(enum RGBLED::Colour LEDColour, int timeOn);
  
  void LEDRed();
  void LEDYellow();
  void LEDGreen();
  void LEDCyan();
  void LEDBlue();
  void LEDMagenta();
  
  void LEDOff();
};


#endif // _RGBLED_H_
