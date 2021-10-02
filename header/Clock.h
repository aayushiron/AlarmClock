#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "Wire.h"
#include "ds3231.h"

typedef unsigned short ctime; // Type to signify when something measures time

// Class that stores the information for the current time and the alarm
class Clock {
private:

	// The current second (in military time)
	ctime second;

	unsigned short alarmTime; // The amount of time the alarm has been ringing for in seconds
	unsigned short ALARM_LENGTH = 255; // The time the alarm should ring for in seconds
	bool alarmRinging; // True if the alarm is ringing
	bool alarmRang; // True if the alarm already rang

	// Checks if the alarm is actually on
	bool alarmOn;

	struct ts time;   // The current time
	struct ts aTime;  // The time the alarm is supposed to ring

public:
	Clock();

	// Must be called at least once every second
	void updateTime();

	ctime getMinutes();
	ctime getHours();
	ctime getSeconds();
	ctime getAlarmMinutes();
	ctime getAlarmHours();

	void setAlarmOn(bool aOn);
	bool isAlarmOn();

	bool isAlarmRinging();
	void turnOffAlarm();

	void incrementMinutes();
	void incrementHours();
	void incrementAlarmMinutes();
	void incrementAlarmHours();
};

#endif // _CLOCK_H_
