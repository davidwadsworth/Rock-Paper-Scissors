#pragma once
#include "Audio.h"



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
	Mix_Music * playing_;
};