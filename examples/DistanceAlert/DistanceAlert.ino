#include <UltrasonicSensorLibrary.h>

/*
  DistanceAlert
  A simple project that uses the ultrasonic sensor to warn when an object is too close.

  Wiring:
    - Trig pin -> Arduino digital pin 2
    - Echo pin -> Arduino digital pin 3
    - LED pin -> Arduino digital pin 13
    - VCC -> 5V
    - GND -> GND
*/

// Pin configuration and thresholds.
const uint8_t kTrigPin = 2;
const uint8_t kEchoPin = 3;
const uint8_t kLedPin = 13;
const unsigned long kSerialBaudRate = 115200;
const float kAlertThresholdCm = 15.0f;

Ultrasonic sensor(kTrigPin, kEchoPin);

void setup()
{
    pinMode(kLedPin, OUTPUT);
    digitalWrite(kLedPin, LOW);

    Serial.begin(kSerialBaudRate);
    sensor.begin();

    Serial.println("DistanceAlert example started.");
}

void loop()
{
    // Read distance and check whether the measurement is valid.
    const float distanceCm = sensor.readCM();

    if (isnan(distanceCm))
    {
        Serial.println("Measurement failed.");
        digitalWrite(kLedPin, LOW);
    }
    else
    {
        Serial.print("Distance: ");
        Serial.print(distanceCm);
        Serial.println(" cm");

        // Turn on the LED when an object is closer than the defined threshold.
        if (distanceCm < kAlertThresholdCm)
        {
            digitalWrite(kLedPin, HIGH);
        }
        else
        {
            digitalWrite(kLedPin, LOW);
        }
    }
}
