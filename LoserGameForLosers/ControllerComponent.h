#pragma once

#include "ECS.h"
#include <SDL.h>
#include "Controller.h"
#include "KeyboardHandler.h"

class ControllerComponent : public Component
{
	KeyboardHandler * keyboard_;

	std::vector<SDL_Scancode> keys_ = { SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_4 };

	int controller_id_;

	Controller * controller_;
public:


	ControllerComponent(const int controller_id) : controller_id_(controller_id)
	{}

	ControllerComponent(const int controller_id, const std::vector<SDL_Scancode> keys) : keys_(keys), controller_id_(controller_id)
	{}

	~ControllerComponent()
	= default;

	void init() override
	{
		keyboard_ = new KeyboardHandler;
		controller_ = Game::data->get_controller(controller_id_);
	}

	void change_controller(const int new_controller)
	{
		controller_ = Game::data->get_controller(controller_id_);
	}

	bool keyboard_check(const int key)
	{
		auto is_pressed = true;

		const auto first_key = key % 10;

		if (first_key < 0)
			is_pressed &= !keyboard_->check_key_state(keys_[std::abs(first_key)]);		
		else
			is_pressed &= keyboard_->check_key_state(keys_[first_key]);
		if (std::abs(key) > 9)
			is_pressed &= keyboard_check(key / 10);

		return is_pressed;
	}

	void update() override
	{
		for (auto& c : controller_->current_controller)
		{
			if (keyboard_check(c->keys))
				c->command->execute(entity);
			else
				c->command->idle(entity);
		}
	}

};

