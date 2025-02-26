#ifndef DIGITAL_SENSOR_H
#define DIGITAL_SENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class DigitalSensor : public Sensor {
private:
    int pin;
    int value;

public:
    DigitalSensor(int p) : pin(p), value(0) {}

    void setup() override {
        pinMode(pin, INPUT);
    }

    void update() override {
        value = digitalRead(pin);
    }

    int getValue() override {
        return value;
    }
};

#endif // DIGITAL_SENSOR_H
