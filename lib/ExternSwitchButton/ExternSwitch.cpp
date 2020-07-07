#include "Arduino.h"
#include "ExternSwitch.h"


ExternSwitch::ExternSwitch(/* args */)
{
}

ExternSwitch::~ExternSwitch()
{
}

bool ExternSwitch::readPin()
{
    return bitRead(_state, _bit);
}

void ExternSwitch::setStateByte(byte stateByte)
{
    _state = stateByte;
}