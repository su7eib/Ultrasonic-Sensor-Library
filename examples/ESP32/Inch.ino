#include <UltrasonicSensorLibrary.h>

const uint8_t kTrigPin = 26;
const uint8_t kEchoPin = 27;
const unsigned long kSerialBaudRate = 9600;
Ultrasonic sensor(kTrigPin, kEchoPin);

void setup()
{
    Serial.begin(kSerialBaudRate);
    sensor.begin();
    Serial.println("ESP32 inch");
}

void loop()
{
    float distance = sensor.readInch();
    if (isnan(distance))
    {
        Serial.println("Failed");
    }
    else
    {
        Serial.print(distance);
        Serial.println(" in");
    }
    delay(150);
}
