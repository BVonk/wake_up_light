

/*
 Name:		wake_up_light.ino
 Created:	12/10/2017 12:12:34 AM
 Author:	bartl
*/

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include "AlarmClock.h"
#include "Menu.h"
#include "PushButton.hpp"


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
RTC_DS3231 RTC;
//RTC_DS1307 RTC;
AlarmClock alarmClock;
PushButton button1;
PushButton button2;
PushButton button3;
PushButton button4;
Menu menu(RTC, alarmClock, button1, button2, button3, button4);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int alarmHours = 19, alarmMinutes = 38;
int ledPin = 6;
const uint16_t update_rate_ms = 20;



// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.print("Startup\n");

  button1.init(2, update_rate_ms);
  button2.init(3, update_rate_ms);
  button3.init(4, update_rate_ms);
  button4.init(5, update_rate_ms);
//  lcd.begin(16,2);
//  lcd.backlight();
//  lcd.backlight();
//  lcd.clear();
  
	// initialize digital pin LED_BUILTIN as an output.
	Wire.begin();
	pinMode(LED_BUILTIN, OUTPUT);

  Serial.print("Starting RTC\n");
  // Initialize RTC
//  RTC.begin();
  if (! RTC.begin()) {
    Serial.print("Couldn't find RTC\n");
  }
  if (RTC.lostPower()) {
    Serial.print("RTC is NOT running!\n");
    // Set the date and time at compile time
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
//   RTC.adjust(DateTime(__DATE__, __TIME__)); //removing "//" to adjust the time
    // The default display shows the date and time

  DateTime now = RTC.now();
  alarmClock.setAlarmTime(6, 5);
  alarmClock.setAlarmLength(1800);
  alarmClock.enableAlarm();
}


// the loop function runs over and over again forever
void loop() {
  DateTime now = RTC.now();

  // Check buttons pressed;
  button1.update();
  button2.update();
  button3.update();
  button4.update();

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

  
//  lcd.setCursor(0, 1);
//  lcd.print("Hour:");
//  if (now.hour()<=9)
//  {
//    lcd.print("0");
//  }
//  lcd.print(now.hour(), DEC);
//
//  lcd.print(":");
//  if (now.minute()<=9)
//  {
//    lcd.print("0");
//  }
//  lcd.print(now.minute(), DEC);

//	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//	delay(100);                       // wait for a second
//	digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);                       // wait for a second
  now = RTC.now();
//  print_time(now);

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

//
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

