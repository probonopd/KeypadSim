// KeypadSimDemo.ino - Example usage of KeypadSim library
#include <KeypadSim.h>

const byte rowPins[KeypadSim::ROWS] = {2, 3, 4, 5};
const byte colPins[KeypadSim::COLS] = {6, 7, 8};
KeypadSim keypad(rowPins, colPins);

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }  // Wait for native USB
  keypad.begin();
  Serial.println("KeypadSim ready. Type keys (0-9, C, R) and press Enter.");
}

void loop() {
  keypad.loop();
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') return;
    keypad.queueKey(c);
    Serial.print("Queued key: ");
    Serial.println(c);
  }
}
