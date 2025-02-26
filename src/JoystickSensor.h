#ifndef JOYSTICK_SENSOR_H
#define JOYSTICK_SENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#include "AnalogValueSensor.h"
#include "ButtonSensor.h"

class JoystickSensor : public Sensor {
private:
    AnalogValueSensor xAxis; // X-axis sensor
    AnalogValueSensor yAxis; // Y-axis sensor
    ButtonSensor button;     // Button sensor

public:
    JoystickSensor(
        int xPin, int yPin, int buttonPin,
        int xMin, int xMax,
        int yMin, int yMax,
        void (*onXLessThanCallback)() = nullptr,
        void (*onXGreaterThanCallback)() = nullptr,
        void (*onXResetCallback)() = nullptr,
        void (*onYLessThanCallback)() = nullptr,
        void (*onYGreaterThanCallback)() = nullptr,
        void (*onYResetCallback)() = nullptr,
        void (*onButtonPressedCallback)() = nullptr,
        void (*onButtonReleasedCallback)() = nullptr,
        void (*onButtonClickedCallback)() = nullptr,
        void (*onButtonResetCallback)() = nullptr
    )
        : xAxis(xPin, xMin, xMax, onXLessThanCallback, onXGreaterThanCallback, onXResetCallback),
          yAxis(yPin, yMin, yMax, onYLessThanCallback, onYGreaterThanCallback, onYResetCallback),
          button(buttonPin, 0, onButtonPressedCallback, onButtonReleasedCallback, onButtonClickedCallback, onButtonResetCallback) {}

    void setup() override {
        xAxis.setup();
        yAxis.setup();
        button.setup();
    }

    void update() override {
        xAxis.update();
        yAxis.update();
        button.update();
    }

    int getValue() override {
        // This method isn't very meaningful for a joystick sensor as it involves multiple inputs.
        // Instead, you can access individual values using `getXValue`, `getYValue`, or `getButtonState`.
        return 0;
    }

    int getXValue() {
        return xAxis.getValue();
    }

    int getYValue() {
        return yAxis.getValue();
    }

    int getButtonState() {
        return button.getValue();
    }
};

#endif // JOYSTICK_SENSOR_H
