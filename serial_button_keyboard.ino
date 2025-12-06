#include <Keyboard.h>

String storedText[3] = {"", "", ""}; // Stores text for each button
const int buttonPins[3] = {2, 3, 4}; // pins 2, 3, and 4
bool buttonPressed[3] = {false, false, false};
bool lastButtonState[3] = {HIGH, HIGH, HIGH};
unsigned long lastDebounceTime[3] = {0, 0, 0};
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  // Read serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input == "\\reset") {
      for (int i = 0; i < 3; i++) {
        storedText[i] = "";
      }
      Serial.println("All stored texts cleared");
    } else if (input == "\\show") {
      for (int i = 0; i < 3; i++) {
        Serial.println("Button " + String(i + 1) + ": " + storedText[i]);
      }
    } else {
      int buttonNum = 0; // Default to button 1
      if (input.startsWith("\\1-")) {
        buttonNum = 0;
        input = input.substring(3);
      } else if (input.startsWith("\\2-")) {
        buttonNum = 1;
        input = input.substring(3);
      } else if (input.startsWith("\\3-")) {
        buttonNum = 2;
        input = input.substring(3);
      }
      storedText[buttonNum] = input;
      Serial.println("Stored for button " + String(buttonNum + 1) + ": " + input);
    }
  }

  // Read each button with debounce
  for (int i = 0; i < 3; i++) {
    int reading = digitalRead(buttonPins[i]);
    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading == LOW && !buttonPressed[i]) {
        buttonPressed[i] = true;
        String text = storedText[i];
        if (text == "\\enter") {
          Keyboard.press(KEY_RETURN);
          delay(100);
          Keyboard.releaseAll();
        } else if (text == "\\delete") {
          Keyboard.press(KEY_BACKSPACE);
          delay(100);
          Keyboard.releaseAll();
        } else {
          int ctrlIndex = text.indexOf("\\ctrl-");
          if (ctrlIndex != -1 && ctrlIndex + 7 < text.length()) {
            char key = text[ctrlIndex + 5];
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(key);
            delay(100);
            Keyboard.releaseAll();
          } else {
            for (int j = 0; j < text.length(); j++) {
              Keyboard.press(text[j]);
              delay(100);
              Keyboard.releaseAll();
              delay(100);
            }
          }
        }
      } else if (reading == HIGH) {
        buttonPressed[i] = false;
      }
    }
    lastButtonState[i] = reading;
  }
}
