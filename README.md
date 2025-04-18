# KeypadSim Arduino Library

KeypadSim is an Arduino library for simulating a matrix keypad. It allows you to queue keypresses programmatically, making it ideal for testing, automation, or simulating user input on devices that expect a physical keypad.

## Features
- Simulate keypresses for a matrix keypad
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

## Examples

### KeypadSimDemo
Demonstrates how to use the KeypadSim library to simulate keypresses on a 4x3 matrix keypad. This sketch allows you to queue keypresses via the serial monitor, which are then sent to the simulated keypad. Useful for testing and automation scenarios where you want to emulate user input programmatically.

### KeypadController
Shows how to use the standard Keypad library to simulate a device that reads a physical keypad, such as a vending machine. This example demonstrates how to read keypresses from the simulated keypad, making it useful for simulating the device side of a keypad interface.


## API Reference

### KeypadSim Class

- **KeypadSim(rowPins, numRows, colPins, numCols, keyLayout, scanMode)**
  - Constructor. Initializes the simulated keypad.
  - `rowPins`: array of row pin numbers
  - `numRows`: number of rows
  - `colPins`: array of column pin numbers
  - `numCols`: number of columns
  - `keyLayout`: 2D array of key characters
  - `scanMode`: `ROWS_PULSED_COLS_READ` or `COLS_PULSED_ROWS_READ`

- **void queueKey(char key)**
  - Queues a keypress for simulation.

- **void loop()**
  - Call regularly to process the keypress queue.

### ScanMode Enum
- `ROWS_PULSED_COLS_READ`: Use this if your controller pulses the rows LOW and reads the columns.
- `COLS_PULSED_ROWS_READ`: Use this if your controller pulses the columns LOW and reads the rows.

## Troubleshooting

### No keypresses are detected
- Ensure you are calling `keypad.loop()` regularly in your main loop.
- Double-check your wiring and pin assignments.
- Make sure the scan mode matches your controller's expectations.

### Keypresses are missed or repeated
- Try increasing the delay between queued keypresses.
- Check for debounce issues in your controller code.

### Build errors in PlatformIO or Arduino IDE
- Ensure you are using a supported platform (e.g., AVR, SAM).
- Update PlatformIO or Arduino IDE to the latest version.
- Check that all required dependencies are installed.

For further help, open an issue on the [GitHub repository](https://github.com/probonopd/KeypadSim/issues).
