#include <UltrasonicSensorLibrary.h>

/*
  BasicRead
  This example shows the simplest way to use the library with an HC-SR04 sensor.

  Wiring:
    - Trig pin -> Arduino digital pin 2
    - Echo pin -> Arduino digital pin 3
    - VCC -> 5V
    - GND -> GND
*/

// Pin configuration for the ultrasonic sensor.
const uint8_t kTrigPin = 2;
const uint8_t kEchoPin = 3;
const unsigned long kSerialBaudRate = 115200;

// Create a sensor object using the configured pins.
Ultrasonic sensor(kTrigPin, kEchoPin);

void setup()
{
    Serial.begin(kSerialBaudRate);
    sensor.begin();

    Serial.println("Ultrasonic sensor ready.");
}

void loop()
{
    // Read the latest distance in centimeters.
    // The library handles measurement timing internally.
    const float distanceCm = sensor.readCM();

    if (isnan(distanceCm))
    {
        Serial.println("Measurement failed. Please check wiring or sensor range.");
    }
    else
    {
        Serial.print("Distance: ");
        Serial.print(distanceCm);
        Serial.println(" cm");
    }
}
