# KeypadSim Arduino Library

KeypadSim is an Arduino library for simulating a 4x3 matrix keypad. It allows you to queue keypresses programmatically, making it ideal for testing, automation, or simulating user input on devices that expect a physical keypad.

## Features
- Simulate keypresses for a 4x3 matrix keypad (keys: 0-9, C, R)
- Non-blocking operation (call `loop()` regularly)
- Command queue for multiple keypresses

## Usage

### 1. Wiring
Connect your Arduino to a device that would normally be controlling a matrix keypad as shown below.

```
Keypad Pins:         Arduino Pins:      Wire Color

[ROW0] ------------- D4                brown
[ROW1] ------------- D5                red
[ROW2] ------------- D6                orange
[ROW3] ------------- D7                yellow

[COL0] ------------- D8                green
[COL1] ------------- D9                blue
[COL2] ------------- D10               purple
```

// Rows: brown, red, orange, yellow
// Columns: green, blue, purple

```
Keypad (front view)
+---+---+---+
| 1 | 2 | 3 |   ROW0 (D4, brown)
+---+---+---+
| 4 | 5 | 6 |   ROW1 (D5, red)
+---+---+---+
| 7 | 8 | 9 |   ROW2 (D6, orange)
+---+---+---+
| C | 0 | R |   ROW3 (D7, yellow)
+---+---+---+

|   |   |   |
|   |   |   +-- COL2 (D10, purple)
|   |   +------ COL1 (D9, blue)
|   +---------- COL0 (D8, green)
```

Wire the keypad rows and columns to the Tuino096 digital pins as shown above. Use the suggested wire colors for easier identification.

### 2. Example Sketch
See `examples/KeypadSimDemo/KeypadSimDemo.ino` for a complete example. Basic usage:

```cpp
#include <KeypadSim.h>

const byte rowPins[KeypadSim::ROWS] = {4, 5, 6, 7};
const byte colPins[KeypadSim::COLS] = {8, 9, 10};
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
```

### 3. API
- `KeypadSim(const byte rowPins[ROWS], const byte colPins[COLS], unsigned long keyPressDurationMs = 10)`
- `void begin()`
- `void loop()`
- `void queueKey(char key)`
- `bool isIdle() const`

## License
MIT