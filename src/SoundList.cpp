#include "../header/SoundList.h"

int SoundList::getLength() {
	return fileNames.size();
}

string SoundList::getNameAt(int i) {
	// Returns message if the song is not found or the song if it is
	if (i == -1) return "Hee Ho :(";
	return (fileNames)[i];
}

int SoundList::getSelectedIndex() {
	return (fileNames.size() == 0) ? -1 : selectedIndex;
}

int SoundList::getHoveringIndex() {
	return (fileNames.size() == 0) ? -1 : hoveringIndex;
}

void SoundList::setSelectedIndex(int ind) {
	selectedIndex = ind;
}

void SoundList::getSoundBounds(int* lowerBound, int* upperBound, int intervalLength) {
	if (fileNames.size() < intervalLength) {
		*lowerBound = 0;
		*upperBound = fileNames.size();
	} else if (hoveringIndex < intervalLength) {
		*lowerBound = 0;
		*upperBound = intervalLength;
	} else if (fileNames.size() - hoveringIndex <= intervalLength) {
		*lowerBound = selectedIndex;
	} else if (hoveringIndex < lowerBound) {
		*lowerBound = selectedIndex;
		*upperBound = selectedIndex + intervalLength;
	} else if (hoveringIndex > upperBound) {
		*upperBound = selectedIndex;
		*lowerBound = upperBound - intervalLength;
	}
}

void SoundList::loadNames() {
	musicFolder = SD.open("music/"); // Opens folder
	fileNames.erase(fileNames.begin(), fileNames.end()); // clears filename vector

	// Loops through all files in the folder and adds their name to the vector
	File entry = musicFolder.openNextFile();
	string name;
	while (entry) {
	  name.assign(entry.name());
	  fileNames.push_back(name);
	  entry.close();
	  entry = musicFolder.openNextFile();
	}
	musicFolder.close();
}

void SoundList::incrementHoveringIndex() {
	hoveringIndex = (hoveringIndex + 1) % fileNames.size();
}

void SoundList::decrementHoveringIndex() {
	if (hoveringIndex - 1 == -1) hoveringIndex = fileNames.size() - 1;
	else hoveringIndex = (hoveringIndex - 1) % fileNames.size();
}
