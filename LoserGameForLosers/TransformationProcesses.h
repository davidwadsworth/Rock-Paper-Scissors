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

class ChooseAttack: public Process
{
	Entity *left_, *right_;
	bool left_is_player_, right_is_player_;
	bool not_initialized_;
public:
	ChooseAttack(Entity * player_left, Entity * player_right)
		: not_initialized_(true)
	{
		left_is_player_ = player_left->has_component<ControllerComponent>();
		right_is_player_ = player_right->has_component<ControllerComponent>();

		left_ = player_left;
		right_ = player_right;
	}

	bool do_work() override
	{

		if (not_initialized_)
		{
			if (left_is_player_)
			{
				const auto left_box = Game::assets->create_option_box(options_choose_attack, { 0, SCREEN_HALF_HEIGHT }, true);
				left_box->get_component<OptionsComponent>().change_target(left_);
			}
			if (right_is_player_)
			{
				const auto right_box = Game::assets->create_option_box(options_choose_attack, { SCREEN_HALF_WIDTH * 5 / 4, SCREEN_HALF_HEIGHT }, false);
				right_box->get_component<OptionsComponent>().change_target(left_);
			}
			not_initialized_ = false;
		}

		if (!manager.get_group(Game::group_cursors).size())
		{
			return true;
		}
		
		return false;
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