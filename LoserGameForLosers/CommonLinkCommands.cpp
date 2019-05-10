#include "stdafx.h"
#include "CommonLinkCommands.h"

namespace LinkCommands
{
	void ChangeState::execute(Entity * entity)
	{
		previous_state_ = Game::state_id;
		if (Game::state_id != state_)
			Game::set_next_state(state_);
	}


	void SelectAttack::change_target(Entity * target)
	{
		target_ = target;
	}

	void SelectAttack::execute(Entity * entity)
	{
		if (target_)
		{
			previous_attack_id_ = target_->get_component<PlayerComponent>().attack_id;
			target_->get_component<PlayerComponent>().choose_attack(attack_id_);
		}
	}

	void ChooseCharacter::execute(Entity * entity)
	{
		if (entity->get_component<ControllerComponent>().get_input_controller_id() == input_controller_player_1)
		{
			previous_id_ = Game::game_settings->player_1_info;
			Game::game_settings->set_player_1(character_id_);
		}
		else
		{
			previous_id_ = Game::game_settings->player_2_info;
			Game::game_settings->set_player_2(character_id_);
		}
	}

	void ChooseBackground::execute(Entity * entity)
	{
		Game::game_settings->set_background(background_id_);
	}

	void SetDifficulty::execute(Entity * entity)
	{
	}

	void SetGameMode::execute(Entity * entity)
	{
		Game::game_settings->game_mode = game_id_;
	}
}


