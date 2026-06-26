#include "UltrasonicSensorLibrary.h"

namespace
{
    constexpr unsigned long kDefaultTimeoutMicros = 30000;
    constexpr unsigned long kDefaultIntervalMs = 60;
}

UltrasonicSensorLibrary::UltrasonicSensorLibrary(uint8_t trigPin, uint8_t echoPin)
{
    _trigPin = trigPin;
    _echoPin = echoPin;
    _singlePin = false;
    _timeout = kDefaultTimeoutMicros;
    _interval = kDefaultIntervalMs;
    _lastMeasurementTime = 0;
    _lastDistance = NAN;
    _hasValidMeasurement = false;
}

UltrasonicSensorLibrary::UltrasonicSensorLibrary(uint8_t signalPin)
{
    _trigPin = signalPin;
    _echoPin = signalPin;
    _singlePin = true;
    _timeout = kDefaultTimeoutMicros;
    _interval = kDefaultIntervalMs;
    _lastMeasurementTime = 0;
    _lastDistance = NAN;
    _hasValidMeasurement = false;
}

void UltrasonicSensorLibrary::begin()
{
    pinMode(_trigPin, OUTPUT);
    digitalWrite(_trigPin, LOW);

    if (!_singlePin)
    {
        pinMode(_echoPin, INPUT);
    }

    _lastMeasurementTime = 0;
    _lastDistance = NAN;
    _hasValidMeasurement = false;
}

void UltrasonicSensorLibrary::setTimeout(unsigned long timeoutMicroseconds)
{
    _timeout = timeoutMicroseconds;
}

void UltrasonicSensorLibrary::setInterval(unsigned long intervalMilliseconds)
{
    _interval = intervalMilliseconds;
}

void UltrasonicSensorLibrary::triggerPulse()
{
    pinMode(_trigPin, OUTPUT);
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(_trigPin, LOW);
}

bool UltrasonicSensorLibrary::refresh()
{
    if (_lastMeasurementTime != 0)
    {
        unsigned long elapsed = millis() - _lastMeasurementTime;

        if (elapsed < _interval)
        {
            delay(_interval - elapsed);
        }
    }

    unsigned long duration = 0;

    if (_singlePin)
    {
        triggerPulse();
        pinMode(_trigPin, INPUT);
        duration = pulseIn(_trigPin, HIGH, _timeout);
    }
    else
    {
        triggerPulse();
        duration = pulseIn(_echoPin, HIGH, _timeout);
    }

    _lastMeasurementTime = millis();

    if (duration == 0)
    {
        return false;
    }

    _lastDistance = duration / 58.0f;
    _hasValidMeasurement = true;
    return true;
}

float UltrasonicSensorLibrary::readCM()
{
    if (_hasValidMeasurement)
    {
        unsigned long elapsed = millis() - _lastMeasurementTime;

        if (elapsed < _interval)
        {
            return _lastDistance;
        }
    }

    refresh();
    return _lastDistance;
}

float UltrasonicSensorLibrary::readMM()
{
    return readCM() * 10.0f;
}

float UltrasonicSensorLibrary::readInch()
{
    return readCM() / 2.54f;
}