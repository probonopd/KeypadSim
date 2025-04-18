#ifndef KEYPAD_SIM_H
#define KEYPAD_SIM_H

#include <Arduino.h>

class KeypadSim {
public:
    KeypadSim(const byte* rowPins, byte numRows, const byte* colPins, byte numCols, const char* keyLayout, unsigned long keyPressDurationMs = 10);
    void begin();
    void loop();
    void queueKey(char key);
    bool isIdle() const;

private:
    const char* keys = nullptr; // Pointer to key layout (row-major order)
    byte nRows = 0;
    byte nCols = 0;
    char commandBuffer[16];
    uint8_t bufHead = 0, bufTail = 0;
    int currentKeyRow = -1;
    int currentKeyCol = -1;
    bool waitingForRowPulse = false;
    unsigned long keyPressLatchTime = 0;
    unsigned long keyPressDuration;
    byte rowPinsStorage[8]; // Support up to 8 rows
    byte colPinsStorage[8]; // Support up to 8 cols
    const byte* rowPins = nullptr;
    const byte* colPins = nullptr;

    void enqueueCommand(char c);
    bool dequeueCommand(char &out);
    void simulateKeyPress(char key);
};

#endif // KEYPAD_SIM_H
