#pragma once
#include "Audio.h"

struct PlayMessage
{
	int id;
	int volume;
};

class AudioPlayer : public Audio
{
public:
	AudioPlayer(){}


	void init()
	{
	}
	void play_sound(int sound_id) override;
	void stop_sound(int sound_id) override;
	void stop_all_sound() override;

private:
	static const int MAX_PENDING = 16;

	static PlayMessage pending_[MAX_PENDING];
	static int numPending_;
};