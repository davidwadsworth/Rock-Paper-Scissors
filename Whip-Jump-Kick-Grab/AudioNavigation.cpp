#include "stdafx.h"
#include "AudioNavigation.h"

namespace Navigation
{
	PlaySound::PlaySound(AudioQueue * player, const int id)
		: sound_id_(id), player_(player)
	{}

	int PlaySound::choose_path()
	{
		player_->play_sound(sound_id_);
		return true;
	}

	PlayMusic::PlayMusic(AudioQueue * player, const int id, const int loop)
		: music_id_(id), loop_(loop), player_(player)
	{}

	int PlayMusic::choose_path()
	{
		player_->play_music(music_id_, loop_);
		return true;
	}

	StopMusic::StopMusic(AudioQueue * player)
		: player_(player)
	{}

	int StopMusic::choose_path()
	{
		player_->stop_music();
		return 1;
	}
}

