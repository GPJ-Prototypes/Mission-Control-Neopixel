#include <Adafruit_NeoPixel.h>

// ─── Pin Definitions ──────────────────────────────────────────────
#define BUTTON_PIN      2
#define MOSFET_PIN      5

#define RING1_PIN       6
#define RING2_PIN       7
#define RING3_PIN       8
#define RING_PIXELS     16

#define STRAND_PIN      4
#define STRAND_PIXELS   684

#define RING_PIXEL_DELAY  30

// ─── NeoPixel Objects ─────────────────────────────────────────────
Adafruit_NeoPixel ring1(RING_PIXELS, RING1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring2(RING_PIXELS, RING2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring3(RING_PIXELS, RING3_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strand(STRAND_PIXELS, STRAND_PIN, NEO_GRB + NEO_KHZ800);

// ─── State ────────────────────────────────────────────────────────
bool ring1Complete = false;
bool ring2Complete = false;
bool ring3Complete = false;
bool ringsComplete = false;
bool strandActive  = false;

// ─── Helpers ──────────────────────────────────────────────────────
void fillRingSequential(Adafruit_NeoPixel &ring, uint32_t color, int delayMs) {
  for (int i = 0; i < RING_PIXELS; i++) {
    ring.setPixelColor(i, color);
    ring.show();
    delay(delayMs);
  }
}

void checkAllRingsComplete() {
  if (ring1Complete && ring2Complete && ring3Complete && !ringsComplete) {
    ringsComplete = true;
    digitalWrite(MOSFET_PIN, HIGH);  // Enable arcade button LED
    Serial.println("STATUS:ALL_RINGS_COMPLETE");
  }
}

void setStrandWhite(bool on) {
  if (on) {
    for (int i = 0; i < STRAND_PIXELS; i++) {
      strand.setPixelColor(i, strand.Color(255, 255, 255));
    }
  } else {
    strand.clear();
  }
  strand.show();
}

// ─── Setup ────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, LOW);

  ring1.begin(); ring1.setBrightness(200); ring1.show();
  ring2.begin(); ring2.setBrightness(200); ring2.show();
  ring3.begin(); ring3.setBrightness(200); ring3.show();

  strand.begin(); strand.setBrightness(255); strand.show();

  Serial.println("Mission Control: Ready — waiting for serial commands");
}

// ─── Serial Handler ───────────────────────────────────────────────
void handleSerial() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    uint32_t green = ring1.Color(0, 255, 0);

    if (cmd == '1' && !ring1Complete) {
      fillRingSequential(ring1, green, RING_PIXEL_DELAY);
      ring1Complete = true;
      Serial.println("STATUS:RING1_COMPLETE");
      checkAllRingsComplete();
    }
    else if (cmd == '2' && !ring2Complete) {
      fillRingSequential(ring2, green, RING_PIXEL_DELAY);
      ring2Complete = true;
      Serial.println("STATUS:RING2_COMPLETE");
      checkAllRingsComplete();
    }
    else if (cmd == '3' && !ring3Complete) {
      fillRingSequential(ring3, green, RING_PIXEL_DELAY);
      ring3Complete = true;
      Serial.println("STATUS:RING3_COMPLETE");
      checkAllRingsComplete();
    }
  }
}

// ─── Main Loop ────────────────────────────────────────────────────
void loop() {
  handleSerial();

  if (!ringsComplete) return;

  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50);
    if (digitalRead(BUTTON_PIN) == LOW) {

      if (!strandActive) {
        setStrandWhite(true);
        strandActive = true;
        Serial.println("STATUS:STRAND_ON");
      } else {
        setStrandWhite(false);
        strandActive = false;
        Serial.println("STATUS:STRAND_OFF");
      }

      while (digitalRead(BUTTON_PIN) == LOW) { delay(10); }
    }
  }
}