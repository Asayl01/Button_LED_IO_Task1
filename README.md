# Arduino LED Buttons Project
A simple Arduino project to control 3 LEDs using 3 push buttons.  
Each button toggles its corresponding LED ON/OFF on every press.

## Components Required
- Arduino UNO (or compatible)
- 3 × LEDs
- 3 × 1000 kΩ resistors
- 3 × Push buttons
- Jumper wires (Male-Male)
- Breadboard

## Wiring Guide
| LED | Pin | Button | Pin |
|-----|-----|--------|-----|
| 1   | D2  | 1      | D5  |
| 2   | D3  | 2      | D6  |
| 3   | D4  | 3      | D7  |
- Buttons use `INPUT_PULLUP` and connect to GND.
- LEDs are active HIGH (use 1000 kΩ resistor in series).

## Simulation Wiring (Tinkercad)
This is the circuit layout as designed in Tinkercad:
![Wiring Image](Button_Led.png)

## Real-life Circuit (Breadboard Setup)
This is an actual photo of the physical setup on a breadboard:
![Wiring Image](Breadbored_setup.jpg)

## Alternative Control Modes
This project supports multiple interaction patterns for LED control. You can easily switch between these modes by modifying the loop() function while maintaining the same hardware setup.

1. Momentary Mode | LED lights only while pressing the button.
```cpp
void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], digitalRead(buttonPins[i]) == LOW ? HIGH : LOW);
  }
}
```
2. Long Press Mode | 1-second hold required

```cpp
unsigned long pressStart[3] = {0};
const unsigned long LONG_PRESS = 1000;
```
New loop():
```cpp void loop() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (pressStart[i] == 0) pressStart[i] = millis();
      if (millis() - pressStart[i] >= LONG_PRESS) {
        ledStates[i] = !ledStates[i];
        digitalWrite(ledPins[i], ledStates[i]);
        pressStart[i] = 0;
      }
    } else {
      pressStart[i] = 0;
    }
  }
}
```
3. Double-Click Detection
```cpp
unsigned long lastClick[3] = {0};
byte clickCount[3] = {0};
const unsigned long DBL_CLICK_DELAY = 300; // 300ms window
```
New loop():
```cpp
void loop() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW && !buttonPressed[i]) {
      buttonPressed[i] = true;
      if (millis() - lastClick[i] < DBL_CLICK_DELAY) clickCount[i]++;
      else clickCount[i] = 1;
      lastClick[i] = millis();

      if (clickCount[i] == 2) {
        ledStates[i] = !ledStates[i];
        digitalWrite(ledPins[i], ledStates[i]);
        clickCount[i] = 0;
      }
    } else if (digitalRead(buttonPins[i]) == HIGH) {
      buttonPressed[i] = false;
    }
  }
}
```
4. Combo Mode (Press Button 1+2) | Special control when two buttons are pressed together:
```cpp
void loop() {
  // Combo action (Buttons 1+2 control LED 3)
  if (digitalRead(buttonPins[0]) == LOW && digitalRead(buttonPins[1]) == LOW) {
    digitalWrite(ledPins[2], HIGH);
  } else {
    digitalWrite(ledPins[2], LOW);
  }

  // Default toggle for other buttons
  for (int i = 0; i < 2; i++) {
    if (digitalRead(buttonPins[i]) == LOW && !buttonPressed[i]) {
      buttonPressed[i] = true;
      ledStates[i] = !ledStates[i];
      digitalWrite(ledPins[i], ledStates[i]);
    } else if (digitalRead(buttonPins[i]) == HIGH) {
      buttonPressed[i] = false;
    }
  }
}
```


