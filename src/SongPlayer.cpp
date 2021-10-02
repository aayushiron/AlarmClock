#include "../header/SongPlayer.h"

SongPlayer::SongPlayer(Clock* clck) {
	clock = clck;
	player = TMRpcm();
	player.loop(0); // Makes sure the clock doesn't keep looping the song
	player.speakerPin = 11; // Initializes the speaker
	isPlaying = false;
}

bool SongPlayer::isSongPlaying() {return isPlaying;}

void SongPlayer::pause() {
	player.pause();
	isPlaying = !isPlaying;
}

void SongPlayer::increaseVolume() {
	if (volume < 6) {
		volume++;
		player.setVolume(volume);
	}
}

void SongPlayer::decreaseVolume() {
	if (volume > 0) {
		volume--;
		player.setVolume(volume);
	}
}

void SongPlayer::updateSong(string songName) {
	// Updates the song information if the song is switched
	if (oldSongName != songName) {
		player.stopPlayback();
		player.play((char*) ("music/" + songName).c_str());
		if (!isPlaying) {
			player.pause();
		}
		oldSongName = songName;
	}
}
