#pragma once
#include "Audio.h"
#include "AudioData.h"


class AudioQueue : public Audio
{
	int channel_count_;
	AudioCollection* data_;

	void load_music_files()
	{
		for (auto sound : data_->data)
		{	
			switch (sound.id)
			{
			case 0:



			default:
				;
			}
		}
	}

public:
	AudioQueue(AudioCollection * data)
		: data_(data)
	{}

	~AudioQueue() = default;

	void play_sound(const int sound_id) override
	{
		
	}

	void stop_sound(int sound_id) override
	{}

	void stop_all_sound() override
	{}

};
