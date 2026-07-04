#include <UltrasonicSensorLibrary.h>

/*
  SinglePin Arduino
  Reads a single-pin ultrasonic sensor using Arduino.

  Wiring:
    - Signal pin -> digital pin 2
    - VCC -> 5V or 3.3V
    - GND -> GND
*/

const uint8_t kSignalPin = 2;
const unsigned long kSerialBaudRate = 9600;
Ultrasonic sensor(kSignalPin);

void setup()
{
    Serial.begin(kSerialBaudRate);
    sensor.begin();
    Serial.println("Single-pin Arduino");
}

void loop()
{
    float distance = sensor.readCM();

    if (isnan(distance))
    {
        Serial.println("Failed");
    }
    else
    {
        Serial.print(distance);
        Serial.println(" cm");
    }

    delay(150);
}
