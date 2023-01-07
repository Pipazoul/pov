# pov
Fork from https://create.arduino.cc/projecthub/theSTEMpedia/persistence-of-vision-pov-display-using-arduino-583d5f
With a few upgrades



## Usage

Connect to ssid `pov-server` with password defined in `pov-server/src/conf/wifi-conf.h`

Open a browser and go to `192.168.4.1`

## Hardware

### pov-server

The main lolin32 stuff
Controls the led display but also emit a wifi signal to allow animation modification on the led panel


#### Setup

This project has been setup with platform.io extension on vscode and probably wont work in a standard Arduino IDE environement

Before flashing th loli please setup the following :

Edit `pov-server/src/conf/wifi-conf.h` to change the wifi credentials ans SSID

You also can edit  `pov-server/src/animations.h` if you want to add more default animations


#### Developpement

`src/conf/wifi-conf.h`contains variables related to wifi ssid and credentials

`src/animations.h`contains "led animation variables" and some led animation functions

`src/html.h`contains the html code for the webserver, stored in a variable ( in the future the file will be more dynamic,to permit the loading of dynamic custom animations)

`src/main.cpp` the main code and declaration 

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
**/api/display/










