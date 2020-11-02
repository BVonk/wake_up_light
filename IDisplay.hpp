#ifndef ___IDISPLAY_INCLUDE__
#define ___IDISPLAY_INCLUDE__

#include <stdint.h>

class IDisplay
{
public:
   //  virtual ~IDisplay;

    virtual void Init(uint16_t update_rate_ms) = 0;
    virtual void ShowTime(uint8_t hour, uint8_t minute) = 0;
    virtual void ShowDate(uint8_t day, uint8_t Month, uint16_t year) = 0;
    virtual void ShowAlarmOnOff(bool alarm_on) = 0;
    virtual void SetFlickerOn(bool flicker_on) = 0;

};

#endif
