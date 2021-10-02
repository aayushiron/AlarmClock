#include "../header/Screen.h"
#include "../SymbolBitmaps.h"
#include <string>

Screen::Screen(Clock* clck, TFT_HX8357* tt, SoundList* list, SongPlayer* plyr) {
	clock = clck;

	tft = tt;

	soundList = list;

	player = plyr;

	// Sets the old value to 1 over the max value to ensure it isn't equal when the program runs
	oldHours = 25;
    oldMinutes = 61;
    oldSeconds = 61;

    state = ScreenState::TIME;
    oldState = state;

    oldColor = FOREGROUND_COLOR;

    oldHovSongIndex = -1;

    oldPlayState = true;
}

void Screen::updateScreen() {
	// Draws the correct screen based on the state of the program
	switch(state) {
	case ScreenState::TIME:
		drawTime(FOREGROUND_COLOR, false);
		break;
	case ScreenState::TIME_SWITCHING: case ScreenState::ALARM_TIME_SWITCHING:
		// Draws the time flashing when the alarm or time is being changed (every 250 ms)
		drawTime((millis() % 500 < 250) ? BACKGROUND_COLOR : FOREGROUND_COLOR, state == ScreenState::ALARM_TIME_SWITCHING);
		break;
	case ScreenState::SOUND_SELECT:
		// Draws the sound select if any informastion has been changed
		if (oldHovSongIndex != soundList->getHoveringIndex() || oldSelSongIndex != soundList->getSelectedIndex() || oldState == ScreenState::TIME)
			drawSoundSelect();
		break;
	}

	oldState = state;
}

void Screen::drawTime(uint16_t color, bool isAlarmTime) {
	// Resets the screen
	if (oldState == ScreenState::SOUND_SELECT) {
		tft->fillScreen(BACKGROUND_COLOR);
	}

	// Draws the time and the alarm symbol if the alarm is set
	if (state == ScreenState::TIME && (oldMinutes != clock->getMinutes() || oldColor != color || oldState == ScreenState::SOUND_SELECT))
		drawMinutesAndHours(color, state == ScreenState::ALARM_TIME_SWITCHING);

	drawAlarmSymbol();

	// Draws the seconds if they changed
	if (oldSeconds != clock->getSeconds() || oldState == ScreenState::SOUND_SELECT || oldState == ScreenState::ALARM_TIME_SWITCHING) {
		drawSeconds((isAlarmTime) ? BACKGROUND_COLOR : FOREGROUND_COLOR); // Hides the seconds if the alarm time is changed
	}

	// Flashes the Minutes and hours if the time is being changed
	if (oldColor != color && (state == ScreenState::TIME_SWITCHING || isAlarmTime)) drawMinutesAndHours(color, isAlarmTime);

	// Draws the Lines for the current song playing
	tft->drawFastHLine(10, ypos + 120, 460, FOREGROUND_COLOR);
	tft->drawFastHLine(10, ypos + 200, 460, FOREGROUND_COLOR);

	// Writes the current song playing
	tft->setTextSize(SMALL_FONT);
	tft->setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
	tft->drawString((char*) soundList->getNameAt(soundList->getSelectedIndex()).c_str(), 20, ypos + 140, 1);

	// Draws the sound select play or pause if needed
	if (oldPlayState != player->isSongPlaying() || oldState == ScreenState::SOUND_SELECT) {
		if (!oldPlayState) {
			tft->drawBitmap(420, ypos + 140, play_icon, 40, 40, BACKGROUND_COLOR);
			tft->drawBitmap(420, ypos + 140, pause_icon, 40, 40, FOREGROUND_COLOR);
		} else {
			tft->drawBitmap(420, ypos + 140, pause_icon, 40, 40, BACKGROUND_COLOR);
			tft->drawBitmap(420, ypos + 140, play_icon, 40, 40, FOREGROUND_COLOR);
		}
		oldPlayState = !oldPlayState;
	}

	// Resets text size for next run
	tft->setTextSize(LARGE_FONT);

	oldColor = color;
}

void Screen::drawSoundSelect() {
	soundList->loadNames();
	tft->fillScreen(BACKGROUND_COLOR); // Resets screen

	tft->setTextSize(SMALL_FONT); // Changes text size for song names
	// Creates variables for color (changes for each song)
	uint16_t colorBack = BACKGROUND_COLOR;
	uint16_t colorFront = FOREGROUND_COLOR;
	// Positions used to place each song name
	int yCurr = 10;
	int xPadding = 10;
	std::string currName;

	// Gets song indexes that will be shown on screen
	soundList->getSoundBounds(&lowerBound, &upperBound, MAX_NUM_SONGS);

	// Loops through all songs to be shown on screen
	for (int i = lowerBound; i < upperBound; i++) {
		// Changes the color based on when the song is being hovered on or not
		if (i == soundList->getHoveringIndex()) {
			colorFront = BACKGROUND_COLOR;
			colorBack = FOREGROUND_COLOR;
		} else {
			colorBack = BACKGROUND_COLOR;
			colorFront = FOREGROUND_COLOR;
		}

		// Draws all parts of the song
		tft->setTextColor(colorFront, BACKGROUND_COLOR);
		tft->fillRect(xPadding, yCurr, 460, 60, colorBack);
		tft->drawString((char*) soundList->getNameAt(i).c_str(), xPadding * 2, yCurr + 10, 1);

		// Draws the play symbol on the song currently playing
		if (i == soundList->getSelectedIndex()) tft->drawBitmap(480 - xPadding * 2 - 40, yCurr + 10, note_icon, 40, 40, colorFront);
		yCurr += 60;
	}

	// Updates variables
	oldHovSongIndex = soundList->getHoveringIndex();
	oldSelSongIndex = soundList->getSelectedIndex();

	// Resets text size
	tft->setTextSize(LARGE_FONT);
}

int Screen::drawString(char* oldStr, char* str, int xpos, int ypos, uint16_t color) {
	// Draws the original text in Black and then in the color passed in
	tft->setTextColor(BACKGROUND_COLOR, BACKGROUND_COLOR);
	tft->drawString(oldStr, xpos, ypos, 1);
	tft->setTextColor(color, BACKGROUND_COLOR);
	return tft->drawString(str, xpos, ypos, 1);
	tft->setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
}

int Screen::drawNumber(long oldNum, long num, int xpos, int ypos, uint16_t color) {
	// Draws the original number in Black and then in the color passed in (prints nothing if oldNum == -1)
	if (oldNum != -1) {
		tft->setTextColor(BACKGROUND_COLOR, BACKGROUND_COLOR);
		tft->drawNumber(oldNum, xpos, ypos, 1);
		tft->setTextColor(color, BACKGROUND_COLOR);
	}
	return tft->drawNumber(num, xpos, ypos, 1);
	tft->setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
}

ctime Screen::formatHours(ctime hours) {
	// Formats the time to be in 12 hour format
	return (hours % 12 == 0) ? 12 : hours % 12;
}

void Screen::drawMinutesAndHours(uint16_t color, bool isAlarmTime) {
	// Positions to draw different parts of the clock at
	int xpos = 0;
	int ytime = ypos + 10;
	int xtime;

	// The hours and minutes to be drawn
	ctime hours;
	ctime minutes;

	// Updates the hours and minutes based on the state of the screen
	if (isAlarmTime) {
		hours = clock->getAlarmHours();
		minutes = clock->getAlarmMinutes();
	} else {
		hours = clock->getHours();
		minutes = clock->getMinutes();
	}

	// Draw hours
	if (formatHours(hours) < 10) {
		if (formatHours(oldHours) < 10) {
		  xpos += drawNumber(0, 0, xpos, ypos, color); // Add seconds leading zero
		  xpos += drawNumber(formatHours(oldHours), formatHours(hours), xpos, ypos, color);
		} else {
		  xpos += drawNumber(formatHours(oldHours), 0, xpos, ypos, color);
		  xpos += drawNumber(-1, formatHours(hours), xpos, ypos, color);
		}
	} else {
	  if (formatHours(oldHours) < 10) {
		  xpos += drawNumber(0, formatHours(hours)/10, xpos, ypos, color);
		  xpos += drawNumber(formatHours(oldHours), formatHours(hours) % 10, xpos, ypos, color);
	  } else xpos += drawNumber(formatHours(oldHours), formatHours(hours), xpos, ypos, color);
	}

	xcolon = xpos; // Save colon coord for later to flash on/off later
	xpos += tft->drawString(":", xpos - 20, ypos - 8, 1) - 40;

	// Draws the minutes
	if (minutes < 10) {
	  if (oldMinutes < 10) {
		  xpos += drawNumber(0, 0, xpos, ypos, color); // Add seconds leading zero
		  xpos += drawNumber(oldMinutes, minutes, xpos, ypos, color);
		} else {
		  xpos += drawNumber(oldMinutes, 0, xpos, ypos, color);
		  xpos += drawNumber(-1, minutes, xpos, ypos, color);
		}
	} else {
		if (oldMinutes < 10) {
		  xpos += drawNumber(0, minutes/10, xpos, ypos, color);
		  xpos += drawNumber(oldMinutes, minutes % 10, xpos, ypos, color);
		} else xpos += drawNumber(oldMinutes, minutes, xpos, ypos, color);
	}

	oldMinutes = minutes;
	xsecs = xpos; // Save seconds 'x' position for later display updates
	xtime = xsecs + 20;

	tft->setTextSize(1);

	// Draws AM or PM depending on the time
	if (hours < 12) {
	  if (oldHours < 12) xtime += drawString("A", "A", xtime, ytime, FOREGROUND_COLOR);
	  else xtime += drawString("P", "A", xtime, ytime, FOREGROUND_COLOR);
	} else {
	  if (oldHours < 12) xtime += drawString("A", "P", xtime, ytime, FOREGROUND_COLOR);
	  else xtime += drawString("P", "P", xtime, ytime, FOREGROUND_COLOR);
	}
	drawString("M", "M", xtime, ytime, FOREGROUND_COLOR);

	oldHours = hours;

	tft->setTextSize(LARGE_FONT);
}

void Screen::drawSeconds(uint16_t color) {
	// Positions to draw different parts of the clock at
	int ysecs = ypos + 60;
	int xpos = xsecs;

	if (clock->getSeconds() % 2) { // Flash the colons on/off
		tft->setTextColor(BACKGROUND_COLOR, BACKGROUND_COLOR); // Set color to background color
		tft->drawString(":", xcolon - 20, ypos - 8, 1);     // Hour:minute colon
		tft->setTextSize(SMALL_FONT);
		xpos += tft->drawString(":", xsecs, ysecs, 1); // Seconds colon
		tft->setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);    // Set color back to foreground
	} else {
		tft->drawString(":", xcolon - 20, ypos - 8, 1);     // Hour:minute colon
		tft->setTextSize(SMALL_FONT);
		tft->setTextColor(color, BACKGROUND_COLOR);
		xpos += tft->drawString(":", xsecs, ysecs, 1); // Seconds colon
		tft->setTextColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
	}

	//Draw seconds
	if (clock->getSeconds() < 10) {
	  if (oldSeconds < 10) {
		  xpos += drawNumber(0, 0, xpos, ysecs, color); // Add seconds leading zero
		  xpos += drawNumber(oldSeconds, clock->getSeconds(), xpos, ysecs, color);
	  } else {
		  xpos += drawNumber(oldSeconds, 0, xpos, ysecs, color);
		  xpos += drawNumber(-1, clock->getSeconds(), xpos, ysecs, color);
	  }
	} else {
	  if (oldSeconds < 10) {
		  xpos += drawNumber(0, clock->getSeconds()/10, xpos, ysecs, color);
		  xpos += drawNumber(oldSeconds, clock->getSeconds() % 10, xpos, ysecs, color);
	  } else xpos += drawNumber(oldSeconds, clock->getSeconds(), xpos, ysecs, color);
	}

	oldSeconds = clock->getSeconds();
	tft->setTextSize(LARGE_FONT);
}

void Screen::drawAlarmSymbol() {
	if (clock->isAlarmRinging()) {
		tft->drawBitmap(xsecs + 30, 27, alarm_bitmap, 40, 40, (clock->getSeconds() % 2) ? BACKGROUND_COLOR : FOREGROUND_COLOR);
	} else if (!clock->isAlarmOn()) {
		tft->drawBitmap(xsecs + 30, 27, alarm_bitmap, 40, 40, BACKGROUND_COLOR);
	} else {
		tft->drawBitmap(xsecs + 30, 27, alarm_bitmap, 40, 40, FOREGROUND_COLOR);
	}
}
