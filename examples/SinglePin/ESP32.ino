#include <UltrasonicSensorLibrary.h>

/*
  SinglePin ESP32
  Reads a single-pin ultrasonic sensor using ESP32.

  Wiring:
    - Signal pin -> GPIO 26
    - VCC -> 3.3V or 5V with a level shifter on the signal pin
    - GND -> GND
*/

const uint8_t kSignalPin = 26;
const unsigned long kSerialBaudRate = 9600;
Ultrasonic sensor(kSignalPin);

void setup()
{
    Serial.begin(kSerialBaudRate);
    sensor.begin();
    Serial.println("Single-pin ESP32");
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
