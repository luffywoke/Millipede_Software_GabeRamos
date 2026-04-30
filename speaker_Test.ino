// --- Pin Assignments ---
const int PIN_BUTTON  = 2;   // Momentary push button
const int PIN_SPEAKER = 10;   // Speaker positive

// --- State ---
int buttonState;
int lastButtonState = LOW;


void setup() {
  pinMode(PIN_BUTTON,  INPUT_PULLUP);
  pinMode(PIN_SPEAKER, OUTPUT);

  Serial.begin(9600);
  Serial.println("System ready — Press button to play beep");
}


void loop() {
  buttonState = digitalRead(PIN_BUTTON);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      tone(PIN_SPEAKER, 500, 500); // 1000Hz, 500ms duration
      Serial.println("Playing beep!");
    }
    delay(50);
  }

  lastButtonState = buttonState;
}
