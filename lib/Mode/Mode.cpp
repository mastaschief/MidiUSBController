#include "Arduino.h"
#include "Mode.h"

Mode::Mode(uint8_t okPin, uint8_t modeChangePin, uint8_t potiPins[])
{
    _ok.init(okPin);
    _modeChange.init(modeChangePin);

    
}

Mode::~Mode()
{

}

uint8_t Mode::getState()
{

    return _state;
}

uint8_t Mode::getSubMenu()
{
    return _subMenu;
}

bool Mode::run()
{
    if (_modeChange.read())
    {
        _state++;
        if (_state >= MODEAMOUNT)
        {
            _state = 0;
            _subMenu = 0;
        }
        return true;
    }
    if (_ok.read() && _state == 1)
    {
        _subMenu++;
        return true;
    }
    
    return false;
}

void Mode::setStateToZero()
{
    _state = 0;
    _subMenu = 0;
}

void Mode::subMenuIncrease(uint8_t value)
{
    _subMenu = _subMenu + value;
}