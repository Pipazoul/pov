# pov
Fork from https://create.arduino.cc/projecthub/theSTEMpedia/persistence-of-vision-pov-display-using-arduino-583d5f
With a few upgrades


## Hardware

### pov-server

The main lolin32 stuff
Controls the led display but also emit a wifi signal to allow animation modification on the led panel

**Webserver**
A Webui with the following features [WIP]
- draw form in a table and display them
- select the declared animations
- strobe mode (time param)
- turn on and off the leds

#### API ROUTES**

**/api/animation/{id}**


**/api/display/off**
**/api/display/on**
**/api/display/set?array=01011101-01011101-01011101-01011101**











