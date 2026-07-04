#include <UltrasonicSensorLibrary.h>

const uint8_t kTrigPin = 26;
const uint8_t kEchoPin = 27;
const unsigned long kSerialBaudRate = 9600;
Ultrasonic sensor(kTrigPin, kEchoPin);

void setup()
{
    Serial.begin(kSerialBaudRate);
    sensor.begin();
    Serial.println("ESP32 cm");
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
