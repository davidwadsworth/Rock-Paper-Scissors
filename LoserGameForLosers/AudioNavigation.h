#pragma once
#include "Navigator.h"

namespace Navigation
{
	class PlaySound : public Navigator
	{
		int sound_id_;
		AudioQueue * player_;
	public:
		explicit PlaySound(AudioQueue * player, int id);

		int choose_path() override;
	};

	class PlayMusic : public Navigator
	{
		int music_id_, loop_;
		AudioQueue * player_;
	public:
		PlayMusic(AudioQueue * player, int id, int loop);

		int choose_path() override;

	};

	class StopMusic : public Navigator
	{
		AudioQueue * player_;
	public:
		explicit StopMusic(AudioQueue * player);
		int choose_path() override;
	};
}
