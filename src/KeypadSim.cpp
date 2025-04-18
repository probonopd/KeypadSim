#include "KeypadSim.h"

KeypadSim::KeypadSim(const byte rowPinsIn[ROWS], const byte colPinsIn[COLS], unsigned long keyPressDurationMs)
    : keyPressDuration(keyPressDurationMs) {
    for (byte i = 0; i < ROWS; i++) rowPins[i] = rowPinsIn[i];
    for (byte j = 0; j < COLS; j++) colPins[j] = colPinsIn[j];
}

void KeypadSim::begin() {
    for (byte i = 0; i < ROWS; i++) {
        pinMode(rowPins[i], INPUT_PULLUP);
    }
    for (byte j = 0; j < COLS; j++) {
        pinMode(colPins[j], INPUT_PULLUP);
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
    switch (key) {
        case '1': row=0; col=0; break;
        case '2': row=0; col=1; break;
        case '3': row=0; col=2; break;
        case '4': row=1; col=0; break;
        case '5': row=1; col=1; break;
        case '6': row=1; col=2; break;
        case '7': row=2; col=0; break;
        case '8': row=2; col=1; break;
        case '9': row=2; col=2; break;
        case 'C': case 'c': row=3; col=0; break;
        case '0':           row=3; col=1; break;
        case 'R': case 'r': row=3; col=2; break;
        default:
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
    // 2) If we’re waiting for the controller to scan our row...
    if (waitingForRowPulse) {
        if (digitalRead(rowPins[currentKeyRow]) == LOW) {
            // Controller has pulled the row LOW → latch the key
            pinMode(colPins[currentKeyCol], OUTPUT);
            digitalWrite(colPins[currentKeyCol], LOW);
            keyPressLatchTime = millis();
            waitingForRowPulse = false;
        }
    }
    // 3) If a key is currently held LOW, check for release time
    else if (currentKeyCol >= 0) {
        if (millis() - keyPressLatchTime >= keyPressDuration) {
            // Release the key
            pinMode(colPins[currentKeyCol], INPUT_PULLUP);
            // Reset state
            currentKeyRow = currentKeyCol = -1;
        }
    }
}
