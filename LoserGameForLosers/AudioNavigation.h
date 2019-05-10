#pragma once
#include "Navigator.h"

namespace Navigation
{
	class PlaySound : public Navigator
	{
		int sound_id_;
	public:
		explicit PlaySound(int id);

		int choose_path() override;
	};

	class PlayMusic : public Navigator
	{
		int music_id_, loop_;
	public:
		PlayMusic(int id, int loop);

		int choose_path() override;

	};

	class StopMusic : public Navigator
	{
	public:
		StopMusic() {}

		int choose_path() override;
	};
}
