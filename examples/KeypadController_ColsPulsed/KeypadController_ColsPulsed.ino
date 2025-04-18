// KeypadController_ColsPulsed.ino - Example controller for COLS_PULSED_ROWS_READ mode
// This sketch demonstrates how to use the Keypad library to simulate a controller that pulses columns LOW and reads rows.
// Use this if your device/controller expects COLS_PULSED_ROWS_READ scan mode.
#include <Arduino.h>
#include <Keypad.h>

const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns

// Standard 4x3 keypad layout (row-major order)
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'C','0','R'}
};

// Rows: brown, red, orange, yellow
// Columns: green, blue, purple
byte rowPins[ROWS] = {4, 5, 6, 7}; // Used as input with internal pullup resistors
byte colPins[COLS] = {8, 9, 10};   // Being pulsed LOW

// Keypad constructor for COLS_PULSED_ROWS_READ: columns pulsed, rows read
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }  // Wait for native USB
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}
