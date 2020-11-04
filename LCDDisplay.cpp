#include "LCDDisplay.hpp"
//#include <LiquidCrystal_I2C.h>


LCDDisplay::LCDDisplay(LiquidCrystal_I2C& display)
:blink_time_(0)
,blink_on_(false)
,blink_mode_on_(false)
,display_(display)
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

void LCDDisplay::Clear()
{
  display_.clear();
}

void LCDDisplay::ShowTime(uint8_t hour, uint8_t minute)
{
    if(handleBlink())
    {
      display_.clear();
    }
    else
    {
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
void LCDDisplay::Blink()
{
    blink_mode_on_=true;
}

void LCDDisplay::NoBlink()
{
    blink_mode_on_=false;
}

bool LCDDisplay::handleBlink()
{
  if(not blink_mode_on_)
  {
    return false;
  }
  
  blink_time_+=update_rate_ms_;
  if(blink_time_>blink_switch_time_)
  {
    blink_time_=0;
    blink_on_ = blink_on_^0x1;
  }

  return blink_on_;
}
