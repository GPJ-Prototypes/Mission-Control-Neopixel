#include <Adafruit_NeoPixel.h>

#define RING_PIN     6
#define STRIP_PIN    7
#define BUTTON_PIN   2

#define RING_COUNT   16     // change to your ring size
#define STRIP_COUNT  60     // change to your strip length

// Ring is usually RGB
Adafruit_NeoPixel ring(RING_COUNT, RING_PIN, NEO_GRB + NEO_KHZ800);

// Strip is RGBW
Adafruit_NeoPixel strip(STRIP_COUNT, STRIP_PIN, NEO_GRBW + NEO_KHZ800);

bool lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  ring.begin();
  strip.begin();

  ring.clear();
  strip.clear();

  ring.show();
  strip.show();
}

void loop() {

  // ------------------------
  // SERIAL CONTROL
  // ------------------------
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == '1') {
      setRingGreen();
    }

    if (cmd == '0') {
      clearRing();
    }
  }

  // ------------------------
  // BUTTON CONTROL
  // ------------------------
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    triggerStripWhite();
  }

  lastButtonState = buttonState;
}


// ========================
// FUNCTIONS
// ========================

void setRingGreen() {
  for (int i = 0; i < RING_COUNT; i++) {
    ring.setPixelColor(i, ring.Color(0, 255, 0));
  }
  ring.show();
}

void clearRing() {
  ring.clear();
  ring.show();
}

void triggerStripWhite() {

  // Turn on RGBW white channel only
  for (int i = 0; i < STRIP_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
  }
  strip.show();

  delay(3000);

  strip.clear();
  strip.show();
}
