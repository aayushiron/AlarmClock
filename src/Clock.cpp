#include "../header/Clock.h"
#include "Arduino.h"

Clock::Clock() {
	alarmOn = false;
	alarmRinging = false;
	alarmRang = false;

	Wire.begin();
}

void Clock::updateTime() {
	// Updates the current time
	DS3231_get(&time);

	// Checks if a second has passed
	if (second != time.sec) {
		second = time.sec;

		// Updates the amount of time the alarm has been ringing for
		if (alarmRinging) alarmTime++;
	}

	if (alarmOn) {
		// Checks if it is time to start ringing the alarm
		if (!alarmRang && !alarmRinging && time.hour == aTime.hour && time.min == aTime.min) {
			alarmRinging = true;
			// Resets the time the alarm has been ringing for
			alarmTime = 0;
		}
		// Turns off the alarm if it has rung enough
		else if (alarmRinging && alarmTime >= ALARM_LENGTH) {
			alarmRinging = false;
		}

		// Resets alarmRang if it is no longer the time for the alarm to ring
		if (alarmRang && time.hour != aTime.hour && time.min != aTime.min) {
			alarmRang = false;
		}
	}
	// Stops the alarm from ringing if it is not on
	else if (alarmRinging) {
		alarmRinging = false;
		alarmRang = false;
	}
}

ctime Clock::getMinutes() {
	return time.min;
}

ctime Clock::getHours() {
	return time.hour;
}

ctime Clock::getSeconds() {
	return time.sec;
}

ctime Clock::getAlarmMinutes() {
	return aTime.min;
}

ctime Clock::getAlarmHours() {
	return aTime.hour;
}

void Clock::setAlarmOn(bool aOn) {
	alarmOn = aOn;
}

bool Clock::isAlarmOn() {
	return alarmOn;
}

bool Clock::isAlarmRinging() {
	return alarmRinging;
}

void Clock::turnOffAlarm() {
	alarmRinging = false;
	// Sets alarmRang to true if it is still the correct time to turn off the alarm
	if (time.hour == aTime.hour && time.min == aTime.min) alarmRang = true;
}

void Clock::incrementHours() {
	DS3231_get(&time); // Get the current time
	time.hour = (++time.hour) % 24;
	DS3231_set(time);
}

void Clock::incrementMinutes() {
	DS3231_get(&time); // Get the current time
	time.min = (++time.min) % 60;
	DS3231_set(time); // Update the current time
}

void Clock::incrementAlarmHours() {
	aTime.hour = (++aTime.hour) % 24;
}

void Clock::incrementAlarmMinutes() {
	aTime.min = (++aTime.min) % 60;
}
