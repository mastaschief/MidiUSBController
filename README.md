Um Modep(https://blokas.io/modep/) als Multieffektgerät für meinen Bass zu nutzen, habe ich einen Raspberry Pi 4 in ein altes Audiointerface eingebaut. Zur Steurung der Effekte habe ich einen Midi Controller entworfen.
Bilder und 3D Entwürfe:

Aufbau:
Instrumen(Bass)	-> Audiointerface Klinken Input
Midi Controller	-> RasperryPi USB
Externer Controller -> RJ45 Buchse (I2C)
Audioninterface Output -> Endstufe(Bassverstärker)

Funktionen:
- An und Ausschalten der Effekte -> funktioniert

ToDo:
Aufräumen, besser kommentieren
Led Farbe wird nicht richtig gespeichert bzw. geladen
LFO Funktion integrieren
Integration der MenuLEDs
externe Expressionanschlüsse integrieren
externe I2C Client geräte einbinden
Lizenz überprüfen