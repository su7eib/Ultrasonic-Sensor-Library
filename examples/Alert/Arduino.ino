#include <UltrasonicSensorLibrary.h>

const uint8_t kTrigPin = 2;
const uint8_t kEchoPin = 3;
const uint8_t kLedPin = 13;
const unsigned long kSerialBaudRate = 9600;
const float kAlertCm = 15.0f;
Ultrasonic sensor(kTrigPin, kEchoPin);

void setup()
{
    pinMode(kLedPin, OUTPUT);
    digitalWrite(kLedPin, LOW);
    Serial.begin(kSerialBaudRate);
    sensor.begin();
    Serial.println("Arduino alert");
}

void loop()
{
    float distance = sensor.readCM();
    if (isnan(distance))
    {
        Serial.println("Failed");
        digitalWrite(kLedPin, LOW);
    }
    else
    {
        Serial.print(distance);
        Serial.println(" cm");
        if (distance < kAlertCm)
        {
            digitalWrite(kLedPin, HIGH);
        }
        else
        {
            digitalWrite(kLedPin, LOW);
        }
    }
    delay(150);
}
