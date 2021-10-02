#ifndef _HEADER_SONGPLAYER_H_
#define _HEADER_SONGPLAYER_H_

#include "string"
#include "Clock.h"
#include "tmrpcm.h"

using namespace std;

// Class that controls all playback of songs
class SongPlayer {
public:
	// Constructs songplayer with a clock pointer passed in
	SongPlayer(Clock* clck);

	// Pauses playback
	void pause();

	// Increases the volume (max is 7)
	void increaseVolume();

	// Decreases the volume (min is 0)
	void decreaseVolume();

	// Checks if the song is currently playing
	bool isSongPlaying();

	// Changes the selected song
	void updateSong(string songName);

private:
	// The old song that was playing
	string oldSongName;

	// Pointer to the clock being used in the alarm clock
	Clock* clock = nullptr;

	// Initial volume
	int volume = 6;

	// The player library used to play audio files
	TMRpcm player;

	// State of whether the song is playing or nots
	bool isPlaying;
};

#endif /* _HEADER_SONGPLAYER_H_ */
