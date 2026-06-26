# Ultrasonic Sensor Library

Ultrasonic Sensor Library is a lightweight Arduino library for HC-SR04 and compatible ultrasonic sensors. It provides a simple interface for measuring distance in centimeters, millimeters, or inches while handling timing and sensor triggering for you.

## Version 1.0.0

This release includes the core features needed for a practical Arduino library:

- Support for Trig/Echo sensors
- Support for single-pin ultrasonic sensors
- Automatic timing control with a default interval of 60 ms
- Cached readings to reduce unnecessary sensor triggers
- Easy unit conversion to cm, mm, and inch
- Safe handling of failed measurements

## Features

- Simple class-based API
- Automatic measurement timing
- Built-in timeout support
- Returns `NAN` when a measurement fails
- Keeps the last successful measurement available when a new attempt fails

## Installation

1. Download the repository as a ZIP file.
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library.
3. Select the downloaded ZIP file and restart the IDE if needed.

## Wiring

### Trig + Echo

- Connect the Trig pin to the Arduino digital output pin.
- Connect the Echo pin to the Arduino digital input pin.
- Power the sensor with 5V and GND.

### Single Pin

- Connect the single signal pin to the Arduino digital pin.
- Power the sensor with 5V and GND.

## Basic Usage

### Trig + Echo Sensor

```cpp
#include <UltrasonicSensorLibrary.h>

UltrasonicSensorLibrary sensor(2, 3);

void setup()
{
    Serial.begin(115200);
    sensor.begin();
}

void loop()
{
    float distance = sensor.readCM();
    Serial.println(distance);
}
```

### Single Pin Sensor

```cpp
#include <UltrasonicSensorLibrary.h>

UltrasonicSensorLibrary sensor(2);

void setup()
{
    Serial.begin(115200);
    sensor.begin();
}

void loop()
{
    float distance = sensor.readCM();
    Serial.println(distance);
}
```

## API

- `begin()` initializes the sensor pins.
- `readCM()` returns the distance in centimeters.
- `readMM()` returns the distance in millimeters.
- `readInch()` returns the distance in inches.
- `setTimeout(timeoutMicroseconds)` changes the echo timeout.
- `setInterval(intervalMilliseconds)` changes the minimum delay between measurements.
- `refresh()` forces a new measurement and returns `true` on success or `false` on failure.

## Notes

- The default timeout is 30,000 microseconds.
- The default measurement interval is 60 ms.
- Failed measurements do not overwrite the last valid reading.

## Changelog

### v1.0.0

- Added support for Trig/Echo and single-pin sensors
- Added automatic measurement timing
- Added cm, mm, and inch conversions
- Added timeout and interval configuration
- Added cached measurement handling and safe failure behavior
