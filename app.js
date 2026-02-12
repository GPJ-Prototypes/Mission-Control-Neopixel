/**
 * GCN26 MISSION CONTROL - HARDWARE INTERFACE
 * 3 Nornal LEDs with a Neopixel RBGW strip
 */

const rpio = require('rpio');
const ws281x = require('rpi-ws281x');

// Physical 32 (GPIO 12) | Physical 33 (GPIO 13) | Physical 35 (GPIO 19)
const INDICATOR_PINS = [32, 33, 35]; 

// BUTTON_PIN: Physical 18 (GPIO 24)
const BUTTON_PIN = 18;               

// PIXEL_PIN: GPIO 18 (Physical Pin 12) 
// Note: ws281x library REQUIRES the GPIO/BCM number (18)
const PIXEL_PIN = 18;                

const NUM_PIXELS = 8; // Updated for 8-pixel strip

// --- INITIALIZATION ---

// 1. Setup rpio for Indicators and Button
rpio.init({ mapping: 'physical' });
INDICATOR_PINS.forEach(pin => rpio.open(pin, rpio.OUTPUT, rpio.LOW));
rpio.open(BUTTON_PIN, rpio.INPUT, rpio.PULL_UP);

// 2. Setup Neopixels for Lightbox
ws281x.configure({ 
    leds: NUM_PIXELS, 
    gpio: PIXEL_PIN, 
    brightness: 100, // Full brightness for mission control
    dma: 10 
});
const pixelData = new Uint32Array(NUM_PIXELS);

// --- FUNCTIONS ---

/**
 * Toggles the 12V Indicators (via MOSFET board)
 * @param {number} index - 0, 1, or 2
 * @param {boolean} state - true for ON, false for OFF
 */
function setIndicator(index, state) {
    if (index < 0 || index >= INDICATOR_PINS.length) return;
    rpio.write(INDICATOR_PINS[index], state ? rpio.HIGH : rpio.LOW);
    console.log(`Indicator ${index + 1} (Pin ${INDICATOR_PINS[index]}): ${state ? 'ON' : 'OFF'}`);
}

/**
 * Fires the Lightbox (White flash)
 */
function triggerLightbox() {
    console.log("--> LIGHTBOX: ALERT (WHITE)");
    // Set all pixels to White
    for (let i = 0; i < NUM_PIXELS; i++) pixelData[i] = 0xFFFFFF;
    ws281x.render(pixelData);
    
    // Auto-off after 2 seconds
    setTimeout(() => {
        for (let i = 0; i < NUM_PIXELS; i++) pixelData[i] = 0x000000;
        ws281x.render(pixelData);
        console.log("--> LIGHTBOX: RESET");
    }, 2000);
}

// --- MAIN EXECUTION ---
console.log("Start");

// Startup Sequence: Turn on Indicators one by one
INDICATOR_PINS.forEach((pin, i) => {
    setTimeout(() => {
        setIndicator(i, true);
    }, i * 500);
});

// Main Loop: Poll for Button Press (Physical Pin 18)
setInterval(() => {
    if (rpio.read(BUTTON_PIN) === rpio.LOW) {
        triggerLightbox();
    }
}, 100);

// Cleanup
process.on('SIGINT', () => {
    console.log("\nShutting down hardware...");
    ws281x.reset();
    INDICATOR_PINS.forEach((pin, i) => setIndicator(i, false));
    process.exit();
});