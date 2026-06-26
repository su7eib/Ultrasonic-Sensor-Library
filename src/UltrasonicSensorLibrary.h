#ifndef ULTRASONIC_SENSOR_LIBRARY_H
#define ULTRASONIC_SENSOR_LIBRARY_H

#include <Arduino.h>

class Ultrasonic
{
public:
    Ultrasonic(uint8_t trigPin, uint8_t echoPin);
    Ultrasonic(uint8_t signalPin);

    void begin();
    float readCM();
    float readMM();
    float readInch();
    void setTimeout(unsigned long timeoutMicroseconds);
    void setInterval(unsigned long intervalMilliseconds);
    bool refresh();

private:
    uint8_t _trigPin;
    uint8_t _echoPin;
    bool _singlePin;
    unsigned long _timeout;
    unsigned long _interval;
    unsigned long _lastMeasurementTime;
    float _lastDistance;
    bool _hasValidMeasurement;

    void triggerPulse();
};

using UltrasonicSensorLibrary = Ultrasonic;

#endif