#include "LCDDisplay.hpp"
//#include <LiquidCrystal_I2C.h>


LCDDisplay::LCDDisplay(LiquidCrystal_I2C& display)
:display_(display)
{
    update_rate_ms_ = 20;
}

LCDDisplay::~LCDDisplay()
{}

void LCDDisplay::Init(uint16_t update_rate_ms)
{
    update_rate_ms_ = update_rate_ms;
    display_.init();
    display_.backlight();
    display_.clear();
}

void LCDDisplay::ShowTime(uint8_t hour, uint8_t minute)
{
//    display_.clear();
    display_.setCursor(0, 1);
    // display_.print("Hour:");
    if (hour<=9)
    {
    display_.print("0");
    }
    display_.print(hour, DEC);

    display_.print(":");
    if (minute<=9)
    {
    display_.print("0");
    }
    display_.print(minute, DEC);
}

void LCDDisplay::ShowDate(uint8_t day, uint8_t month, uint16_t year)
{
    display_.clear();
    display_.setCursor(0, 1);
    display_.print(day, DEC);
    display_.print("/");
    display_.print(month, DEC);
    display_.print("/");
    display_.print(year, DEC);
}

void LCDDisplay::ShowAlarmOnOff(bool alarm_on)
{
    display_.clear();
    display_.setCursor(0, 1);
    if(alarm_on)
    {
        display_.print("Alarm on");
    }
    else
    {
        display_.print("Alarm off");
    }
    
}
void LCDDisplay::SetFlickerOn(bool flicker_on)
{
    (void) flicker_on;
}
