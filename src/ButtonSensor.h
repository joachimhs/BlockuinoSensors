#ifndef BUTTON_SENSOR_H
#define BUTTON_SENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class ButtonSensor : public Sensor {
private:
    int pin;
    int delayMs;
    bool isPressed;
    int currentState;
    int startTime;
    void (*onPressedCallback)();
    void (*onReleasedCallback)();
    void (*onClickedCallback)();
    void (*onResetCallback)();

public:
    ButtonSensor(
        int p, int ms,
        void (*pressedCallback)() = nullptr,
        void (*releasedCallback)() = nullptr,
        void (*clickedCallback)() = nullptr,
        void (*resetCallback)() = nullptr
    ) : pin(p), delayMs(ms), isPressed(false), currentState(HIGH), startTime(0),
        onPressedCallback(pressedCallback), onReleasedCallback(releasedCallback),
        onClickedCallback(clickedCallback), onResetCallback(resetCallback) {}

    void setup() override {
        pinMode(pin, INPUT_PULLUP);
    }

    void update() override {
        currentState = digitalRead(pin);

        if (currentState == LOW && !isPressed) { // Button pressed
            isPressed = true;
            if (onPressedCallback) onPressedCallback();
        } else if (currentState == HIGH && isPressed) { // Button released
            isPressed = false;
            if (onReleasedCallback) onReleasedCallback();
            if (onClickedCallback) onClickedCallback();
            startTime = millis();
        }

        if (startTime > 0 && millis() - startTime > delayMs) {
            if (onResetCallback) onResetCallback();
            startTime = 0;
        }
    }

    int getValue() override {
        return currentState;
    }
};

#endif // BUTTON_SENSOR_H
