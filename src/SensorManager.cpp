#include "SensorManager.h"

SensorManager::SensorManager(uint8_t dhtPin, uint8_t dhtType) : _dht(dhtPin, dhtType) {}

bool SensorManager::init()
{
    _dht.begin();

    if (!_rtc.begin())
        return false;

    if (!_rtc.isrunning())
    {
        _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    return true;
}

void SensorManager::getFormattedDateTime(char *dateBuf, char *timeBuf)
{
    DateTime now = _rtc.now();
    sprintf(dateBuf, "%02d/%02d/%04d", now.day(), now.month(), now.year());     // format : dd/MM/yyyy
    sprintf(timeBuf, "%02d.%02d.%02d", now.hour(), now.minute(), now.second()); // format : HH:mm:ss
}

bool SensorManager::readData(float &temperature, float &humidity)
{
    temperature = _dht.readTemperature();
    humidity = _dht.readHumidity();

    return !(isnan(temperature) || isnan(humidity));
}