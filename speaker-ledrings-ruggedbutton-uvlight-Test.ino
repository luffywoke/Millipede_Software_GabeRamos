#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// SoftwareSerial for DFPlayer 
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Pin Assignments 
const int PIN_BUTTON = 5;
const int PIN_BLUE   = 2;
const int PIN_GREEN  = 3;
const int PIN_RED    = 4;
const int PIN_EXT    = 7;
const int PIN_INT    = 6;
const int PIN_RELAY  = 8; // UV light relay

// LED Ring Setup 
#define NUMPIXELS 24
Adafruit_NeoPixel extRing(NUMPIXELS, PIN_EXT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel intRing(NUMPIXELS, PIN_INT, NEO_GRB + NEO_KHZ800);

// Timing 
const unsigned long PRESENTATION_DURATION = 120000; // 2 minutes
const unsigned long INTERIOR_DELAY        = 36000;   // Interior light fade delay
const unsigned long UV_ON_TIME            = 36000;  // UV on at 0:36
const unsigned long UV_OFF_TIME           = 102000; // UV off at 1:42

// State 
bool presentationActive = false;
bool intLightActive     = false;
bool uvLightActive      = false; 
unsigned long presentationStart = 0;

int buttonState;
int lastButtonState = LOW;


void setup() {
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_BLUE,   OUTPUT);
  pinMode(PIN_GREEN,  OUTPUT);
  pinMode(PIN_RED,    OUTPUT);
  pinMode(PIN_RELAY,  OUTPUT); 

  digitalWrite(PIN_RELAY, HIGH); // UV off by default (active LOW) 

  // Default button color — green
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_RED,   HIGH);
  digitalWrite(PIN_BLUE,  HIGH);

  // Exterior ring
  extRing.begin();
  extRing.setBrightness(50);
  extRing.show();
  setGreen();

  // Interior ring
  intRing.begin();
  intRing.setBrightness(50);
  intRing.show();
  setLightRed();

  // DFPlayer
  delay(1000);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer failed to initialize!");
    while(true);
  }
  Serial.println("DFPlayer ready!");
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(30);
  myDFPlayer.EQ(0);
  myDFPlayer.stop();

  Serial.println("System ready — Default State");
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

  // Interior light fade delay
  if (presentationActive && intLightActive) {
    if (millis() - presentationStart >= INTERIOR_DELAY) {
      lightRedOff();
      intLightActive = false;
    }
  }

  
  if (presentationActive && !uvLightActive) {
    if (millis() - presentationStart >= UV_ON_TIME) {
      digitalWrite(PIN_RELAY, LOW); // UV light ON
      uvLightActive = true;
      Serial.println("UV light ON");
    }
  }

  
  if (presentationActive && uvLightActive) {
    if (millis() - presentationStart >= UV_OFF_TIME) {
      digitalWrite(PIN_RELAY, HIGH); // UV light OFF
      uvLightActive = false;
      Serial.println("UV light OFF");
    }
  }
}


void startPresentation() {
  presentationActive = true;
  intLightActive     = true;
  uvLightActive      = false; // *** ADDED ***
  presentationStart  = millis();

  setRed();

  // Button turns red
  digitalWrite(PIN_RED,   LOW);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE,  HIGH);

  // Play audio
  myDFPlayer.playFolder(2, 1);

  Serial.println("Presentation started!");
}


void endPresentation() {
  presentationActive = false;
  intLightActive     = true;

  myDFPlayer.stop();

  digitalWrite(PIN_RELAY, HIGH); // Make sure UV is off *** ADDED ***

  setGreen();
  setLightRed();

  // Button turns green
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_RED,   HIGH);
  digitalWrite(PIN_BLUE,  HIGH);

  Serial.println("Presentation ended — Default State");
}


void lightRedOff() {
  for (int brightness = 127; brightness >= 0; brightness--) {
    for (int i = 0; i < NUMPIXELS; i++) {
      intRing.setPixelColor(i, intRing.Color(brightness * 2, brightness, brightness));
    }
    intRing.show();
    delay(15);
  }
}


void setGreen() {
  for (int i = 0; i < NUMPIXELS; i++) {
    extRing.setPixelColor(i, extRing.Color(0, 255, 0));
  }
  extRing.show();
}


void setRed() {
  for (int i = 0; i < NUMPIXELS; i++) {
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