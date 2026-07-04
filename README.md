# Ultrasonic Sensor Library

A compact and reliable library for ultrasonic range sensors.

This library supports both two-pin trig/echo modules and single-pin ultrasonic sensors. It is designed for Arduino boards, ESP32 boards that use the Arduino core, and other Arduino-compatible controllers. It works with standard HC-SR04-style modules, single-pin variants, and many compatible ultrasonic sensors.

## What’s new in v1.1.0

- Updated release number to `1.1.0`
- Expanded compatibility guidance for Arduino and ESP32 boards
- Added new example sketches for single-pin and ESP32 use
- Improved README structure and wiring documentation

## Supported sensors

- HC-SR04
- JSN-SR04T
- HY-SRF05 / SRF02 / SRF04 and compatible digital ultrasonic modules
- Single-pin ultrasonic modules

## Supported controllers

- Arduino Uno, Nano, Mega, Leonardo, Micro and boards compatible with the Arduino framework
- ESP32 boards using the Arduino core
- Other 5V/3.3V microcontrollers supported by the Arduino API

> Note: Some ESP32 boards are not 5V tolerant on data pins. Use a voltage divider or level shifter on the echo pin when using 5V ultrasonic modules.

## Sensor compatibility

The library works with any ultrasonic distance sensor that uses a pulse-width echo response.
This includes standard HC-SR04-style modules, low-power single-pin sensors, and many compatible variants.

For maximum compatibility:
- Use `setDistanceFactor()` to calibrate modules with custom timing or measurement scaling.
- Keep the sensor and controller ground lines common.
- Avoid pins reserved for internal ESP32 functions when using ESP32 boards.

## Wiring

### Trig + Echo modules

- `Trig` -> digital output pin
- `Echo` -> digital input pin
- `VCC` -> 5V (or 3.3V when supported by the module)
- `GND` -> common ground

### Single-pin modules

- `Signal` -> digital pin
- `VCC` -> 5V / 3.3V
- `GND` -> common ground

### ESP32 compatibility

- Use a safe GPIO pin for trigger and echo.
- If the sensor operates at 5V, protect the echo pin with a voltage divider or level shifter.

## Examples

### Arduino
- `examples/Arduino/Mm.ino` — read mm
- `examples/Arduino/Cm.ino` — read cm
- `examples/Arduino/Inch.ino` — read in
- `examples/Arduino/Foot.ino` — read ft
- `examples/Arduino/All.ino` — read mm, cm, in, ft

### ESP32
- `examples/ESP32/Mm.ino` — read mm
- `examples/ESP32/Cm.ino` — read cm
- `examples/ESP32/Inch.ino` — read in
- `examples/ESP32/Foot.ino` — read ft
- `examples/ESP32/All.ino` — read mm, cm, in, ft


### Single-pin
- `examples/SinglePin/Arduino.ino` — Arduino single-pin
- `examples/SinglePin/ESP32.ino` — ESP32 single-pin

## Basic usage

```cpp
#include <UltrasonicSensorLibrary.h>

Ultrasonic sensor(2, 3);

void setup()
{
    Serial.begin(9600);
    sensor.begin();
}

void loop()
{
    float distance = sensor.readCM();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
}
```

### Single-pin setup

```cpp
#include <UltrasonicSensorLibrary.h>

Ultrasonic sensor(2);

void setup()
{
    Serial.begin(9600);
    sensor.begin();
}

void loop()
{
    float distance = sensor.readCM();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
}
```

## API

- `begin()` initializes the sensor pins.
- `readCM()` returns the distance in centimeters.
- `readMM()` returns the distance in millimeters.
- `readInch()` returns the distance in inches.
- `setTimeout(timeoutMicroseconds)` updates the echo timeout.
- `setInterval(intervalMilliseconds)` updates the minimum measurement gap.
- `setDistanceFactor(distanceFactor)` calibrates the conversion factor for different sensors.
- `refresh()` forces a new reading and returns `true` when successful.

### Calibration example

```cpp
sensor.setDistanceFactor(56.0f);
```

Use this when a sensor produces a consistent offset or uses a variant timing formula.

## Implementation details

- The library uses a default timeout of `30,000` microseconds.
- The default measurement interval is `60` milliseconds.
- If a measurement fails, the library retains the last valid distance value.
- Distance is calculated from pulse width using a configurable distance factor, which keeps compatibility across different sensor versions.

## Changelog

### v1.1.0

- Added ESP32 compatibility notes and examples
- Added a single-pin ultrasonic example
- Updated package version to `1.1.0`

### v1.0.0

- Added support for trig/echo sensors and single-pin sensors
- Added automatic measurement timing
- Added unit conversion for cm, mm, and inches
- Added timeout and interval controls
- Added cached measurement handling and safe failure behavior
