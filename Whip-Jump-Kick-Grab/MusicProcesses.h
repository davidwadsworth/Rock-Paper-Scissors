#pragma once
#include "Processes.h"

class PlaySound : public Process
{
	float work_complete_;
	int sound_id_;
public:
	explicit PlaySound(const int id)
		: work_complete_(0), sound_id_(id)
	{}

	bool do_work() override
	{
		Game::audio_queue->play_sound(sound_id_);
		return true;
	}

	float work_done() override { return work_complete_; }
};

class PlayMusic : public Process
{
	float work_complete_;
	int music_id_, loop_;
public:
	PlayMusic(const int id, const int loop)
		: work_complete_(0), music_id_(id), loop_(loop)
	{}

	bool do_work() override
	{
		Game::audio_queue->play_music(music_id_, loop_);
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }

};

class StopMusic : public Process
{
	float work_complete_;
public:
	StopMusic()
		: work_complete_(0)
	{}

	bool do_work() override
	{
		Game::audio_queue->stop_music();
		work_complete_ = 1;
		return true;
	}

	float work_done() override { return work_complete_; }
};