# BlockuinoSensors Library
An Arduino library for simplifying sensor integration in Blockuino projects.

## Features
- Abstract `Sensor` base class for extensibility.
- Support for digital, analog, button, ultrasonic, and analog value sensors.
- Easy-to-use API with consistent structure across sensors.

## Installation
1. Clone this repository into your Arduino `libraries` folder.
2. Restart the Arduino IDE.

## Example
```cpp
#include <BlockuinoSensors.h>

DigitalSensor button(2);

void setup() {
    Serial.begin(9600);
    button.setup();
}

void loop() {
    button.update();
    Serial.println(button.getValue());
}
