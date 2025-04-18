# KeypadSim Arduino Library

KeypadSim is an Arduino library for simulating a 4x3 matrix keypad. It allows you to queue keypresses programmatically, making it ideal for testing, automation, or simulating user input on devices that expect a physical keypad.

## Features
- Simulate keypresses for a 4x3 matrix keypad (keys: 0-9, C, R)
- Non-blocking operation (call `loop()` regularly)
- Command queue for multiple keypresses

## Installation

### Arduino IDE

To use this library with the Arduino IDE, follow these steps:
1. Go to Sketch > Include Library > Manage Libraries.
2. In the Library Manager, search for "KeypadSim".
3. Click on the "Install" button next to the KeypadSim library.

### PlatformIO

To use this library with PlatformIO, add the following to your `platformio.ini` file:

```ini
lib_deps = 
    https://github.com/probonopd/KeypadSim
```
## Wiring

Connect your Arduino to a device that would normally be controlling a matrix keypad as shown below.

Keypad (front view)

```
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

| Keypad Pins | Arduino Pins | Wire Color |
|-------------|--------------|------------|
| ROW0        | D4           | brown      |
| ROW1        | D5           | red        |
| ROW2        | D6           | orange     |
| ROW3        | D7           | yellow     |
| COL0        | D8           | green      |
| COL1        | D9           | blue       |
| COL2        | D10          | purple     |

Wire the keypad rows and columns to the Arduino digital pins as shown above. Use the suggested wire colors for easier identification.

## Usage

The KeypadSim library allows you to simulate keypresses programmatically. To use it, create an instance of the `KeypadSim` class and call the `loop()` method regularly to process queued keypresses.
See the examples for more details.

## ScanMode

The `ScanMode` enum configures how the simulated keypad interacts with the controller:

- `ROWS_PULSED_COLS_READ`: Use this if your controller (the device using the simulated keypad) pulses the rows LOW and reads the columns.
- `COLS_PULSED_ROWS_READ`: Use this if your controller pulses the columns LOW and reads the rows.

Specify the scan mode when constructing the `KeypadSim` object:

```cpp
KeypadSim keypad(rowPins, numRows, colPins, numCols, keyLayout, ROWS_PULSED_COLS_READ);
```

Adjust the mode to match your hardware or simulation needs.

## Examples

### KeypadSimDemo
Demonstrates how to use the KeypadSim library to simulate keypresses on a 4x3 matrix keypad. This sketch allows you to queue keypresses via the serial monitor, which are then sent to the simulated keypad. Useful for testing and automation scenarios where you want to emulate user input programmatically.

### KeypadController
Shows how to use the standard Keypad library to simulate a device that reads a physical keypad, such as a vending machine. This example demonstrates how to read keypresses from the simulated keypad, making it useful for simulating the device side of a keypad interface.

## License

MIT
