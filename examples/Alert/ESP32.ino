#include <UltrasonicSensorLibrary.h>

const uint8_t kTrigPin = 26;
const uint8_t kEchoPin = 27;
const uint8_t kLedPin = 2;
const unsigned long kSerialBaudRate = 9600;
const float kAlertCm = 15.0f;
Ultrasonic sensor(kTrigPin, kEchoPin);

void setup()
{
    pinMode(kLedPin, OUTPUT);
    digitalWrite(kLedPin, LOW);
    Serial.begin(kSerialBaudRate);
    sensor.begin();
    Serial.println("ESP32 alert");
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
