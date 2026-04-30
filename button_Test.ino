const int buttonPin = 2;    
const int ledPin = 7;      

int ledState = LOW;         // current state of the LED
int buttonState;            // current reading from the input pin
int lastButtonState = LOW;  // previous reading from the input pin

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState); // set initial LED state
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // If the state has changed, check if it's currently HIGH (pressed)
    if (buttonState == HIGH) {
      ledState = !ledState;      // Toggle the LED state variable
      digitalWrite(ledPin, ledState); 
    }
    // Small delay to "debounce" the button (prevent flickering)
    delay(50); 
  }
  // Save the current state as the last state for the next loop
  lastButtonState = buttonState;
}
