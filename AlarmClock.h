#ifndef ___ALARM_CLOCK_INCLUDE__
#define ___ALARM_CLOCK_INCLUDE__

#include <RTClib.h>
#include <stdint.h>

class AlarmClock
{
public:
  AlarmClock();
  ~AlarmClock();

  void update(DateTime now);
  void setAlarmTime(uint8_t hour, uint8_t minute);
  void enableAlarm();
  void disableAlarm();
  void setAlarmLength(uint16_t length);
  
  bool getAlarmActive();
  bool getAlarmSet();
  uint8_t getAlarmHours();
  uint8_t getAlarmMinutes();
  float getAlarmProgress();

  
private:
  bool alarm_active_;
  bool alarm_set_;
  uint8_t alarm_hour_;
  uint8_t alarm_minute_;
  float alarm_progress_;
  uint16_t alarm_length_seconds_;
  uint32_t alarm_time_triggered_;
};


#endif // ___ALARM_CLOCK_INCLUDE__
