#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <DHT.h>
#include <RTClib.h>

class SensorManager
{
private:
    DHT _dht;
    RTC_DS1307 _rtc;

public:
    SensorManager(uint8_t dhtPin, uint8_t dhtType);
    bool init();
    void getFormattedDateTime(char *dateBuf, char *timeBuf);
    bool readData(float &temperature, float &humidity);
};

#endif