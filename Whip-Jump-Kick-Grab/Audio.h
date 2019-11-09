#pragma once
#include <SDL_mixer.h>

/**
 * @author David Wadsworth
 * 
 * abstract audio creation
 */

class Audio
{
public:
	virtual ~Audio() = default;
	virtual void play_sound(int sound_id) = 0;
	virtual void play_music(int music_id, int loops) = 0;
	virtual void stop_music() = 0;
	virtual void close() = 0;
};