#include "PushButton.hpp"

PushButton::PushButton()
:pressed_(false)
,time_pressed_(0)
,update_rate_ms_(10)
{}

PushButton::~PushButton()
{}



void PushButton::init(uint8_t pin, uint16_t update_rate_ms)
{
  pin_ = pin;
  update_rate_ms_=update_rate_ms;
  pinMode(pin_, INPUT);
}

void PushButton::update()
{
  bool pressed = digitalRead(pin_);
  if(pressed) 
  {
    pressed_ = false;
    time_pressed_ += update_rate_ms_;
  }
  else if(not pressed_ && time_pressed_!=0)
  {
    pressed=true;
    time_pressed_=0;
  }
  else
  {
    pressed_ = false;
    time_pressed_ = 0;
  }
}

bool PushButton::getPressed()
{
  return pressed_;
}

uint16_t PushButton::getTimePressed()
{
  return time_pressed_;
}
