#ifndef Mode_h
#define Mode_h
#include "Arduino.h"
#include "Button.h"

#define MODEAMOUNT 2

class Mode
{
public:
    Mode(uint8_t okPin, uint8_t modeChangePin, uint8_t potiPins[]);
    ~Mode();
    uint8_t getState();
    uint8_t getSubMenu();
    bool run();
    void setStateToZero();
    void subMenuIncrease(uint8_t value);
    

private:
    Button _ok;
    Button _modeChange;
    uint8_t _state = 0;
    uint8_t _subMenu = 0;
    
};
#endif