const int ledPins[]    = {2, 3, 4};
const int buttonPins[] = {5, 6, 7};

bool ledStates[]       = {false, false, false};
bool buttonPressed[]   = {false, false, false};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (!buttonPressed[i]) {
        buttonPressed[i] = true;
        ledStates[i] = !ledStates[i];
        digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW);
      }
    } else {
      buttonPressed[i] = false;
    }
  }
}
