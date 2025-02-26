#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual int getValue() = 0;
};

#endif // SENSOR_H
