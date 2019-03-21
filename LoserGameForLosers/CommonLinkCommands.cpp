#include "stdafx.h"
#include "CommonLinkCommands.h"

void ChangeStateLink::execute(Entity * entity)
{
	if (Game::state_id != state_)
	{
		Game::set_next_state(state_);
	}
	previous_state_ = Game::state_id;
	Game::stack->add(this);
}

void ChangeStateLink::undo()
{
	if (Game::state_id != previous_state_)
	{
		Game::set_next_state(previous_state_);
	}
}


void SelectAttackLink::change_target(Entity * target)
{
	target_ = target;
}

void SelectAttackLink::execute(Entity * entity)
{
	if (target_)
	{
		previous_attack_id_ = target_->get_component<PlayerComponent>().attack_id;
		target_->get_component<PlayerComponent>().choose_attack(attack_id_);
		entity->del_group(Game::group_cursors);
		entity->destroy();
		entity = nullptr;
	}
	Game::stack->add(this);
}

void SelectAttackLink::undo()
{
	if (target_)
		target_->get_component<PlayerComponent>().choose_attack(previous_attack_id_);
}

void UndoLink::execute(Entity * entity)
{
	auto last = Game::stack->get_last();
	if (last)
		last->undo();
}

void ChooseCharacterLink::execute(Entity * entity)
{
	if (entity->get_component<ControllerComponent>().player1)
	{
		previous_id_ = Game::game_settings->player_1_info;
		Game::game_settings->set_player_1(character_id_);
		entity->get_component<OptionsComponent>().change_options(options_choose_background);
		entity_ = entity;
	}
	else
	{
		Game::game_settings->set_player_2(character_id_);
		entity->del_group(Game::group_cursors);
		entity->destroy();
		entity = nullptr;
	}
	Game::stack->add(this);
}

void ChooseCharacterLink::undo()
{
	if (entity_)
	{
		Game::game_settings->set_player_1(previous_id_);
		entity_->get_component<OptionsComponent>().change_options(options_choose_character);
	}
}

void ChooseBackgroundLink::execute(Entity * entity)
{
	Game::game_settings->set_background(background_id_);

	if (manager.get_group(Game::group_cursors).size() == 1)
	{
		Game::set_next_state(STATE_COMBAT);
	}
}

void SinglePlayerLink::execute(Entity * entity)
{
	entity->get_component<OptionsComponent>().change_options(options_choose_difficulty);
	entity_ = entity;
}

void SinglePlayerLink::undo()
{
	if (entity_)
		entity_->get_component<OptionsComponent>().change_options(options_start_menu);
}

void TwoPlayerLink::execute(Entity * entity)
{
	entity->get_component<OptionsComponent>().change_options(options_choose_character);
	p1_entity_ = entity;
	p2_entity_ = Game::assets->create_option_box(options_choose_character, SDL_Point{ SCREEN_WIDTH * 5 / 4, SCREEN_HALF_HEIGHT }, false);
}

void TwoPlayerLink::undo()
{
	if (p1_entity_)
		p1_entity_->get_component<OptionsComponent>().change_options(options_start_menu);
	if (p2_entity_)
	{
		p2_entity_->del_group(Game::group_cursors);
		p2_entity_->destroy();
		p2_entity_ = nullptr;
	}
}

void SetDifficultyLink::execute(Entity * entity)
{
	entity_ = entity;
	entity_->get_component<OptionsComponent>().change_options(options_choose_character);
}

void SetDifficultyLink::undo()
{
	if (entity_)
		entity_->get_component<OptionsComponent>().change_options(options_choose_difficulty);
}
