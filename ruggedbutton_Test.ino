const int PIN_BUTTON = 10;
const int PIN_BLUE = 11; 
const int PIN_GREEN = 12; 
const int PIN_RED = 13;

int buttonState;
int lastButtonState = LOW;

void setup() {
 pinMode(PIN_BUTTON, INPUT_PULLUP);
 pinMode(PIN_BLUE, OUTPUT);
 pinMode(PIN_GREEN, OUTPUT);
 pinMode(PIN_RED, OUTPUT);

 digitalWrite(PIN_BLUE, LOW);
 digitalWrite(PIN_GREEN, HIGH);
 digitalWrite(PIN_RED, HIGH);

  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(PIN_BUTTON);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      Serial.println("Button was pressed!");
    }
    delay(50);
  }
 lastButtonState = buttonState;

}
