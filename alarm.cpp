#include "alarm.h"

AlarmClock::AlarmClock()
:alarm_active_(false)
,alarm_set_(false)
,alarm_hour_(0)
,alarm_minute_(0)
,alarm_time_triggered_(0)
,alarm_progress_(0)
,alarm_length_seconds_(1800)
{
}

AlarmClock::~AlarmClock()
{}

void AlarmClock::update(DateTime now)
{
  if ( alarm_set_ && now.hour() == alarm_hour_ && now.minute() == alarm_minute_ )
  {
    alarm_active_ = true;
    alarm_set_ = false;
    alarm_time_triggered_ = now.secondstime();
  }

  if(alarm_active_)
  {
    alarm_progress_ = (float)(now.secondstime() - alarm_time_triggered_) / (float) alarm_length_seconds_;
  }
  else
  {
    alarm_progress_=0;
  }
  if(alarm_active_ && alarm_progress_ >= 1)
  {
    disableAlarm();
  }
}

void AlarmClock::setAlarmTime(uint8_t hour, uint8_t minute)
{
  if(hour < 24 && minute < 60)
  {
    alarm_hour_ = hour;
    alarm_minute_ = minute;
  }
}

void AlarmClock::setAlarmLength(uint16_t length)
{
  if(length <= 3600)
  alarm_length_seconds_ = length;
}

bool AlarmClock::getAlarmActive()
{
  return alarm_active_;
}

bool AlarmClock::getAlarmSet()
{
  return alarm_set_;
}

uint8_t AlarmClock::getAlarmHours()
{
  return alarm_hour_;
}

uint8_t AlarmClock::getAlarmMinutes()
{
  return alarm_minute_;
}

float AlarmClock::getAlarmProgress()
{
  return alarm_progress_;
}

void AlarmClock::enableAlarm()
{
  alarm_set_ = true;
}

void AlarmClock::disableAlarm()
{
  alarm_active_ = false;
  alarm_set_ = false;
  alarm_progress_ = 0;
}

