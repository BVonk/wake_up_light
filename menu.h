#ifndef ___MENU_INCLUDE__
#define ___MENU_INCLUDE__

#include "Arduino.h"
#include "RTClib.h"
#include "alarm.h"
#include "PushButton.hpp"

class Menu
{
public:
  Menu(RTC_DS3231& RTC, AlarmClock& alarmClock, PushButton& button_menu, PushButton& button_light, PushButton& button_up, PushButton& button_down);
  ~Menu();

  void update();

private:
  PushButton& button_menu_;
  PushButton& button_light_;
  PushButton& button_up_;
  PushButton& button_down_;
  RTC_DS3231& RTC_;
  AlarmClock& alarmClock_;

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
    eCLOCK,
    eDATE,
    eALARMTIME,
    eALARMONOFF,
  };
  
  enum TimeIndex{
    eNOTIME,
    eHOUR,
    eMINUTE,
  };
  
  enum DateIndex{
    eNODATE,
    eYEAR,
    eMONTH,
    eDAY,
  };
};


#endif
