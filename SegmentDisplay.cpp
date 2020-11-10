#include "SegmentDisplay.hpp"


SegmentDisplay::SegmentDisplay(TM1637TinyDisplay& display)
:blink_time_(0)
,blink_on_(false)
,blink_mode_on_(false)
,display_(display)
{
    update_rate_ms_ = 20;
}

SegmentDisplay::~SegmentDisplay()
{}

void SegmentDisplay::Init(uint16_t update_rate_ms)
{
    update_rate_ms_ = update_rate_ms;
    display_.setBrightness(0x0f);
    display_.clear();
}

void SegmentDisplay::Clear()
{
  display_.clear();
}

void SegmentDisplay::ShowTime(uint8_t hour, uint8_t minute)
{
    if(handleBlink())
    {
      display_.clear();
    }
    else
    {
      display_.showNumberDec(hour, 0b01000000, true, 2, 0);
      display_.showNumberDec(minute, 0b01000000, true, 2, 2);
    }
}

void SegmentDisplay::ShowDate(uint8_t day, uint8_t month, uint16_t year)
{
  display_.showNumberDec(day, 0b01000000, true, 2, 0);
  display_.showNumberDec(month, 0b01000000, true, 2, 2);
}

void SegmentDisplay::ShowAlarmOnOff(bool alarm_on)
{
    display_.clear();
    if(alarm_on)
    {
        display_.showString("ON");
    }
    else
    {
        display_.showString("OFF");
    }
    
}
void SegmentDisplay::Blink()
{
    blink_mode_on_=true;
}

void SegmentDisplay::NoBlink()
{
    blink_mode_on_=false;
}

bool SegmentDisplay::handleBlink()
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
