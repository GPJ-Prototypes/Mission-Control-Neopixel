#include <Adafruit_NeoPixel.h>

#define STRAND_PIN     4
#define STRAND_PIXELS  10

const int ledPin = 13;

Adafruit_NeoPixel strand(STRAND_PIXELS, STRAND_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(ledPin, OUTPUT);      // pinMode first
  digitalWrite(ledPin, HIGH);   // then set it on

  Serial.begin(115200);
  strand.begin();
  strand.setBrightness(128);
  strand.show();
  delay(1000);
  Serial.println("WS2815 10px Test Starting...");
}

void loop() {

  // --- Solid White ---
  Serial.println("Solid White");
  for (int i = 0; i < STRAND_PIXELS; i++) strand.setPixelColor(i, strand.Color(255, 255, 255));
  strand.show();
  delay(3000);

  // --- Red ---
  Serial.println("Red");
  for (int i = 0; i < STRAND_PIXELS; i++) strand.setPixelColor(i, strand.Color(255, 0, 0));
  strand.show();
  delay(2000);

  // --- Green ---
  Serial.println("Green");
  for (int i = 0; i < STRAND_PIXELS; i++) strand.setPixelColor(i, strand.Color(0, 255, 0));
  strand.show();
  delay(2000);

  // --- Blue ---
  Serial.println("Blue");
  for (int i = 0; i < STRAND_PIXELS; i++) strand.setPixelColor(i, strand.Color(0, 0, 255));
  strand.show();
  delay(2000);

  // --- Chase ---
  Serial.println("Chase");
  strand.clear();
  for (int i = 0; i < STRAND_PIXELS; i++) {
    strand.setPixelColor(i, strand.Color(255, 255, 255));
    if (i > 0) strand.setPixelColor(i - 1, 0);
    strand.show();
    delay(30);
  }
  strand.clear();
  strand.show();
  delay(500);

  Serial.println("--- Restarting ---\n");
  delay(1000);
}