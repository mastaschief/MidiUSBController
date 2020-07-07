#ifndef SwitchButton_h
#define SwitchButton_h
#include "Arduino.h"
#include "Button.h"
#include "MidiValues.h"

#define STOMPBOXMODES 3

class SwitchButton : public Button, public MidiValues
{
  public:
  SwitchButton();
  ~SwitchButton();
  void setColor(uint8_t red, uint8_t green, uint8_t blue);
  bool runStompbox();
  void setStompboxMode(uint8_t mode);
  void setSwitchNumber(uint8_t switchNumber);
  bool setSwitch(uint8_t switchNumber, uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, uint8_t channel, uint8_t value1, uint8_t value2min, uint8_t value2max, uint16_t speed, uint8_t expressionInput);
  uint8_t getColor(uint8_t rgb); 
  uint8_t getSwitchNumber();
  uint8_t getLedNumber();

private:
  uint8_t _switchNumber;
  uint8_t _color[3];
  uint8_t _stompboxMode; //0 = Switch, 1 = Expression, 2 = LFO
  uint8_t _ledNumber;
  uint16_t _speed;
  uint8_t _expressionInputPin;
};
#endif