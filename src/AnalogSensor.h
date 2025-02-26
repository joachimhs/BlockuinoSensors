#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class AnalogSensor : public Sensor {
private:
    int pin;
    int value;

public:
    AnalogSensor(int p) : pin(p), value(0) {}

    void setup() override {
        pinMode(pin, INPUT);
    }

    void update() override {
        value = analogRead(pin);
    }

    int getValue() override {
        return value;
    }
};

#endif // ANALOG_SENSOR_H
