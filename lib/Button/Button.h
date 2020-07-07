#ifndef Button_h
#define Button_h
#include "Arduino.h"
class Button
{
  public:
  Button();
  ~Button();
  void init(uint8_t pin);
  bool getButtonPressed();
  void setButtonPressedFalse();
  bool getStateOnOff();
  virtual bool readPin();
  unsigned long getPressedTime();
  bool read();

private:
  bool _stateOnOff;//
  uint8_t _pin;
  unsigned long _delayTime;
  unsigned long _pressedTime;
  bool _buttonPressed;

};
#endif