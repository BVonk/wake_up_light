#ifndef ___MENU_INCLUDE__
#define ___MENU_INCLUDE__

#include "Arduino.h"
#include "RTClib.h"
#include "AlarmClock.h"
#include "PushButton.hpp"
#include "LCDDisplay.hpp"

class Menu
{
public:
  Menu(IDisplay& display, RTC_DS3231& RTC, AlarmClock& alarmClock, PushButton& button_menu, PushButton& button_light, PushButton& button_up, PushButton& button_down);
  ~Menu();

  void update();

private:
  PushButton& button_menu_;
  PushButton& button_light_;
  PushButton& button_up_;
  PushButton& button_down_;
  RTC_DS3231& RTC_;
  AlarmClock& alarmClock_;
  IDisplay& display_;

  void incrementBrightness();
  void incrementMenuIndex();
  void incrementChangeTimeIndex();
  void incrementChangeDateIndex();
  
  void incrementHour();
  void decrementHour();

  void incrementMinute();
  void decrementMinute();

  void incrementYear();
  void decrementYear();

  void incrementMonth();
  void decrementMonth();

  void incrementDay();
  void decrementDay();  
  uint8_t calculateMaxDay();

  void setTempDateTime();

  void handleIndexClock();
  void handleIndexDate();
  void handleIndexAlarmTime();
  void handleIndexAlarmOnOff();
  
  uint8_t index_;
  uint8_t change_time_index_;
  uint8_t change_date_index_;
  uint8_t brightness_;

  uint8_t temp_hour_;
  uint8_t temp_minute_;
  uint8_t temp_day_;
  uint8_t temp_month_;
  uint16_t temp_year_;

  enum MenuIndex{
    eCLOCK=0,
    eDATE,
    eALARMTIME,
    eALARMONOFF,
  };
  
  enum TimeIndex{
    eNOTIME=0,
    eHOUR,
    eMINUTE,
  };
  
  enum DateIndex{
    eNODATE=0,
    eYEAR,
    eMONTH,
    eDAY,
  };
};


#endif
