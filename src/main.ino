#include <Wire.h>
#include "DisplayManager.h"
#include "SensorManager.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DisplayManager display;
SensorManager sensors(DHTPIN, DHTTYPE);

unsigned long previousClockMillis = 0;
unsigned long previousSensorMillis = 0;

const long CLOCK_INTERVAL = 1000;
const long SENSOR_INTERVAL = 3000;

void setup()
{
    Wire.begin(8, 9);
    Serial.begin(115200);

    display.init();

    if (!sensors.init())
    {
        Serial.print("SENSOR ERROR");
        display.sensorError("SENSOR ERROR!");
        while (1)
            ;
    }
}

void loop()
{
    unsigned long currentMillis = millis();

    // clock tick every 1s
    if (currentMillis - previousClockMillis >= CLOCK_INTERVAL)
    {
        previousClockMillis = currentMillis;

        char dateBuffer[16];
        char timeBuffer[16];

        sensors.getFormattedDateTime(dateBuffer, timeBuffer);
        display.updateClock(dateBuffer, timeBuffer);
    }

    // sensor reading every 3s (based on)
    if (currentMillis - previousSensorMillis >= SENSOR_INTERVAL)
    {
        previousSensorMillis = currentMillis;

        float temperature, humidity;
        bool status = sensors.readData(temperature, humidity);

        display.updateTemperature(temperature, !status);
        display.updateHumidity(humidity, !status);
    }
}
