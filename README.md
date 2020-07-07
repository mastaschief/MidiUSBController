Um Modep(https://blokas.io/modep/) als Multieffektgerät für meinen Bass zu nutzen, habe ich einen Raspberry Pi 4 in ein altes Audiointerface eingebaut. 
Zur Steurung der Effekte habe ich einen Midi Controller entworfen.

Bilder und 3D Entwürfe: https://cloud.0815musiker-innen.de/index.php/s/WfBTnQDQkk3EqNn

Aufbau:
Instrumen(Bass)	-> Audiointerface Klinken Input
Midi Controller	-> RasperryPi USB
Externer Controller -> RJ45 Buchse (I2C)
Audioninterface Output -> Endstufe(Bassverstärker)

Funktionen:
- An und Ausschalten der Effekte

ToDo:
- Aufräumen, besser kommentieren
- Led Farbe wird nicht richtig gespeichert bzw. geladen
- LFO Funktion integrieren
- Integration der MenuLEDs
- externe Expressionanschlüsse integrieren
- externe I2C Client geräte einbinden
- Lizenz überprüfen

Verwendete externe Librarys:
- Adafruit NeoPixel (https://github.com/adafruit/Adafruit_NeoPixel)
- MIDIUSB           (https://github.com/arduino-libraries/MIDIUSB)
- U8glib            (https://github.com/olikraus/U8glib_Arduino)

Verwendete Komponenten:
- Pro Micro Mikrocontroller
- 10k Potentiometer
- Taster
- 5mm ws2812b
- 128*64 OLED Display
- Klinkenbuchsen
- RJ45 Buchsen
- USB B Buchse

https://github.com/mastaschief/MidiUSBController
