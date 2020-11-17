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
    void Backlight();
    void NoBacklight();
    void ToggleBacklight();
    void Clear();
    void Blink();
    void NoBlink();

private:
    bool handleBlink();
    bool backlight_;
    const uint16_t blink_switch_time_ = 500;
    uint16_t blink_time_;
    bool blink_on_;
    bool blink_mode_on_;
    uint16_t update_rate_ms_;
    LiquidCrystal_I2C& display_;
};


#endif
