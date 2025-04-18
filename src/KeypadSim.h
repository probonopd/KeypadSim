#ifndef KEYPAD_SIM_H
#define KEYPAD_SIM_H

#include <Arduino.h>

class KeypadSim {
public:
    static const byte ROWS = 4;
    static const byte COLS = 3;

    KeypadSim(const byte rowPins[ROWS], const byte colPins[COLS], unsigned long keyPressDurationMs = 10);
    void begin();
    void loop();
    void queueKey(char key);
    bool isIdle() const;

private:
    char keys[ROWS][COLS] = {
        { '1','2','3' },
        { '4','5','6' },
        { '7','8','9' },
        { 'C','0','R' }
    };
    char commandBuffer[16];
    uint8_t bufHead = 0, bufTail = 0;
    int currentKeyRow = -1;
    int currentKeyCol = -1;
    bool waitingForRowPulse = false;
    unsigned long keyPressLatchTime = 0;
    unsigned long keyPressDuration;
    byte rowPins[ROWS];
    byte colPins[COLS];

    void enqueueCommand(char c);
    bool dequeueCommand(char &out);
    void simulateKeyPress(char key);
};

#endif // KEYPAD_SIM_H
