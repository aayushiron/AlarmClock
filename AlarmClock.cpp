#include "AlarmClock.h"
#include <TFT_HX8357.h> // Hardware-specific library
#include "Fonts/GFXFF/FreeMono24pt7b.h"
#include <SD.h>
#include <SPI.h>
#include <pcmRF.h>

TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library
SoundList soundList;
Clock clock = Clock();
SongPlayer player = SongPlayer(&clock);
Screen screen = Screen(&clock, &tft, &soundList, &player);
Controls controls = Controls();

File root;

// Forward declaring functions
void handleButtonInputs();
void playAlarm();

//The setup function is called once at startup of the sketch
void setup()
{
	// Initializes the screen
	tft.init();
	tft.setRotation(1);
	tft.fillScreen(BACKGROUND_COLOR);
	tft.setTextSize(LARGE_FONT);
	tft.setFreeFont(&FreeMono24pt7b);

	// Starts the serial to print out messages
	Serial.begin(115200);

	Serial.print("Initializing SD card...");

	// Starts the SD card
	if (!SD.begin(53)) {
	  Serial.println("initialization failed!");
	  return;
	}
	Serial.println("initialization done.");

	// Loads names of the songs and updates the player
	soundList.loadNames();
	player.updateSong(soundList.getNameAt(soundList.getSelectedIndex()));

	Serial.println("done!");

	pinMode(7, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
	handleButtonInputs();
	clock.updateTime();
	player.updateSong(soundList.getNameAt(soundList.getSelectedIndex()));
	screen.updateScreen();
	playAlarm();
}

void handleButtonInputs() {
	if (controls.isAlarmOffPressed()) {
		if (clock.isAlarmRinging()) clock.turnOffAlarm();
		else if (clock.isAlarmOn()) clock.setAlarmOn(false);
		else clock.setAlarmOn(true);
	}

	if (controls.isChangeMinPressed()) {
		if (screen.getScreenState() == ScreenState::TIME_SWITCHING) clock.incrementMinutes();
		else if (screen.getScreenState() == ScreenState::ALARM_TIME_SWITCHING) clock.incrementAlarmMinutes();
	}

	if (controls.isChangeHourPressed()) {
		if (screen.getScreenState() == ScreenState::TIME_SWITCHING) clock.incrementHours();
		else if (screen.getScreenState() == ScreenState::ALARM_TIME_SWITCHING) clock.incrementAlarmHours();
	}

	if (controls.isVolumeUpPressed()) {
		// Go up lift if screen on song select or pause/play a song if on time
		if (screen.getScreenState() == ScreenState::SOUND_SELECT) soundList.decrementHoveringIndex();
		else player.increaseVolume();
	}

	if (controls.isVolumeDownPressed()) {
		// Go down list if screen on song select or pause/play a song if on time
		if (screen.getScreenState() == ScreenState::SOUND_SELECT) soundList.incrementHoveringIndex();
		else player.decreaseVolume();
	}

	if (controls.isPlayPressed()) {
		// Select a song if screen on song select or pause/play a song if on time
		if (screen.getScreenState() == ScreenState::SOUND_SELECT) {
			soundList.setSelectedIndex(soundList.getHoveringIndex());
			player.updateSong(soundList.getNameAt(soundList.getSelectedIndex()));
		}
		else player.pause();
	}

	if (controls.isScreenSwitchPressed()) {
		if (screen.getScreenState() == ScreenState::SOUND_SELECT) screen.changeScreenState(ScreenState::TIME);
		else {
			if (player.isSongPlaying()) player.pause();
			screen.changeScreenState(ScreenState::SOUND_SELECT);
		}
	}

	if (controls.isTimeSwitchPressed()) {
		// Switch to the correct state using the current screen state
		switch (screen.getScreenState()) {
		case ScreenState::ALARM_TIME_SWITCHING:
			screen.changeScreenState(ScreenState::TIME);
			break;
		case ScreenState::TIME:
			screen.changeScreenState(ScreenState::TIME_SWITCHING);
			break;
		case ScreenState::TIME_SWITCHING:
			screen.changeScreenState(ScreenState::ALARM_TIME_SWITCHING);
			break;
		}
	}
}

void playAlarm() {
	// Play a tone for 250 seconds and be silent for 250 seconds if
	// alarm is ringing
	if (clock.isAlarmRinging() && millis() % 500 < 250) tone(7, 1000);
	else noTone(7);
}
