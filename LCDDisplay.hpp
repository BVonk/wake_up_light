#ifndef ___LCDDISPLAY_INCLUDE__
#define ___LCDDISPLAY_INCLUDE__
#include "IDisplay.hpp"
#include <LiquidCrystal_I2C.h>

class LCDDisplay : public IDisplay
{
public:
    LCDDisplay(LiquidCrystal_I2C& display);
    ~LCDDisplay();
    void Init(uint16_t update_rate_ms);
    void ShowTime(uint8_t hour, uint8_t minute);
    void ShowDate(uint8_t day, uint8_t month, uint16_t year);
    void ShowAlarmOnOff(bool alarm_on);
    void SetFlickerOn(bool flicker_on);

private:
    uint16_t update_rate_ms_;
    LiquidCrystal_I2C& display_;
};


#endif
