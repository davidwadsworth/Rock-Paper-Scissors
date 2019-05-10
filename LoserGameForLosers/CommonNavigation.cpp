#include "stdafx.h"
#include "CommonNavigation.h"

namespace Navigation
{
	Delay::Delay(const Uint32 delay)
		: total_delay_(delay), ticks_(0)
	{}

	int Delay::choose_path()
	{
		if (ticks_++ > total_delay_)
			return 1;
		return 0;
	}

	ChangeController::ChangeController(Entity * player, const CONTROLLER_DATA new_controller)
		: player_(player), new_controller_(new_controller)
	{}

	int ChangeController::choose_path()
	{
		player_->get_component<ControllerComponent>().change_controller(new_controller_);
		return 1;
	}

	ChangeState::ChangeState(const game_states new_state)
		: new_state_(new_state)
	{}

	int ChangeState::choose_path()
	{
		Game::set_next_state(new_state_);
		return 1;
	}

	CreateOptionBox::CreateOptionBox(const int options_id, const int input_id, const Vector2D position)
		: target_(nullptr), option_box_(nullptr), input_id_(input_id), options_id_(options_id), position_(position)
	{}

	CreateOptionBox::CreateOptionBox(const int options_id, const int input_id, const Vector2D position, Entity* target)
		: target_(target), option_box_(nullptr), input_id_(input_id), options_id_(options_id), position_(position)
	{}

	void CreateOptionBox::init()
	{
		option_box_ = Game::assets->create_option_box(options_id_, position_, input_id_);

		if (target_)
			option_box_->get_component<OptionsComponent>().change_target(target_);
	}

	void CreateOptionBox::close()
	{
		option_box_->del_group(Game::group_cursors);
		option_box_->destroy();
	}

	int CreateOptionBox::choose_path()
	{
		return option_box_->get_component<OptionsComponent>().get_path();
	}
}



