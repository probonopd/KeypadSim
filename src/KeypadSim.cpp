#include "KeypadSim.h"

KeypadSim::KeypadSim(const byte* rowPinsIn, byte numRows, const byte* colPinsIn, byte numCols, const char* keyLayout, ScanMode scanModeIn, unsigned long keyPressDurationMs)
    : keys(keyLayout), nRows(numRows), nCols(numCols), scanMode(scanModeIn),keyPressDuration(keyPressDurationMs) {
    for (byte i = 0; i < nRows && i < 8; i++) rowPinsStorage[i] = rowPinsIn[i];
    for (byte j = 0; j < nCols && j < 8; j++) colPinsStorage[j] = colPinsIn[j];
    rowPins = rowPinsStorage;
    colPins = colPinsStorage;
}

void KeypadSim::begin() {
    if (scanMode == ROWS_PULSED_COLS_READ) {
        for (byte i = 0; i < nRows; i++) {
            pinMode(rowPins[i], INPUT_PULLUP);
        }
        for (byte j = 0; j < nCols; j++) {
            pinMode(colPins[j], INPUT_PULLUP);
        }
    } else { // COLS_PULSED_ROWS_READ
        for (byte j = 0; j < nCols; j++) {
            pinMode(colPins[j], INPUT_PULLUP);
        }
        for (byte i = 0; i < nRows; i++) {
            pinMode(rowPins[i], INPUT_PULLUP);
        }
    }
    bufHead = bufTail = 0;
    currentKeyRow = currentKeyCol = -1;
    waitingForRowPulse = false;
}

void KeypadSim::queueKey(char key) {
    enqueueCommand(key);
}

bool KeypadSim::isIdle() const {
    return !waitingForRowPulse && currentKeyCol < 0 && bufHead == bufTail;
}

void KeypadSim::enqueueCommand(char c) {
    uint8_t next = (bufHead + 1) % sizeof(commandBuffer);
    if (next != bufTail) {
        commandBuffer[bufHead] = c;
        bufHead = next;
    }
}

bool KeypadSim::dequeueCommand(char &out) {
    if (bufHead == bufTail) return false;
    out = commandBuffer[bufTail];
    bufTail = (bufTail + 1) % sizeof(commandBuffer);
    return true;
}

void KeypadSim::simulateKeyPress(char key) {
    int row = -1, col = -1;
    for (byte r = 0; r < nRows; r++) {
        for (byte c = 0; c < nCols; c++) {
            if (keys[r * nCols + c] == key) {
                row = r;
                col = c;
                break;
            }
        }
        if (row != -1) break;
    }
    if (row == -1 || col == -1) {
        // Invalid key, ignore
        return;
    }
    currentKeyRow = row;
    currentKeyCol = col;
    waitingForRowPulse = true;
}

void KeypadSim::loop() {
    // 1) If idle, start next queued key
    if (!waitingForRowPulse && currentKeyCol < 0) {
        char nextKey;
        if (dequeueCommand(nextKey)) {
            simulateKeyPress(nextKey);
        }
    }
    // 2) If we’re waiting for the controller to scan our row or column...
    if (waitingForRowPulse) {
        if (scanMode == ROWS_PULSED_COLS_READ) {
            if (digitalRead(rowPins[currentKeyRow]) == LOW) {
                // Controller has pulled the row LOW → latch the key
                pinMode(colPins[currentKeyCol], OUTPUT);
                digitalWrite(colPins[currentKeyCol], LOW);
                keyPressLatchTime = millis();
                waitingForRowPulse = false;
            }
        } else { // COLS_PULSED_ROWS_READ
            if (digitalRead(colPins[currentKeyCol]) == LOW) {
                // Controller has pulled the column LOW → latch the key
                pinMode(rowPins[currentKeyRow], OUTPUT);
                digitalWrite(rowPins[currentKeyRow], LOW);
                keyPressLatchTime = millis();
                waitingForRowPulse = false;
            }
        }
    }
    // 3) If a key is currently held LOW, check for release time
    else if (currentKeyCol >= 0) {
        if (millis() - keyPressLatchTime >= keyPressDuration) {
            // Release the key
            if (scanMode == ROWS_PULSED_COLS_READ) {
                pinMode(colPins[currentKeyCol], INPUT_PULLUP);
            } else { // COLS_PULSED_ROWS_READ
                pinMode(rowPins[currentKeyRow], INPUT_PULLUP);
            }
            // Reset state
            currentKeyRow = currentKeyCol = -1;
        }
    }
}
