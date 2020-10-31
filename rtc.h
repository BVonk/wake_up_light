#ifndef ___RTC_INCLUDE__
#define ___RTC_INCLUDE__

#include "Wire.h"
#include "Arduino.h"
#define DS3231_I2C_ADDRESS 0x68

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val);
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val);

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
	dayOfMonth, byte month, byte year);
void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte
	*dayOfMonth, byte *month, byte *year);
void displayTime();



#endif