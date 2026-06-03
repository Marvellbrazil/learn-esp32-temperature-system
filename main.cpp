#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <RTClib.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 rtc;

LiquidCrystal_I2C ClockLCD(0x25, 16, 2);
LiquidCrystal_I2C TempLCD(0x27, 16, 2);
LiquidCrystal_I2C HumidLCD(0x26, 16, 2);

unsigned long previousClockMillis = 0;
unsigned long previousSensorMillis = 0;
const long clockInterval = 1000;  
const long sensorInterval = 3000; 

void setup() {
    Wire.begin(8, 9);
    Serial.begin(115200);

    ClockLCD.init();
    TempLCD.init();
    HumidLCD.init();
    ClockLCD.backlight();
    TempLCD.backlight();
    HumidLCD.backlight();

    if (!rtc.begin()) {
        Serial.println("RTC DS1307 NOT DETECTED!");
        ClockLCD.print("RTC Error!      ");
        while (1); 
    }

    if (!rtc.isrunning()) {
        Serial.println("RTC ADJUSTING...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    dht.begin();
    ClockLCD.clear();
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousClockMillis >= clockInterval) {
        previousClockMillis = currentMillis;

        DateTime now = rtc.now();

        char dateBuffer[16];
        char timeBuffer[16];

        sprintf(dateBuffer, "%02d/%02d/%04d", now.day(), now.month(), now.year());
        sprintf(timeBuffer, "%02d.%02d.%02d", now.hour(), now.minute(), now.second());

        ClockLCD.setCursor(0, 0);
        ClockLCD.print(dateBuffer);
        
        ClockLCD.setCursor(0, 1);
        ClockLCD.print(timeBuffer);
    }

    if (currentMillis - previousSensorMillis >= sensorInterval) {
        previousSensorMillis = currentMillis;

        float temp = dht.readTemperature();
        float humid = dht.readHumidity();

        if (isnan(temp) || isnan(humid)) {
            TempLCD.setCursor(0, 0);  TempLCD.print("Sensor ERROR!   ");
            HumidLCD.setCursor(0, 0); HumidLCD.print("Sensor ERROR!   ");
        } else {
            TempLCD.setCursor(0, 0);  TempLCD.print("Temperature:    ");
            TempLCD.setCursor(0, 1);  TempLCD.print(temp, 1); TempLCD.print(" C              ");

            HumidLCD.setCursor(0, 0); HumidLCD.print("Humidity:       ");
            HumidLCD.setCursor(0, 1); HumidLCD.print(humid, 1); HumidLCD.print(" %              ");
        }
    }
}
