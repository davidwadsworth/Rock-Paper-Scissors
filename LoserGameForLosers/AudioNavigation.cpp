#include "stdafx.h"
#include "AudioNavigation.h"

namespace Navigation
{
	PlaySound::PlaySound(const int id)
		: sound_id_(id)
	{}

	int PlaySound::choose_path()
	{
		Game::audio_queue->play_sound(sound_id_);
		return true;
	}

	PlayMusic::PlayMusic(const int id, const int loop)
		: music_id_(id), loop_(loop)
	{}

	int PlayMusic::choose_path()
	{
		Game::audio_queue->play_music(music_id_, loop_);
		return true;
	}

	int StopMusic::choose_path()
	{
		Game::audio_queue->stop_music();
		return 1;
	}
}

