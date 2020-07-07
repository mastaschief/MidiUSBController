#include "Arduino.h"
#include "SwitchButton.h"

SwitchButton::SwitchButton()
{

}

SwitchButton::~SwitchButton()
{

}

void SwitchButton::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    _color[0] = red;
    _color[0] = green;
    _color[0] = blue;
}

bool SwitchButton::setSwitch(uint8_t switchNumber, uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, uint8_t channel, uint8_t value1, uint8_t value2min, uint8_t value2max, uint16_t speed, uint8_t expressionInput)
{
    if (_switchNumber == switchNumber)
    {
        _ledNumber = ledNumber;
        setColor(red, green, blue);
        _stompboxMode = mode;
        setMidi(channel, value1, value2min, value2max);
        _speed = speed;
        _expressionInputPin = expressionInput;
        return true;
    }
    return false;
}

void SwitchButton::setSwitchNumber(uint8_t switchNumber)
{
    _switchNumber = switchNumber;
    _ledNumber = switchNumber + 1;
}

uint8_t SwitchButton::getLedNumber()
{
    return _ledNumber;
}

bool SwitchButton::runStompbox()
{
    read();
    if (getButtonPressed())
    {
        switch (_stompboxMode)
        {
        case 0://Swith
            sendMidiMessage(getStateOnOff());
            setButtonPressedFalse();
            return true;
            break;
        case 1://Expression
            break;
        case 2://Value
            break;
        default:
            break;
        }
        return false;
    }
    return false;
}

void SwitchButton::setStompboxMode(uint8_t mode)
{
    if (mode < STOMPBOXMODES)
    {
        _stompboxMode = mode;
    }
}

uint8_t SwitchButton::getColor(uint8_t rgb)
{
    if (getStateOnOff())
    {
        return _color[rgb];
    }
    else
    {
        return 0x000000;
    }
}

uint8_t SwitchButton::getSwitchNumber()
{
    return _switchNumber;
}