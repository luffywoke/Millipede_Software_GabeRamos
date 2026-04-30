#include <Adafruit_NeoPixel.h>

#define PIN        6   // DIN connected to pin 6
#define NUMPIXELS  24  // Number of pixels on your ring

Adafruit_NeoPixel ring(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(50); // Keep brightness low (0-255)
  ring.show();
}

void loop() {
  // Light all pixels green
  for(int i = 0; i < NUMPIXELS; i++) {
    ring.setPixelColor(i, ring.Color(0, 255, 0));
  }
  ring.show();
}
