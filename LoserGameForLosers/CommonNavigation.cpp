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

	CreateOptionBox::CreateOptionBox(AssetManager * asset_manager, const int options_id, const int input_id, const Vector2D position)
		: target_(nullptr), option_box_(nullptr), input_id_(input_id), options_id_(options_id), position_(position), asset_manager_(asset_manager)
	{}

	CreateOptionBox::CreateOptionBox(AssetManager * asset_manager, const int options_id, const int input_id, const Vector2D position, Entity* target)
		: target_(target), option_box_(nullptr), input_id_(input_id), options_id_(options_id), position_(position), asset_manager_(asset_manager)
	{}

	void CreateOptionBox::init()
	{
		option_box_ = asset_manager_->create_option_box(options_id_, position_, input_id_);

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

	CreateMenuOptionBox::CreateMenuOptionBox(AssetManager * asset_manager, int options_id, int input_id, Vector2D position)
		: option_box_(nullptr), input_id_(input_id), options_id_(options_id), position_(position), asset_manager_(asset_manager)
	{
	}

	void CreateMenuOptionBox::init()
	{
		option_box_ = asset_manager_->create_menu_option_box(options_id_, position_, input_id_);
	}

	int CreateMenuOptionBox::choose_path()
	{
		return option_box_->get_component<OptionsComponent>().get_path();
	}

	void CreateMenuOptionBox::close()
	{
		option_box_->del_group(Game::group_cursors);
		option_box_->destroy();
	}

}



