#include <UltrasonicSensorLibrary.h>

const uint8_t kTrigPin = 2;
const uint8_t kEchoPin = 3;
const unsigned long kSerialBaudRate = 9600;
Ultrasonic sensor(kTrigPin, kEchoPin);

void setup()
{
    Serial.begin(kSerialBaudRate);
    sensor.begin();
    Serial.println("Arduino all units");
}

void loop()
{
    float mm = sensor.readMM();
    float cm = sensor.readCM();
    float inch = sensor.readInch();
    float foot = inch / 12.0f;

    if (isnan(cm))
    {
        Serial.println("Failed");
    }
    else
    {
        Serial.print(mm);
        Serial.print(" mm | ");
        Serial.print(cm);
        Serial.print(" cm | ");
        Serial.print(inch);
        Serial.print(" in | ");
        Serial.print(foot);
        Serial.println(" ft");
    }

    delay(200);
}
