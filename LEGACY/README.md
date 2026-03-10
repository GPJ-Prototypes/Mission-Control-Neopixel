# Mission Control: Breadboard Prototype

A Node.js interface to control **3 Green LEDs** (simulating 12V
indicators)
and one **8-pixel Neopixel strip** via a Raspberry Pi 4B. (Hardware I have on hand)


Added a (Arduino) Teensy script. THis is a much easier way to go if we can. This test just has the Neopixel ring and small strip. This will be the easier way to go depending on where the app lives. 

------------------------------------------------------------------------

## 🛠 Prerequisites

**Hardware:** Raspberry Pi 4B
**OS:** Debian Trixie (64-bit)
**Node.js:** v20.20.0
**Permissions:** Script must run with `sudo` for hardware access.

------------------------------------------------------------------------

## 🔌 Hardware Setup (The Holes)

Connect your components to these **Physical Pin numbers**
(the hole count on the board).

  Component     Physical Pin   Logic Type   Note
  ------------- -------------- ------------ --------------------------------
  LED 1         32             Output       Future 12V Green Light 1
  LED 2         33             Output       Future 12V Green Light 2
  LED 3         35             Output       Future 12V Green Light 3
  Pixel Strip   12             PWM          8-Pixel Data Line (GPIO 18)
  Button        18             Input        One side to Pin 18, one to GND
  Ground        14             GND          Common Ground for all parts

------------------------------------------------------------------------

## 📦 Installation

**Important:** You must build the drivers on the Pi.\
If you copied a `node_modules` folder from a Mac or PC, delete it first.

``` bash
cd ~/Desktop/GCN26-Mission-Control-Neopixel
rm -rf node_modules package-lock.json
npm install
```

------------------------------------------------------------------------

## 🚀 Execution

Run the script using the absolute path to your Node binary:

``` bash
sudo /home/dpYOUR-PI-NAME/.nvm/versions/node/v20.20.0/bin/node app.js
```
