#ifndef _SOUNDLIST_H_
#define _SOUNDLIST_H_

#include <Arduino.h>
#include <vector>
#include <string>
#include <SD.h>
#include <SPI.h>

using namespace std;

// The class that contains a list of all songs on the SD card
class SoundList {
private:
	// The names of all song files on the sd card
	vector<string> fileNames = vector<string>();

	// The folder where all music is stored
	File musicFolder;

	// The indexes used to find the song being played
	int selectedIndex, hoveringIndex;

public:
	int getLength();
	string getNameAt(int index);
	int getSelectedIndex();
	void setSelectedIndex(int ind);
	int getHoveringIndex();

	void incrementHoveringIndex();
	void decrementHoveringIndex();

	// Gets the top and bottom bounds of the songs that fit in interval length based
	// on the currently selected song
	void getSoundBounds(int* lowerBound, int* upperBound, int intervalLength);

	// Loads all file names from sd card
	void loadNames();
};



#endif /* _SOUNDLIST_H_ */
