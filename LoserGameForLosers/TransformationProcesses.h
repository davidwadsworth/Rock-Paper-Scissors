#pragma once
#include "Process.h"
#include "Game.h"

class DisplayPrompt : public Process
{
	int sprite_id_;
	SDL_Rect* prompt_rect_;
public:
	DisplayPrompt(int sprite_id)
		: sprite_id_(sprite_id), prompt_rect_(new SDL_Rect{0, 0, SCREEN_WIDTH, 160})
	{}

	bool do_work() override
	{
		Game::assets->create_prompt(sprite_id_, prompt_rect_);
		return true;
	}

	float work_done() override
	{
		return 1;
	}
};

class DisplayRoundPrompt : public Process
{
	SDL_Rect *round_dest_, *tens_dest_, *ones_dest_;
	int round_id_, number_id_, round_number_;

public:
	DisplayRoundPrompt(int round_id, int number_id, int round_number)
		: round_dest_(new SDL_Rect{ 0,0, 600, 160 }), tens_dest_(new SDL_Rect{ 600, 0, 100, 160 }), ones_dest_(new SDL_Rect{700, 0, 100, 160}), 
		  round_id_(round_id), number_id_(number_id), round_number_(round_number)
	{}

	bool do_work() override
	{
		Game::assets->create_prompt(round_id_, round_dest_);
		Game::assets->create_prompt(number_id_ + (round_number_ / 10), tens_dest_);
		Game::assets->create_prompt(number_id_ + (round_number_ % 10), ones_dest_);
		return true;
	}

	float work_done() override { return 1; }
};

class ClearPrompts : public Process
{
public:
	ClearPrompts()
	{}

	bool do_work() override
	{
		for (auto& p : manager.get_group(Game::group_prompts))
		{
			p->del_group(Game::group_prompts);
			p->destroy();
		}
		return true;
	}

	float work_done() override { return 1; }
};