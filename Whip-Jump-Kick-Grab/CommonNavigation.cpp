#include "stdafx.h"
#include "CommonNavigation.h"
#include "ControllerComponent.h"

namespace Navigation
{
	Delay::Delay(const Uint32 delay)
		: total_delay_(delay), timer_(new Timer())
	{}

	int Delay::choose_path()
	{
		if (!timer_->is_started())
			timer_->start();

		if (timer_->get_ticks() > total_delay_)
		{
			timer_->stop();
			return 1;
		}

		return 0;
	}

	ChangeState::ChangeState(const game_states new_state)
		: new_state_(new_state)
	{}

	int ChangeState::choose_path()
	{
		Game::set_next_state(new_state_);
		return 1;
	}

	CreateOptionBox::CreateOptionBox(Manager * manager, const int glyph_id, const int cursor_id, const int options_id, const int input_id, const int controller_id, const Vector2D position)
		: target_(nullptr), input_id_(input_id), options_id_(options_id), cursor_id_(cursor_id), glyph_id_(glyph_id), controller_id_(controller_id), position_(position), option_box_(manager)
	{}

	CreateOptionBox::CreateOptionBox(Manager * manager, const int glyph_id, const int cursor_id, const int options_id, const int input_id, const int controller_id, const Vector2D position, Entity* target)
		: target_(target), input_id_(input_id), options_id_(options_id), cursor_id_(cursor_id), glyph_id_(glyph_id), controller_id_(controller_id), position_(position), option_box_(manager)
	{}

	void CreateOptionBox::init()
	{
		option_box_.create(glyph_id_, cursor_id_, options_id_, controller_id_, position_, input_id_);

		if (target_)
			option_box_.get_asset()->get_component<OptionsComponent>().change_target(target_);
	}

	void CreateOptionBox::close()
	{
		option_box_.destroy();
	}

	int CreateOptionBox::choose_path()
	{
		return option_box_.get_asset()->get_component<OptionsComponent>().get_path();
	}

	EnableController::EnableController(Entity * player)
		: player_(player)
	{}
	int EnableController::choose_path()
	{
		player_->get_component<ControllerComponent>().activate();
		return 1;
	}
	DisableController::DisableController(Entity * player)
		: player_(player)
	{}

	int DisableController::choose_path()
	{
		player_->get_component<ControllerComponent>().deactivate();
		return 1;
	}

}



