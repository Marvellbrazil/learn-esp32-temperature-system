#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>

class DisplayManager
{
private:
    LiquidCrystal_I2C _clockLCD;
    LiquidCrystal_I2C _tempLCD;
    LiquidCrystal_I2C _humidLCD;

public:
    DisplayManager();
    void init();
    void sensorError(const char *text);
    void updateClock(const char *date, const char *time);
    void updateTemperature(float temp, bool isError);
    void updateHumidity(float humid, bool isError);
};

#endif
