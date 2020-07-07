#include "Arduino.h"
#include "Button.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::init(uint8_t pin)
{
  
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
  _buttonPressed = false;
}

bool Button::readPin()
{
  return !digitalRead(_pin);
}

bool Button::read()
{
  if (millis() - _delayTime > 500)
  {
    if (readPin())
    {
      _stateOnOff = !_stateOnOff;
      _buttonPressed = true;
      // if (_buttonPressed)
      // {
      //   unsigned long startPress = millis();
      //   do
      //   {
      //     /* code */
      //   } while (readPin());
      //   _pressedTime = millis() - startPress;
      // }
      _delayTime = millis();
      return true;
    }
  }
  return false;
}

unsigned long Button::getPressedTime()
{
  return _pressedTime;
}

bool Button::getButtonPressed()
{
  return _buttonPressed;
}

bool Button::getStateOnOff()
{
  return _stateOnOff;
}

void Button::setButtonPressedFalse()
{
  _buttonPressed = false;
}

