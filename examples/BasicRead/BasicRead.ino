#include <UltrasonicSensorLibrary.h>

UltrasonicSensorLibrary sensor(2, 3);

void setup()
{
    Serial.begin(115200);
    sensor.begin();
}

void loop()
{
    float distanceCm = sensor.readCM();

    if (isnan(distanceCm))
    {
        Serial.println("Measurement failed");
    }
    else
    {
        Serial.print("Distance: ");
        Serial.print(distanceCm);
        Serial.println(" cm");
    }

    delay(250);
}
