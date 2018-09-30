This sketch is made for an ESP8266 Wifi chip. For help on programming ESP8266 variants see: 
https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/

Turns the ESP into a simple web server where you can toggle it's GPIO pin from a button on a website it serves.
This version also queries time.nist.gov to provide accurate local 24-hour time.

This project requies that you have the following two libraries installed:
- Timezone can be found at: https://github.com/JChristensen/Timezone
- TimeLib can be found at: https://github.com/PaulStoffregen/Time
See the Arduino documentation for installing libraries.