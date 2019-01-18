#include "stdafx.h"
#include "LinkCommands.h"

void ChangeStateCommand::execute(Entity * entity)
{
	if (Game::state_id != state_)
		Game::set_next_state(state_);
}
