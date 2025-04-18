// This sketch demonstrates how to use the Keypad library to simulate a keypad controller.
// It mocks the behavior of a device that uses a keypad for input, such as a vending machine.
// The simulated device sends pulses to the rows and reads the columns to determine which key is pressed.

#include <Arduino.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

// NOTE: The strange order of the characters is because we need to
// pulse the rows low, but normally the keypad library assumes that the
// colums are pulsed low. So we need to reverse the order of the
// rows and columns in the constructor. This is a bit confusing, but it works.
char keys[ROWS][COLS] = {
  {'1', '4', '7'},
  {'C', '2', '5'},
  {'8', '0', '3'},
  {'6', '9', 'R'}
};

// Rows: brown, red, orange, yellow
// Columns: green, blue, purple
byte rowPins[ROWS] = {4, 5, 6, 7}; // Being pulsed LOW
byte colPins[COLS] = {8, 9, 10}; // Used as input with internal pullup resistors

// NOTE: Reversed order of rowPins and colPins in the constructor
// so that the rows are pulsed LOW and the columns are HIGH
// to match the controller we are simulating.
Keypad keypad = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS);

void setup(){
  Serial.begin(9600);
  while (!Serial) { ; }  // Wait for native USB
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
}
