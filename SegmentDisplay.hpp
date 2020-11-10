#ifndef ___SegmentDisplay_INCLUDE__
#define ___SegmentDisplay_INCLUDE__
#include "IDisplay.hpp"
#include <TM1637TinyDisplay.h>

class SegmentDisplay : public IDisplay
{
public:
    SegmentDisplay(TM1637TinyDisplay& display);
    ~SegmentDisplay();
    void Init(uint16_t update_rate_ms);
    void ShowTime(uint8_t hour, uint8_t minute);
    void ShowDate(uint8_t day, uint8_t month, uint16_t year);
    void ShowAlarmOnOff(bool alarm_on);
    void Clear();
    void Blink();
    void NoBlink();

private:
    bool handleBlink();
    
    const uint16_t blink_switch_time_ = 500;
    uint16_t blink_time_;
    bool blink_on_;
    bool blink_mode_on_;
    uint16_t update_rate_ms_;
    TM1637TinyDisplay& display_;
};


#endif
