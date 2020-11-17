#include "PushButton.hpp"

PushButton::PushButton()
:pressed_(false)
,long_pressed_(false)
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
    long_pressed_= false;
    if(time_pressed_ <= 1000)
    {
      time_pressed_ += update_rate_ms_;
    }
  }
  else if(not pressed && time_pressed_ > 1000)
  {
    long_pressed_=true;
    pressed_=false;
    time_pressed_=0;
  }
  else if(not pressed && time_pressed_ !=0)
  {
    pressed_ = true;
    long_pressed_ = false;
    time_pressed_ = 0;
  }
  else
  {
    pressed_ = false;
    long_pressed_ = false;
    time_pressed_ = 0;
  }
//  Serial.print("pressed \n");
//  Serial.print(pressed, DEC);
//  Serial.print(" short ");
//  Serial.print(pressed_, DEC);
//  Serial.print(" long ");
//  Serial.print(long_pressed_, DEC);
//  Serial.print(time_pressed_, DEC);
}

bool PushButton::getPressed()
{
  return pressed_;
}

uint16_t PushButton::getLongPressed()
{
  return long_pressed_;
}
