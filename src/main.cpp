// Copyright (c) Jahr 2020, Felix Schwemlein

// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.

// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

//TODO:
//Aufräumen, besser kommentieren
//Led Farbe wird nicht richtig gespeichert bzw. geladen
//LFO Funktion integrieren
//Integration der MenuLEDs
//externe Expressionanschlüsse integrieren
//externe I2C Client geräte einbinden
//Lizenz überprüfen



#define POTI1PIN 19
#define POTI2PIN 20
#define POTI3PIN 21
#define SWITCH1PIN 15
#define SWITCH2PIN 14
#define BUTT1PIN 7
#define BUTT2PIN 4

#define NEOPIXELPIN 16
#define NUM_LEDS 3
#define EEPRROMSWITCHSTART 200

#include "Arduino.h"
#include "EEPROM.h"
#include "U8glib.h"
#include "Button.h"
#include "SwitchButton.h"
#include "Mode.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel pixels(NUM_LEDS, NEOPIXELPIN, NEO_RGB + NEO_KHZ800);

uint8_t potiPins[] = {POTI1PIN, POTI2PIN, POTI3PIN};
Mode menu(BUTT1PIN, BUTT2PIN, potiPins);

SwitchButton internalSwitch[2];

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send ACK
Button testButton;
bool printDisplay = true;
uint8_t displayMode;
char charDisplayHelper[4];
bool safeOrDontSafe;

struct assign
{
  uint8_t whichSwitch;
  uint8_t ledNumber;
  uint8_t color[3];//0 r, 1 g, 2 b
  uint8_t mode;
  uint8_t channel;
  uint8_t value1;
  uint8_t value2min;
  uint8_t value2max;
  uint16_t speed;
  uint8_t expressionInputPin;
}assignToSwitch;

void safeSwitchToEEprom()
{
  EEPROM.put(EEPRROMSWITCHSTART + (assignToSwitch.whichSwitch*20), assignToSwitch);
  internalSwitch[assignToSwitch.whichSwitch].setSwitch(assignToSwitch.whichSwitch , assignToSwitch.ledNumber, assignToSwitch.color[0], assignToSwitch.color[1], assignToSwitch.color[2], assignToSwitch.mode, assignToSwitch.channel, assignToSwitch.value1, assignToSwitch.value2min, assignToSwitch.value2max, assignToSwitch.speed, assignToSwitch.expressionInputPin);
}

void loadSwitchesAtStart()
{
  for (size_t i = 0; i < 2; i++)//interne Switches
  {
    EEPROM.get(EEPRROMSWITCHSTART + (i*20), assignToSwitch);
    internalSwitch[i].setSwitch(assignToSwitch.whichSwitch , assignToSwitch.ledNumber, assignToSwitch.color[0], assignToSwitch.color[1], assignToSwitch.color[2], assignToSwitch.mode, assignToSwitch.channel, assignToSwitch.value1, assignToSwitch.value2min, assignToSwitch.value2max, assignToSwitch.speed, assignToSwitch.expressionInputPin);
  }
}

void printLED(uint8_t led, uint8_t red, uint8_t green, uint8_t blue)
{
  pixels.setPixelColor(led, pixels.Color(red, green, blue));
  pixels.show();
}

void valueToChar(uint16_t value)
{
  itoa(value, charDisplayHelper, 10);
}

uint16_t getPotiValue(uint8_t poti, uint16_t min, uint16_t max)
{
  uint16_t returnValue;
  if ((max-min) >=  5)
  {
    returnValue = map(analogRead(poti), 0, 1023, min, max);
  }
  else
  {
    returnValue = map(analogRead(poti), 0, 700, min, max);
  }
    return returnValue;
}

void draw(uint8_t display) {
  u8g.setFont(u8g_font_unifont);
  switch (display)
  {
  case 0:
    u8g.drawStr( 20, 40, "Stompbox");
    printLED(0, 0, 127, 0);
    break;
  case 1:
    u8g.drawStr( 20, 40, "Assign");
    printLED(0, 0, 0, 127);
    break;
  case 2:
    u8g.drawStr( 20, 40, "Press Switch");
    valueToChar(assignToSwitch.whichSwitch);
    u8g.drawStr(60, 15, charDisplayHelper);
    break;
  case 3:
    printDisplay = true;
    u8g.drawStr(40, 40, "Color");
    uint8_t colors[3];
    for (size_t i = 0; i < 3; i++)
    {
      uint8_t printValue = map(analogRead(potiPins[i]), 0, 1023, 0, 255);
      valueToChar(printValue);
      u8g.drawStr(5+(i*40), 15, charDisplayHelper);
      switch (i)
      {
      case 0:
      colors[0] = printValue;
        break;
      case 1:
      colors[1] = printValue;
        break;
      case 2:
      colors[2]= printValue;
        break;
      default:
        break;
      }
    }
    for (size_t i = 0; i < 3; i++)
    {
      assignToSwitch.color[0] = colors[i];
    }
    printLED(assignToSwitch.ledNumber, colors[0], colors[1], colors[2]);
    printLED(0, colors[0], colors[1], colors[2]);
    break;
  case 4:
    {
      printDisplay = true;
      u8g.drawStr(40, 40, "Mode");
      u8g.drawStr(5, 10, "Stomp");
      u8g.drawStr(60, 10, "Exp");
      u8g.drawStr(100, 10, "LFO");
      uint8_t modeValue = getPotiValue(potiPins[0],0,2);
      u8g.drawTriangle(30+(modeValue*40), 20, 25+(modeValue*40), 30, 35+(modeValue*40), 30);
      assignToSwitch.mode = modeValue;
    }
    break;
  case 5://Midi Channel und cc
    printDisplay = true;
    for (size_t i = 0; i < 2; i++)
      {
        uint16_t printMidValue;
        if (i<1)
        {
        printMidValue = map(analogRead(potiPins[i]), 0, 1023, 0, 16);
        assignToSwitch.channel = printMidValue;
        }
        else
        {
        printMidValue = map(analogRead(potiPins[i]), 0, 1023, 0, 127);
        assignToSwitch.value1 = printMidValue;
        }
        valueToChar(printMidValue);
        u8g.drawStr(5+(i*40), 15, charDisplayHelper);
      }
    u8g.drawStr(5,35,"ch");
    u8g.drawStr(45, 35, "cc");
    
    u8g.drawStr(20, 60, "Midi Setting");
    break;
  case 6:
    printDisplay = true;
    uint8_t yesOrNo;
    yesOrNo = getPotiValue(potiPins[0],0,1);
    Serial.println(yesOrNo);
    u8g.drawTriangle(15+(yesOrNo*95), 20, 10+(yesOrNo*95), 30, 20+(yesOrNo*95), 30);
    u8g.drawStr(5, 10, "no");
    u8g.drawStr(100, 10, "yes");
    u8g.drawStr(40, 60, "Safe?");
    if (yesOrNo == 1)
    {
      safeOrDontSafe = true;
    }
    else
    {
      safeOrDontSafe = false;
    }
    break;
  case 7:
    u8g.drawStr(40,40,"Saved!");
    break;
  case 8:
    u8g.drawStr(20,40, "Cancelled!");
    break;
  case 10://Expression
    u8g.drawStr(40, 60, "Move Pot");
    break;
  case 11://LFO
    for (size_t i = 0; i < 3; i++)
    {
      uint16_t printLFOValue;
      if (i<2)
      {
      printLFOValue = map(analogRead(potiPins[i]), 0, 1023, 0, 127);
        if (i == 0)
        {
          assignToSwitch.value2min = printLFOValue;
        }
        else
        {
          assignToSwitch.value2max = printLFOValue;
        }
      }
      else
      {
      printLFOValue = map(analogRead(potiPins[i]), 0, 1023, 0, 1023);
      assignToSwitch.speed = printLFOValue;
      }
      valueToChar(printLFOValue);
      u8g.drawStr(5+(i*40), 15, charDisplayHelper);
    }
    u8g.drawStr(5,35,"min");
    u8g.drawStr(45, 35, "max");
    u8g.drawStr(80,35, "speed");
    u8g.drawStr(20, 60, "LFO Setting");
    break;
  default:
    u8g.drawStr(20,20, "Fail");
    break;
  } 
}

void setup(void) {
  Serial.begin(9600);
  delay(1000);
  pixels.begin();
  pixels.setBrightness(50);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  // internalSwitch[0].init(SWITCH1PIN);
  // internalSwitch[1].init(SWITCH2PIN);
  // internalSwitch[0].setSwitchNumber(0);
  // internalSwitch[1].setSwitchNumber(1);
  // internalSwitch[0].setMidi(1,36);
  // internalSwitch[1].setMidi(2,36);
  // internalSwitch[0].setStompboxMode(0);
  // internalSwitch[1].setStompboxMode(0);
  // internalSwitch[0].setColor(0, 180, 0);
  // internalSwitch[1].setColor(0, 0, 180);

  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    printLED(i, 0, 0, 0);
	}
  loadSwitchesAtStart();
}

void loop(void) {
  if (menu.run())
  {
    printDisplay = true;
  }

  switch (menu.getState())
  {
    case 0: //Stompbox
      for (size_t i = 0; i < 2; i++)//internal
      {
        if (internalSwitch[i].runStompbox())
        {
          printLED(internalSwitch[i].getLedNumber(), internalSwitch[i].getColor(0), internalSwitch[i].getColor(1), internalSwitch[i].getColor(2));
          printDisplay = true;
        }
      }
      displayMode = 0;
      break;
    case 1: //Assign
      switch (menu.getSubMenu())
      {
        case 0://Welcome
          displayMode = 1;
          break;
        case 1://Choose Switch
          displayMode = 2;
          for (size_t i = 0; i < 2; i++)
          {
            if (internalSwitch[i].read())
            {
              assignToSwitch.whichSwitch = internalSwitch[i].getSwitchNumber();
              assignToSwitch.ledNumber = internalSwitch[i].getLedNumber();
              printDisplay = true;
            }
          }
          break;
        case 2://Choose Color
          displayMode = 3;
          break;
        case 3://ChooseMode
          displayMode = 4;
          break;
        case 4:
          switch (assignToSwitch.mode)
          {
          case 0:
            menu.subMenuIncrease(1);
            printDisplay = true;
            break;
          case 1://ExpressionConfig
            displayMode = 10;
            printDisplay = true;
            break;
          case 2://LFOConfig
            displayMode = 11;
            printDisplay = true;
            break;
          default:
            Serial.println(assignToSwitch.mode);
            
            break;
          }
        break;
        case 5://MidiSetting
          displayMode = 5;
          break;
        case 6://Safe
          displayMode = 6;
          break;
        case 7://Result
          if (safeOrDontSafe)
          {
            displayMode = 7;
            safeSwitchToEEprom();
          }
          else
          {
            displayMode = 8;
          }
          menu.subMenuIncrease(1);
          break;
        case 8://Finish Submenu
          //delay(500);
          menu.setStateToZero();
          printDisplay = true;
          menu.run();
          break;
        default:
          break;
      }
    break;
    default:
      Serial.print("Fail");
      break;
  }
  if (printDisplay)
  {
    Serial.print(displayMode);
    printDisplay = false;
    u8g.firstPage();  
    do {
      draw(displayMode);
    } while( u8g.nextPage() );
    
  }
  
}