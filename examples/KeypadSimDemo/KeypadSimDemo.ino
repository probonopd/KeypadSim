// KeypadSimDemo.ino - Example usage of KeypadSim library
#include <KeypadSim.h>

// Example for a 4x3 keypad layout (row-major order)
const char KEYPAD_LAYOUT[12] = {
  '1','2','3',
  '4','5','6',
  '7','8','9',
  'C','0','R'
};

const byte ROWS = 4;
const byte COLS = 3;
const byte rowPins[ROWS] = {4, 5, 6, 7};
const byte colPins[COLS] = {8, 9, 10};
KeypadSim keypad(rowPins, ROWS, colPins, COLS, KEYPAD_LAYOUT);

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
    
    // Return if not one of the valid keys
    if (strchr(KEYPAD_LAYOUT, c) == nullptr) {
      Serial.println("Invalid key. Use 0-9, C, R.");
      return;
    }
    
    keypad.queueKey(c);
    Serial.print("Queued key: ");
    Serial.println(c);
  }
}
