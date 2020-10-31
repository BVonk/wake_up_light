#ifndef ___MENU_INCLUDE__
#define ___MENU_INCLUDE__

#include "Arduino.h"

enum MenuIndex{
  eCLOCK,
  eDATE,
  eALARMTIME,
  eALARMONOFF,
}

enum ButtonIndex{
  e0000,
  e0001,
  e0010,
  e0011,
  e0100,
  e0101,
  e0110,
  e0111,
  e1000,
  e1001,
  e1010,
  e1011,
  e1100,
  e1101,
  e1110,
  e1111,
}

class Menu
{
public:
  Menu(Button& button_menu, Button& button_light, Button&, button_up, Button& button_down)
  :button_menu_(button_menu)
  ,button_light_(button_light)
  ,button_up_(button_up)
  ,button_down_(button_down)
  ,index_(eCLOCK)
  ,change_index(0)
  ,brightness_(2)
  {};
  ~Menu();

  update()
  {
    switch case(index_)
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
  }

private:
  Button& button_menu_;
  Button& button_light_;
  Button& button_up_;
  Button& button_down_;

  void incrementBrightness()
  {
    if(brightness_ = 4) brightness_ = 0;
    else brightness++;
  }

  void incrementMenu()
  {
    if(index_ == eALARMONOFF) index_ = eCLOCK;
    else index_++;
  }

  void handleIndexClock()
  {
    if(change_index_=0)
    {
      if(button_menu.getPressed())
      {
        incrementMenu();
      }
      if(button_menu.getTimePressed() < 2000)
      {
        incrementChangeIndex()
      }
    }
  }
  
  void handleIndexDate();
  void handleIndexAlarmTime();
  void handleIndexAlarmOnOff();
  
  int index_;
  int change_time_index_;
  int change_date_index_;
  int brightness_;
}


#endif
