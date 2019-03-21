#pragma once
#include <SDL_mixer.h>

struct PlayMessage
{
	int id;
	int volume;
};

class Audio
{
public:
	virtual ~Audio() {}
	virtual void play_sound(int sound_id) = 0;
	virtual void stop_sound(int sound_id) = 0;
	virtual void stop_all_sound() = 0;
};