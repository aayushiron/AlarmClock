#include "../header/Controls.h"

Button::Button(int pin) : pressTime(0) {
	port = pin;
	pinMode(pin, INPUT);
}

bool Button::isButtonPressed() {
	// Checking if it has been enough time to register another button press
	if (millis() - pressTime >= DEBOUNCE_TIME && !digitalRead(port)) {
		pressTime = millis(); // Storing a new value
		return true;
	}

	return false;
}

Controls::Controls() {
	// Initializes all buttons to the correct port
	changeHourButton = Button(PinType::CHANGE_HOUR);
	changeMinButton = Button(PinType::CHANGE_MIN);
	playButton = Button(PinType::PLAY);
	screenSwitchButton = Button(PinType::SCREEN_STATE_SWITCH);
	timeSwitchButton = Button(PinType::TIME_SWITCHER);
	alarmOffButton = Button(PinType::TURN_ALARM_OFF);
	volumeDownButton = Button(PinType::VOLUME_DOWN);
	volumeUpButton = Button(PinType::VOLUME_UP);
}

bool Controls::isAlarmOffPressed() {return alarmOffButton.isButtonPressed();}
bool Controls::isChangeHourPressed() {return changeHourButton.isButtonPressed();}
bool Controls::isTimeSwitchPressed() {return timeSwitchButton.isButtonPressed();}
bool Controls::isScreenSwitchPressed() {return screenSwitchButton.isButtonPressed();}
bool Controls::isVolumeUpPressed() {return volumeUpButton.isButtonPressed();}
bool Controls::isVolumeDownPressed() {return volumeDownButton.isButtonPressed();}
bool Controls::isPlayPressed() {return playButton.isButtonPressed();}
bool Controls::isChangeMinPressed() {return changeMinButton.isButtonPressed();}
