#include "DisplayManager.h"
#include "TextHelper.h"

DisplayManager::DisplayManager() : _clockLCD(0x25, 16, 2), _tempLCD(0x27, 16, 2), _humidLCD(0x26, 16, 2) {}

void DisplayManager::init()
{
    _clockLCD.init();
    _clockLCD.backlight();
    _tempLCD.init();
    _tempLCD.backlight();
    _humidLCD.init();
    _humidLCD.backlight();
}

void DisplayManager::sensorError(const char *text)
{
    char cleanDisplay[17];

    formatLine16(cleanDisplay, sizeof(cleanDisplay), text);

    _tempLCD.setCursor(0, 0);
    _tempLCD.print(cleanDisplay);
    _humidLCD.setCursor(0, 0);
    _humidLCD.print(cleanDisplay);
}

void DisplayManager::updateClock(const char *date, const char *time)
{
    char cleanDate[17];
    char cleanTime[17];

    formatLine16(cleanDate, sizeof(cleanDate), date);
    formatLine16(cleanTime, sizeof(cleanTime), time);

    _clockLCD.setCursor(0, 0);
    _clockLCD.print(cleanDate);
    _clockLCD.setCursor(0, 1);
    _clockLCD.print(cleanTime);
}

void DisplayManager::updateTemperature(float temperature, bool isError)
{
    char line1[17];
    char line2[17];

    _tempLCD.setCursor(0, 0);

    if (isError)
    {
        formatLine16(line1, sizeof(line1), "Sensor ERROR!");
        _tempLCD.print(line1);
    }
    else
    {
        formatLine16(line1, sizeof(line1), "Temperature:");
        _tempLCD.print(line1);

        _tempLCD.setCursor(0, 1);
        formatFloatLine16(line2, sizeof(line2), temperature, "C");
        _tempLCD.print(line2);
    }
}

void DisplayManager::updateHumidity(float humidity, bool isError)
{
    char line1[17];
    char line2[17];

    _humidLCD.setCursor(0, 0);

    if (isError)
    {
        formatLine16(line1, sizeof(line1), "Sensor ERROR!");
        _humidLCD.print(line1);
    }
    else
    {
        formatLine16(line1, sizeof(line1), "Humidity:");
        _humidLCD.print(line1);

        _humidLCD.setCursor(0, 1);
        formatFloatLine16(line2, sizeof(line2), humidity, "%");
        _humidLCD.print(line2);
    }
}