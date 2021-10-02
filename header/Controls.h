#ifndef _CONTROLS_H_
#define _CONTROLS_H_
#include "Arduino.h"

// The pin numbers for the input of the different buttons
enum PinType{
	CHANGE_MIN = 10,
	CHANGE_HOUR = 12,
	TURN_ALARM_OFF = 8,
	TIME_SWITCHER = 9,
	SCREEN_STATE_SWITCH = 5,
	VOLUME_UP = 4,
	PLAY = 2,
	VOLUME_DOWN = 3
};

// The different states of the Buttons
enum ButtonState{
	NOT_PRESSED = LOW,
	PRESSED = HIGH
};

// A Button struct that allows button objects to be created
struct Button {
	private:
		int port; // The port that the button is wired to
		short DEBOUNCE_TIME = 250; // Time between consecutive button presses (ms)
		unsigned long pressTime; // The amount of time the button was last pressed (ms)

	public:
		Button(int pin);
		bool isButtonPressed();
};

// A Class that initializes and controls all buttons in the project
class Controls {
private:
	Button changeMinButton;
	Button changeHourButton;
	Button alarmOffButton;
	Button timeSwitchButton;
	Button screenSwitchButton;
	Button volumeUpButton;
	Button volumeDownButton;
	Button playButton;
public:
	Controls();

	// Methods to check when each button is pressed
	bool isChangeMinPressed();
	bool isChangeHourPressed();
	bool isAlarmOffPressed();
	bool isTimeSwitchPressed();
	bool isScreenSwitchPressed();
	bool isVolumeUpPressed();
	bool isVolumeDownPressed();
	bool isPlayPressed();
};

#endif // _CONTROLS_H_
