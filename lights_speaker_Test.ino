

// --- Pin Assignments ---
const int PIN_BUTTON      = 2;
const int PIN_LED_GREEN   = 5;
const int PIN_LED_RED     = 4;
const int PIN_SPEAKER     = 10;

// --- Timing ---
const unsigned long PRESENTATION_DURATION = 10000; // 10 seconds for testing

// --- State ---
bool presentationActive     = false;
unsigned long presentationStart = 0;

int buttonState;
int lastButtonState = LOW;


void setup() {
  pinMode(PIN_BUTTON,    INPUT_PULLUP);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED,   OUTPUT);
  pinMode(PIN_SPEAKER,   OUTPUT);

  // Default state
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_RED,   LOW);

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

  if (presentationActive) {
    if (millis() - presentationStart >= PRESENTATION_DURATION) {
      endPresentation();
    }
  }
}


void startPresentation() {
  presentationActive  = true;
  presentationStart   = millis();

  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED,   HIGH);
  tone(PIN_SPEAKER, 1000, 500); // beep for 500ms

  Serial.println("Presentation started — Red ON, Beep playing");
}


void endPresentation() {
  presentationActive = false;

  digitalWrite(PIN_LED_RED,   LOW);
  digitalWrite(PIN_LED_GREEN, HIGH);

  Serial.println("Presentation ended — Green ON");
}
