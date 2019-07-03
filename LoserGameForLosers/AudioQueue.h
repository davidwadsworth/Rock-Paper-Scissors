#pragma once
#include "Audio.h"
#include "AudioData.h"


class AudioQueue : public Audio
{
	AudioCollection *data_;

	std::vector<Mix_Music*> loaded_music_;
	std::vector<Mix_Chunk*> loaded_effects_;


	void load_music_files()
	{
		for (const auto& sound : data_->data)
		{
			switch (sound.encoding)
			{
			case 0:
				loaded_music_.push_back(Mix_LoadMUS(sound.path.c_str()));
				break;
			case 1:
				loaded_effects_.push_back(Mix_LoadWAV(sound.path.c_str()));
				break;
			default:
				return;
			}
		}
	}

public:
	AudioQueue() = default;

	explicit AudioQueue(AudioCollection* data)
		: data_(data)
	{
		load_music_files();
	}

	~AudioQueue() = default;

	void play_sound(const int sound_id) override
	{
		Mix_PlayChannel(-1, loaded_effects_[sound_id], 0);
	}

	void play_music(const int music_id, const int loops) override
	{
		Mix_PlayMusic(loaded_music_[music_id], loops);
	}

	void close() override
	{
		Mix_HaltMusic();
		data_ = nullptr;

		for (auto lm : loaded_music_)
			Mix_FreeMusic(lm);
		for (auto lc : loaded_effects_)
			Mix_FreeChunk(lc);
	}

	void stop_music() override
	{
		Mix_HaltMusic();
	}
};
