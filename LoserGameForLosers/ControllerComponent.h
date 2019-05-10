#pragma once

#include "ECS.h"
#include <SDL.h>
#include "Controller.h"
#include "KeyboardHandler.h"

class ControllerComponent : public Component
{
	KeyboardHandler * keyboard_;

	std::vector<SDL_Scancode> keys_;

	int controller_id_;
	int keys_id_;

	ControllerData * data_;
	Controller controller_;
public:

	ControllerComponent(const int controller_id, const int keys_id) : keys_(Game::game_settings->get_keys(keys_id)), controller_id_(controller_id), keys_id_(keys_id)
	{}

	~ControllerComponent()
	= default;

	int get_input_controller_id() const
	{
		return keys_id_;
	}

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

