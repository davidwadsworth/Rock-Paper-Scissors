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

	void SetDifficulty::execute(Entity * entity)
	{
	}

	void SetGameMode::execute(Entity * entity)
	{
		
	}
}


