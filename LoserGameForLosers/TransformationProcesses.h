#pragma once
#include "Process.h"
#include <string>
#include "Game.h"

class FadeInImage : public Process
{
	Uint8 alpha_;
	int atlas_id_;
	Entity * asset_;
public:
	FadeInImage(int atlas_id)
		: alpha_(0), atlas_id_(atlas_id)
	{}

	bool do_work() override;

	float work_done() override { return static_cast<float>(alpha_) / 255.0f; }
};

class FadeOutImage : public Process
{
	Uint8 alpha_;
	Entity * asset_;
public:

	FadeOutImage(Entity * entity)
		: alpha_(255), asset_(entity)
	{}

	FadeOutImage(std::string image_id, SDL_Rect dest)
		: alpha_(255)
	{
	}

	FadeOutImage(std::string image_id, SDL_Rect dest, int round_number)
		: alpha_(255)
	{
		auto x = (round_number % 3) * NUMBER_WIDTH;
		auto y = (round_number / 3) * NUMBER_HEIGHT;

		SDL_Rect src = { x, y, NUMBER_WIDTH, NUMBER_HEIGHT };

	}

	bool do_work() override;

	float work_done() override { return 255 / std::abs(alpha_ - 255); }
};

class CreatePrompt: public Process
{
	int atlas_id_, sprite_id_;
	Vector2D position_;
public:
	CreatePrompt(int atlas_id, int sprite_id, Vector2D image_position)
		: atlas_id_(atlas_id), sprite_id_(sprite_id), position_(image_position)
	{}

	bool do_work() override
	{
		auto sprite_address = Game::data->get_sprite_address(atlas_id_, sprite_id_);
		auto dest = new SDL_Rect{ static_cast<int>(position_.x), static_cast<int>(position_.y), sprite_address->original_width, sprite_address->original_height };
		Game::assets->create_prompt(atlas_id_, sprite_id_, dest);
		return true;
	}

	float work_done() override
	{
		return 1;
	}
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