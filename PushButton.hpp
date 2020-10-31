#ifndef ___PUSH_BUTTON_INCLUDE__
#define ___PUSH_BUTTON_INCLUDE__

#include <Arduino.h>

class PushButton
{
public:
  PushButton();
  ~PushButton();

  void init(uint8_t pin, uint16_t update_rate_ms);  
  void update();
  bool getPressed();
  uint16_t getTimePressed();

  
private:
  uint8_t pin_;
  bool pressed_;
  uint16_t time_pressed_;
  uint16_t update_rate_ms_;
};

#endif
