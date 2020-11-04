

/*
 Name:		wake_up_light.ino
 Created:	12/10/2017 12:12:34 AM
 Author:	bartl
*/

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include "LCDDisplay.hpp"
#include <LiquidCrystal_I2C.h>
#include "AlarmClock.h"
#include "menu.h"
#include "PushButton.hpp"


//LiquidCrystal lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS3231 RTC;
//RTC_DS1307 RTC;
AlarmClock alarmClock;
PushButton button1;
PushButton button2;
PushButton button3;
PushButton button4;
LCDDisplay display(lcd);
Menu menu(display, RTC, alarmClock, button1, button2, button3, button4);


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int alarmHours = 19, alarmMinutes = 38;
int ledPin = 6;
const uint16_t update_rate_ms = 25;

int i;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.print("Startup\n");
  
  button1.init(2, update_rate_ms);
  button2.init(3, update_rate_ms);
  button3.init(4, update_rate_ms);
  button4.init(5, update_rate_ms);

  
	// initialize digital pin LED_BUILTIN as an output.
	Wire.begin();
	pinMode(LED_BUILTIN, OUTPUT);

  Serial.print("Starting RTC\n");
  // Initialize RTC
//  RTC.begin();
  if (! RTC.begin()) {
    Serial.print("Couldn't find RTC\n");
  }
  Serial.print("RTC Started\n");
  if (RTC.lostPower()) {
    Serial.print("RTC is NOT running!\n");
    // Set the date and time at compile time
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
//   RTC.adjust(DateTime(__DATE__, __TIME__)); //removing "//" to adjust the time
    // The default display shows the date and time
  Serial.print("RTC Started\n");
  DateTime now = RTC.now();
  alarmClock.setAlarmTime(6, 10);
  alarmClock.setAlarmLength(1800);
  alarmClock.enableAlarm();
  print_time(now);
  i=0;
  display.Init(update_rate_ms);
}


// the loop function runs over and over again forever
void loop() {
  DateTime now = RTC.now();

  // Check buttons pressed;
  button1.update();
  button2.update();
  button3.update();
//  button4.update();

  // Update menu
  menu.update();

  // Update alarm


  // Update display

  
  alarmClock.update(now);
//  Serial.print("Alarm ");
//  Serial.print(alarmClock.getAlarmHours(), DEC);
//  Serial.print(":");
//  Serial.print(alarmClock.getAlarmMinutes(), DEC);
//  Serial.println();
  
  if(alarmClock.getAlarmActive())
  {
    setLightBrightness(alarmClock.getAlarmProgress());
  }
  
//  display.ShowTime(now.hour(), now.minute());

  delay(update_rate_ms);

  if(i<255) i++;
  else i=0;
  setLightBrightness((float) (i) / (float) 255);
}


//bool check_alarm(int alarmHours, int alarmMinutes, DateTime now){
//  if ( now.hour() == alarmHours && now.minute() == alarmMinutes ){
//    return true;
//  }
//  else {
//    return false;
//    }
//  }


//void set_alarm(int alarmHours, int alarmMinutes){
//  int a=1;
//}


void setLightBrightness(float factor)
{
    float brightness = factor * 255.0; 
    analogWrite(ledPin, brightness);
}


void print_time(DateTime now){
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print("\n");
}
