#include "Arduino.h"
#include "MidiValues.h"

MidiValues::MidiValues()
{

}

MidiValues::~MidiValues()
{

}

void MidiValues::sendMidiMessage(uint8_t value)
{
    uint8_t sendValue;
    sendValue = map(value, 0, 1023, _value2min, _value2max);
    _controlChange(_channel, _value1, sendValue);
    MidiUSB.flush();
}
void MidiValues::sendMidiMessage(bool onOff)
{
    uint8_t sendValue;
    if (onOff)
    {
        sendValue = 127;
    }
    else
    {
        sendValue = 0;
    }
    _controlChange(_channel, _value1, sendValue);
    MidiUSB.flush();
}

void MidiValues::setMidi(uint8_t channel, uint8_t value1)
{
    _channel = channel;
    _value1 = value1;
    _value2min = 0;
    _value2max = 64;
}

void MidiValues::setMidi(uint8_t channel, uint8_t value1, uint8_t value2min, uint8_t value2max)
{
    _channel = channel;
    _value1 = value1;
    _value2min = value2min;
    _value2max = value2max;
}

void MidiValues::_controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}