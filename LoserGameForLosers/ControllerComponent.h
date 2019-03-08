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

	ControllerData * data_;
	Controller controller_;
public:

	bool player1;

	explicit ControllerComponent(const int controller_id) : controller_id_(controller_id), player1(true)
	{}

	ControllerComponent(const int controller_id, const std::vector<SDL_Scancode> keys) : keys_(keys), controller_id_(controller_id), player1(false)
	{}

	~ControllerComponent()
	= default;

	void init() override
	{
		keyboard_ = new KeyboardHandler;
		data_ = Game::data->get_controller_data(controller_id_);
		controller_ = Controller(data_);
	}

	void change_controller(const int new_controller)
	{
		data_ = Game::data->get_controller_data(new_controller);
		controller_ = Controller(data_);
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
		for (auto input : controller_.inputs)
		{
			if (keyboard_check(input.keys))
				input.i_command->execute(entity);
			else
				input.i_command->idle(entity);
		}
	}

};

