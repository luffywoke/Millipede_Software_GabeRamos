#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// --- SoftwareSerial for DFPlayer ---
SoftwareSerial mySoftwareSerial(10,11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Pin Assignments 
const int PIN_BUTTON  = 5;   // Momentary metal push button
const int PIN_BLUE = 2; // Colors for button 👇
const int PIN_GREEN = 3; 
const int PIN_RED = 4;
const int PIN_EXT     = 7;   // LED ring data pin
const int PIN_INT     = 6;




// LED Ring Setup 
#define NUMPIXELS 24
Adafruit_NeoPixel extRing(NUMPIXELS, PIN_EXT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel intRing(NUMPIXELS, PIN_INT, NEO_GRB + NEO_KHZ800);

// Timing 
const unsigned long PRESENTATION_DURATION = 120000; // 2 minutes for whole presentation
const unsigned long INTERIOR_DELAY = 35000; // 35 seconds for start of presentation

// State 
bool presentationActive     = false;
bool intLightActive = false;
unsigned long presentationStart = 0;

int buttonState;
int lastButtonState = LOW;


void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  pinMode(PIN_BUTTON,  INPUT_PULLUP);
  pinMode(PIN_BLUE, OUTPUT); // Initializing the color of LED Button

  digitalWrite(PIN_BLUE, LOW);

  extRing.begin();
  extRing.setBrightness(50);
  extRing.show();

  setGreen(); // Default state — green on startup

  intRing.begin();
  intRing.setBrightness(50);
  intRing.show();

  setLightRed(); // Light red for interior

  delay(1000);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer failed to initialize!");
    while(true);
  }

  
  Serial.println("System ready — Green ON");
}


void loop() {
  buttonState = digitalRead(PIN_BUTTON);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW && !presentationActive) {
      startPresentation();
      digitalWrite(PIN_BLUE, HIGH);
    }
    delay(50);
  }

  lastButtonState = buttonState;

  // Check if presentation time is up
  if (presentationActive) {
    if (millis() - presentationStart >= PRESENTATION_DURATION) {
      endPresentation();
      digitalWrite(PIN_BLUE, LOW);
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

 // Plays narration in this state
  myDFPlayer.playFolder(2,1);
  

  Serial.println("Presentation started — Red ON");
}


void endPresentation() {
  presentationActive = false;
  intLightActive = true;

  myDFPlayer.stop();

  setGreen();
  setLightRed();

  Serial.println("Presentation ended — Green ON");
}

// When presentation is active, wait a couple seconds 
// and then interior light turns off
void lightRedOff() {
  for (int brightness = 127; brightness >= 0; brightness--) {
    for (int i = 0; i < NUMPIXELS; i++) {
      intRing.setPixelColor(i, intRing.Color(brightness * 2, brightness, brightness));
    }
    intRing.show();
    delay(15); // Controls fade speed — higher = slower fade
  }
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
