#include "UltrasonicSensorLibrary.h"

namespace
{
    constexpr unsigned long kDefaultTimeoutMicros = 30000;
    constexpr unsigned long kDefaultIntervalMs = 60;
    constexpr float kDefaultDistanceFactor = 58.0f;
}

Ultrasonic::Ultrasonic(uint8_t trigPin, uint8_t echoPin)
{
    _trigPin = trigPin;
    _echoPin = echoPin;
    _singlePin = false;
    _timeout = kDefaultTimeoutMicros;
    _interval = kDefaultIntervalMs;
    _distanceFactor = kDefaultDistanceFactor;
    _lastMeasurementTime = 0;
    _lastDistance = NAN;
    _hasValidMeasurement = false;
}

Ultrasonic::Ultrasonic(uint8_t signalPin)
{
    _trigPin = signalPin;
    _echoPin = signalPin;
    _singlePin = true;
    _timeout = kDefaultTimeoutMicros;
    _interval = kDefaultIntervalMs;
    _distanceFactor = kDefaultDistanceFactor;
    _lastMeasurementTime = 0;
    _lastDistance = NAN;
    _hasValidMeasurement = false;
}

void Ultrasonic::begin()
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

void Ultrasonic::setTimeout(unsigned long timeoutMicroseconds)
{
    _timeout = timeoutMicroseconds;
}

void Ultrasonic::setInterval(unsigned long intervalMilliseconds)
{
    _interval = intervalMilliseconds;
}

void Ultrasonic::setDistanceFactor(float distanceFactor)
{
    if (distanceFactor > 0.0f)
    {
        _distanceFactor = distanceFactor;
    }
}

void Ultrasonic::triggerPulse()
{
    pinMode(_trigPin, OUTPUT);
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(_trigPin, LOW);
}

bool Ultrasonic::refresh()
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

    _lastDistance = duration / _distanceFactor;
    _hasValidMeasurement = true;
    return true;
}

float Ultrasonic::readCM()
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

float Ultrasonic::readMM()
{
    return readCM() * 10.0f;
}

float Ultrasonic::readInch()
{
    return readCM() / 2.54f;
}