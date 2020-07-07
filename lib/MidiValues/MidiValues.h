#ifndef MidiValues_h
#define MidiValues_h
#include "Arduino.h"
#include "MIDIUSB.h"
class MidiValues
{
public:
    MidiValues();
    ~MidiValues();
    void sendMidiMessage(uint8_t value);
    void sendMidiMessage(bool onOff);
    
    
    void setMidi(uint8_t channel, uint8_t value1);
    void setMidi(uint8_t channel, uint8_t value1, uint8_t value2min, uint8_t value2max);
private:
    uint8_t _channel;
    uint8_t _value1;
    uint8_t _value2min;
    uint8_t _value2max;
    void _controlChange(byte channel, byte control, byte value);
};
#endif