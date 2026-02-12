# 🚀 Mission Control: Multi-Device GPIO Controller

This project drives three NeoPixel Rings (RGB) and one Lightbox Strand
(RGBW) using separate GPIO pins on a Raspberry Pi 4B.

------------------------------------------------------------------------

## 🛠 Prerequisites

-   **Hardware:** Raspberry Pi 4B\
-   **OS:** Debian Trixie (64-bit)\
-   **Power:** External 5V 10A supply (Shared Ground with Pi)\
-   **Logic:** 74AHCT125 Level Shifter (Recommended for 3.3V to 5V data
    conversion)

------------------------------------------------------------------------

## 🔌 Hardware Map

  Device            BCM Pin   Physical Pin   Mode
  ----------------- --------- -------------- -----------------
  Ring 1            18        12             PWM0
  Ring 2            13        33             PWM1
  Ring 3            12        32             PWM0 (Alt)
  Lightbox (RGBW)   19        35             PWM1 (Alt)
  Master Button     24        18             Input (Pull-Up)

------------------------------------------------------------------------

## 📦 Dependencies & Setup

### 1️⃣ Install System Library

``` bash
sudo apt-get install pigpio
```

### 2️⃣ Install Node Modules

``` bash
npm install rpio pigpio-ws281x
```

### 3️⃣ Enable Hardware Access

Run:

``` bash
sudo raspi-config
```

Navigate to:

    Interface Options -> Legacy GPIO -> Yes

Reboot the Pi.

------------------------------------------------------------------------

## ⚠️ Critical Pi Setup Issues

### 1️⃣ The DMA / PWM Limitation

The Raspberry Pi has limited hardware PWM channels. While this script
uses `pigpio` to manage multiple pins, standard GPIO libraries often
conflict.

**Important:** Use `pigpio-ws281x` to ensure timing remains stable
across all 4 pins.

------------------------------------------------------------------------

### 2️⃣ RGBW Data Shifting (SK6812)

The Lightbox uses **SK6812 (RGBW)** LEDs. Standard 3-byte RGB drivers
will cause a color shift because the strip expects **4 bytes per
pixel**.

**Fix:**\
The code treats the 60-pixel strand as an 80-pixel virtual array to
account for the extra White channel bytes.

Use the `setLightboxPixel()` helper function to address pixels
correctly.

------------------------------------------------------------------------

### 3️⃣ Permissions & NVM

Since the script accesses `/dev/mem`, it must run as root.\
If using NVM, `sudo node` will fail.

Run using:

``` bash
sudo $(which node) app.js
```

------------------------------------------------------------------------

### 4️⃣ Ground Looping

If the LEDs flicker or act erratically, ensure the Ground from the
external power supply is physically connected to a Ground pin on the
Raspberry Pi.

Without a common ground, the data signal is unreadable.

------------------------------------------------------------------------

## ▶️ Execution Example

``` bash
sudo /home/dpluml/.nvm/versions/node/v24.13.0/bin/node app.js
```
