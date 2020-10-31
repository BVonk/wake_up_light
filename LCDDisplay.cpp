#include "LCDDisplay.hpp"
#include <LiquidCrystal_I2C.h>


LCDDisplay::LCDDisplay()
{
    display_ = LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
    update_rate_ms_ = 20;
}

LCDDisplay::~LCDDisplay()
{}

LCDDisplay::Init(update_rate_ms)
{
    update_rate_ms_ = update_rate_ms;
    display.begin(16,2);
    display.backlight();
    display.backlight();
    display.clear();
}

void LCDDisplay::ShowTime(uint8_t hour, uint8_t minute)
{
    display.clear();
    display.setCursor(0, 1);
    // display.print("Hour:");
    if (hour<=9)
    {
    display.print("0");
    }
    display.print(hour, DEC);

    display.print(":");
    if (minute<=9)
    {
    display.print("0");
    }
    display.print(minute, DEC);
}

void LCDDisplay::ShowDate(uint8_t day, uint8_t Month, uint16_t year)
{
    display.clear();
    display.setCursor(0, 1);
    display.print(day, DEC);
    display.print("/");
    display.print(month, DEC);
    display.print("/");
    display.print(year, DEC);
}

void LCDDisplay::ShowAlarmOnOff(bool alarm_on)
{
    display.clear();
    display.setCursor(0, 1);
    if(alarm_on)
    {
        display.print("Alarm on");
    }
    else
    {
        display.print("Alarm off");
    }
    
}
void LCDDisplay::SetFlickerOn(bool flicker_on)
{
    (void) flicker_on;
}
