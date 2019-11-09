#include "stdafx.h"
#include "CommonLinkCommands.h"

namespace LinkCommands
{
	void ChangeState::execute(Entity * entity)
	{
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
			target_->get_component<PlayerComponent>().choose_final_attack(attack_id_);
		}
	}

	void SetDifficulty::execute(Entity * entity)
	{
		Game::combat_difficulty = difficulty_id_;
	}

	void SetGameMode::execute(Entity * entity)
	{
		Game::combat_state = game_id_;
	}
}


