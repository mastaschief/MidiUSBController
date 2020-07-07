#ifndef ExternSwitch_h
#define ExternSwitch_h
#include "Arduino.h"
#include "SwitchButton.h"

class ExternSwitch : public SwitchButton
{
private:
    uint8_t _i2cSlaveAdress;
    byte _state;
    uint8_t _bit;
public:
    void setStateByte(byte stateByte);
    bool readPin();
    ExternSwitch(/* args */);
    ~ExternSwitch();
};

#endif