#ifndef ANALOG_VALUE_SENSOR_H
#define ANALOG_VALUE_SENSOR_H

#include <Arduino.h>
#include "AnalogSensor.h"

class AnalogValueSensor : public AnalogSensor {
private:
    int valueLessThan;
    int valueGreaterThan;
    int lastTriggered = 0;
    int debounceTime = 100;
    void (*onLessThanCallback)();
    void (*onGreaterThanCallback)();
    void (*onResetCallback)();

public:
    AnalogValueSensor(
        int p, int lessThan, int greaterThan, int debounceTime,
        void (*lessThanCallback)() = nullptr,
        void (*greaterThanCallback)() = nullptr,
        void (*resetCallback)() = nullptr
    ) : AnalogSensor(p), valueLessThan(lessThan), valueGreaterThan(greaterThan), debounceTime(debounceTime),
        onLessThanCallback(lessThanCallback), onGreaterThanCallback(greaterThanCallback),
        onResetCallback(resetCallback) {}

    void update() override {
        AnalogSensor::update();
        int value = AnalogSensor::getValue();

        if (value < valueLessThan) {
            if (millis() - lastTriggered > debounceTime && onLessThanCallback) {
                lastTriggered = millis();
                onLessThanCallback();
            }
        } else if (value > valueGreaterThan) {
            if (millis() - lastTriggered > debounceTime && onGreaterThanCallback) {
                lastTriggered = millis();
                onGreaterThanCallback();
            }
        } else {
            if (onResetCallback) {
                lastTriggered = millis();
                onResetCallback();
            }
        }
    }
};

#endif // ANALOG_VALUE_SENSOR_H
