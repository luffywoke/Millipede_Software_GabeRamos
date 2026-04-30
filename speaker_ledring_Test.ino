

#include <Adafruit_NeoPixel.h>

// --- Pin Assignments ---
const int PIN_BUTTON  = 2;   // Momentary push button
const int PIN_EXT     = 6;   // LED ring data pin
const int PIN_INT     = 5;
const int PIN_SPEAKER = 10;   // Speaker


// --- LED Ring Setup ---
#define NUMPIXELS 24
Adafruit_NeoPixel extRing(NUMPIXELS, PIN_EXT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel intRing(NUMPIXELS, PIN_INT, NEO_GRB + NEO_KHZ800);

// --- Timing ---
const unsigned long PRESENTATION_DURATION = 10000; // 10 seconds for testing
const unsigned long INTERIOR_DELAY = 5000; // 5 seconds for testing

// --- State ---
bool presentationActive     = false;
bool intLightActive = false;
unsigned long presentationStart = 0;

int buttonState;
int lastButtonState = LOW;


void setup() {
  pinMode(PIN_BUTTON,  INPUT_PULLUP);
  pinMode(PIN_SPEAKER, OUTPUT);

  extRing.begin();
  extRing.setBrightness(50);
  extRing.show();

  setGreen(); // Default state — green on startup

  intRing.begin();
  intRing.setBrightness(50);
  intRing.show();

  setLightRed(); // Light red for interior

  Serial.begin(9600);
  Serial.println("System ready — Green ON");
}


void loop() {
  buttonState = digitalRead(PIN_BUTTON);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW && !presentationActive) {
      startPresentation();
    }
    delay(50);
  }

  lastButtonState = buttonState;

  // Check if presentation time is up
  if (presentationActive) {
    if (millis() - presentationStart >= PRESENTATION_DURATION) {
      endPresentation();
    }
  }
  if (presentationActive && intLightActive) {  
    if (millis() - presentationStart >= INTERIOR_DELAY) {
      lightRedOff();
      intLightActive = false;
    }
  }
} 


void startPresentation() {
  presentationActive  = true;
  intLightActive = true;
  presentationStart   = millis();

  setRed();
  tone(PIN_SPEAKER, 1000, 500); // Beep once at start

  Serial.println("Presentation started — Red ON");
}


void endPresentation() {
  presentationActive = false;
  intLightActive = true;
  setGreen();
  setLightRed();

  Serial.println("Presentation ended — Green ON");
}

// When presentation is active, wait a couple seconds 
// and then interior light turns off
void lightRedOff() {
  for (int i = 0; i < NUMPIXELS; i++) {
    intRing.setPixelColor(i, intRing.Color(0, 0, 0));
  }
  intRing.show();
}


void setGreen() {
  for(int i = 0; i < NUMPIXELS; i++) {
    extRing.setPixelColor(i, extRing.Color(0, 255, 0));
  }
  extRing.show();
}


void setRed() {
  for(int i = 0; i < NUMPIXELS; i++) {
    extRing.setPixelColor(i, extRing.Color(255, 0, 0));
  }
  extRing.show();
}

void setLightRed() {
  for (int i = 0; i < NUMPIXELS; i++) {
    intRing.setPixelColor(i, intRing.Color(255, 127, 127));
  }
  intRing.show();
}