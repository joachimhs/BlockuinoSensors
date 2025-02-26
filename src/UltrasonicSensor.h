#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class UltrasonicSensor : public Sensor {
private:
    int echoPin;
    int trigPin;
    int delayMs;
    int shortDistanceThreshold;
    int currDistance;
    int startTime;
    void (*onShortDistanceCallback)();
    void (*onResetCallback)();

public:
    UltrasonicSensor(
        int echoP, int trigP, int shortDistance, int ms,
        void (*shortDistanceCallback)() = nullptr,
        void (*resetCallback)() = nullptr
    ) : echoPin(echoP), trigPin(trigP), shortDistanceThreshold(shortDistance),
        delayMs(ms), currDistance(0), startTime(-1),
        onShortDistanceCallback(shortDistanceCallback), onResetCallback(resetCallback) {}

    void setup() override {
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }

    void update() override {
        currDistance = ultrasonicDistance();

        if (currDistance <= shortDistanceThreshold && startTime < 0) {
            if (onShortDistanceCallback) onShortDistanceCallback();
            startTime = millis();
        }

        if (startTime > 0 && millis() - startTime > delayMs) {
            if (onResetCallback) onResetCallback();
            startTime = -1;
        }
    }

    int getValue() override {
        return currDistance;
    }

private:
    int ultrasonicDistance() {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        long duration = pulseIn(echoPin, HIGH);
        return static_cast<int>(duration * 0.034 / 2); // Convert to cm
    }
};

#endif // ULTRASONIC_SENSOR_H
