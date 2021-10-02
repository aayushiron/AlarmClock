#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Clock.h"
#include "SoundList.h"
#include "SongPlayer.h"
#include <TFT_HX8357.h>

#define TFT_GREY 0x5AEB

// enum of all the different states the screen can be in
enum ScreenState{TIME, SOUND_SELECT, TIME_SWITCHING, ALARM_TIME_SWITCHING};

// Constants for the background and foreground color
const uint16_t BACKGROUND_COLOR = TFT_BLACK;
const uint16_t FOREGROUND_COLOR = TFT_RED;

// The two different font sizes in the UI
const uint8_t LARGE_FONT = 3;
const uint8_t SMALL_FONT = 1;

// The max number of songs that can be shown in a list at once
const byte MAX_NUM_SONGS = 5;

// Class that controls all things displayed on the screen
class Screen {
private:
	Clock* clock;         // The clock object used to keep time
	TFT_HX8357* tft;      // The screen object used to interface with the time
	SoundList* soundList; // The list of songs on the SD card
	SongPlayer* player;   // The song player that controls song playback

	// The minutes, seconds, and hours last screen refresh
	ctime oldMinutes, oldSeconds, oldHours;

	// The x position of the colon between min, hour, and seconds
	int xcolon, xsecs;

	// The index of the song being hovered on
	int oldHovSongIndex;

	// The index of the selected song
	int oldSelSongIndex;

	// Draws time in the passed in color and whether it is an alarm or not
	void drawTime(uint16_t color, bool isAlarmTime);

	// Draws the sound select ui
	void drawSoundSelect();

	// Draws the passed in string at the passed in position (REQUIRES THE OLD STRING)
	int drawString(char* oldStr, char* str, int xpos, int ypos, uint16_t color);
	// Draws the passed in number at the passed in position (REQUIRES THE OLD NUMBER)
	int drawNumber(long oldNum, long num, int xpos, int ypos, uint16_t color);

	// Draws the current minutes and hours
	void drawMinutesAndHours(uint16_t color, bool isAlarmTime);

	// Draws the current seconds
	void drawSeconds(uint16_t color);

	// Draws the alarm bell symbol
	void drawAlarmSymbol();

	// Formats the hours in 12 AM/PM time
	ctime formatHours(ctime hours);

	// The current and old state of the screen
	ScreenState state, oldState;

	int ypos = 85; // Top left corner of clock text, about half way down

	uint16_t oldColor;

	// The upper and lower bounds of the song list being displayed
	int lowerBound, upperBound;

	// The old state of the songs being played
	bool oldPlayState;

public:
	// The constructor that takes in a clock, a screen, a list, and a songplayer
	Screen(Clock* clck, TFT_HX8357* tt, SoundList* list, SongPlayer* plyr);

	// Updates the screen with the correct information
	void updateScreen();

	// Changes the state of the screen to the new state
	void changeScreenState(ScreenState newState) {state = newState;}
	ScreenState getScreenState() {return state;}
};


#endif /* _SCREEN_H_ */
