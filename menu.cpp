#include "menu.h"

Menu::Menu(IDisplay& display, RTC_DS3231& RTC, AlarmClock& alarmClock, PushButton& button_menu, PushButton& button_light, PushButton& button_up, PushButton& button_down)
:button_menu_(button_menu)
,button_light_(button_light)
,button_up_(button_up)
,button_down_(button_down)
,RTC_(RTC)
,alarmClock_(alarmClock)
,display_(display)
,index_(0)
,change_time_index_(0)
,change_date_index_(0)
,brightness_(0)
,temp_hour_(0)
,temp_minute_(0)
,temp_day_(0)
,temp_month_(0)
,temp_year_(0)
{}

Menu::~Menu()
{}

void Menu::update()
{
  uint8_t temp_index_=index_;
//  Serial.print("Index ");
//  Serial.print(index_, DEC);
//  Serial.print(" ");
//  Serial.print(change_time_index_, DEC);
//  Serial.print("\n");
 
  DateTime now = RTC_.now();
  switch (index_)
  {
    case eCLOCK:
      handleIndexClock();
      break;
    case eDATE:
      handleIndexDate();
      break;
    case eALARMTIME:
      handleIndexAlarmTime();
      break;
    case eALARMONOFF:
      handleIndexAlarmOnOff();
      break;
  }

  if(temp_index_!=index_)
  {
    display_.Clear();
  }
  
  switch (index_)
  {
    case eCLOCK:
      if(not change_time_index_) 
      {
        display_.NoBlink();
        display_.ShowTime(now.hour(), now.minute());
      }
      else 
      {
        display_.Blink();
        display_.ShowTime(temp_hour_, temp_minute_);
      }
      break;
    case eDATE:
      if(not change_date_index_) 
      {
        display_.NoBlink();
        display_.ShowDate(now.day(), now.month(), now.year());
      }
      else 
      {
        display_.Blink();
        display_.ShowDate(temp_day_, temp_month_, temp_year_);
      }
      break;
    case eALARMTIME:
      if(not change_time_index_) 
      {
        display_.NoBlink();
        display_.ShowTime(alarmClock_.getAlarmHours(), alarmClock_.getAlarmMinutes());
      }
      else 
      {
        display_.Blink();
        display_.ShowTime(temp_hour_, temp_minute_);
      }
      break;
    case eALARMONOFF:
      display_.ShowAlarmOnOff(alarmClock_.getAlarmSet());
      break;
  }

}


void Menu::incrementBrightness()
{
  if(brightness_ = 4) brightness_ = 0;
  else brightness_++;
}

void Menu::incrementMenuIndex()
{
  if(index_ == eALARMONOFF) index_ = eCLOCK;
  else index_++;
}

void Menu::incrementChangeTimeIndex()
{
  if(change_time_index_ == eMINUTE)
  {
    change_time_index_=eNOTIME;
  }
  else change_time_index_++;
}

void Menu::incrementChangeDateIndex()
{
    if(change_date_index_ == eYEAR)
    {
      change_date_index_=eNODATE;
    }
    else change_date_index_++;
}

void Menu::incrementHour()
{
  if(temp_hour_ == 23) temp_hour_ = 0;
  else temp_hour_++;
}
void Menu::decrementHour()
{
  if(temp_hour_ == 0) temp_hour_=23;
  else temp_hour_--;
}

void Menu::incrementMinute()
{
  if(temp_minute_ == 59) temp_minute_=0;
  else temp_minute_++;
}
void Menu::decrementMinute()
{
  if(temp_minute_ == 0) temp_minute_=59;
  else temp_minute_--;
}

void Menu::incrementYear()
{
  temp_year_++;
}
void Menu::decrementYear()
{
  if(temp_year_>2001) temp_year_--;
}

void Menu::incrementMonth()
{
  if(temp_month_==12) temp_month_=1;
  else temp_month_++;
}
void Menu::decrementMonth()
{
  if(temp_month_==1) temp_month_=12;
  else temp_month_--;
}

void Menu::incrementDay()
{
  uint8_t max_day = calculateMaxDay();
  if(temp_day_>=max_day) temp_day_=1;
  else temp_day_++;
}
void Menu::decrementDay()
{
  uint8_t max_day = calculateMaxDay();
  if(temp_day_ == 1) temp_day_ = max_day;
  else temp_day_--; 
}
uint8_t Menu::calculateMaxDay()
{
  return 31;
}

void Menu::setTempDateTime()
{
  DateTime now = RTC_.now();
  temp_hour_ = now.hour();
  temp_minute_ = now.minute();
  temp_year_ = now.year();
  temp_month_ = now.month();
  temp_day_ = now.day();
}

void Menu::handleIndexClock()
{
  if(change_time_index_==TimeIndex::eNOTIME)
  {
//    Serial.print(button_menu_.getPressed(), DEC);
//    Serial.print("\n");
    if(button_menu_.getPressed()) incrementMenuIndex();
    else if(button_menu_.getLongPressed())
    {
      incrementChangeTimeIndex();
      setTempDateTime();
    }
  }
  else if(change_time_index_==eHOUR)
  {
    if(button_menu_.getPressed()) incrementChangeTimeIndex();
    else if(button_up_.getPressed()) incrementHour();
    else if(button_down_.getPressed()) decrementHour();
  }
  else if(change_time_index_==eMINUTE)
  {
    if(button_menu_.getPressed()) 
    {
      incrementChangeTimeIndex();
      DateTime now = RTC_.now();
      DateTime new_time = DateTime(now.year(), now.month(), now.day(), temp_hour_, temp_minute_, 0);
      RTC_.adjust(new_time);
    }
    else if(button_up_.getPressed()) incrementMinute();
    else if(button_down_.getPressed()) decrementMinute();
  }
}

void Menu::handleIndexDate()
{
  if(change_date_index_==eNODATE)
  {
    if(button_menu_.getPressed()) incrementMenuIndex();
    else if(button_menu_.getLongPressed())
    {
      incrementChangeTimeIndex();
      setTempDateTime();
    }
  }
  else if(change_date_index_==eYEAR)
  {
    if(button_menu_.getPressed()) incrementChangeDateIndex();
    else if(button_up_.getPressed()) incrementYear();
    else if(button_down_.getPressed()) decrementYear();
  }
  else if(change_date_index_==eMONTH)
  {
    if(button_menu_.getPressed()) incrementChangeDateIndex();
    else if(button_up_.getPressed()) incrementMonth();
    else if(button_down_.getPressed()) decrementMonth();
  }
  else if(change_date_index_==eDAY)   
  {
    if(button_menu_.getPressed()) 
    {
      incrementChangeDateIndex();
      DateTime now = RTC_.now();
      DateTime new_time = DateTime(temp_year_, temp_month_, temp_day_, now.hour(), now.minute(), now.second());
      RTC_.adjust(new_time);
    }
    else if(button_up_.getPressed()) incrementDay();
    else if(button_down_.getPressed()) decrementDay();
  }
}

void Menu::handleIndexAlarmTime()
{
  if(change_time_index_==TimeIndex::eNOTIME)
  {
    if(button_menu_.getPressed()) incrementMenuIndex();
    else if(button_menu_.getLongPressed())
    {
      incrementChangeTimeIndex();
      temp_hour_ = alarmClock_.getAlarmHours();
      temp_minute_ = alarmClock_.getAlarmMinutes();
      
    }
  }
  else if(change_time_index_==eHOUR)
  {
    if(button_menu_.getPressed()) incrementChangeTimeIndex();
    else if(button_up_.getPressed()) incrementHour();
    else if(button_down_.getPressed()) decrementHour();
  }
  else if(change_time_index_==eMINUTE)
  {
    if(button_menu_.getPressed()) 
    {
      incrementChangeTimeIndex();
      alarmClock_.setAlarmTime(temp_hour_, temp_minute_);
    }
    else if(button_up_.getPressed()) incrementMinute();
    else if(button_down_.getPressed()) decrementMinute();
  }
}

void Menu::handleIndexAlarmOnOff()
{
  if(button_menu_.getPressed()) incrementMenuIndex();
  else if(button_up_.getPressed() or button_down_.getPressed())
  {
    if(alarmClock_.getAlarmSet()) alarmClock_.disableAlarm();
    else(alarmClock_.enableAlarm());
  }
}
