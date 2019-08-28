#include "stdafx.h"
#include "AIComponent.h"
#include "AICommands.h"

AIComponent::AIComponent(const int difficulty)
	: difficulty_(difficulty), select_attack_(nullptr), combat_(nullptr), active_(false)
{}

void AIComponent::init()
{
	if (difficulty_ == 3)
		select_attack_ = new AICommands::SelectWinner(entity, GameState::get_manager()->get_group(Game::group_players)[0]);
	else
		select_attack_ = new AICommands::RandomSelectAttack(entity);

	combat_ = new AICommands::RandRangeCombat(entity, GameState::get_manager()->get_group(Game::group_players)[0], &GameState::get_ai_data()->data[difficulty_-1]);
}

void AIComponent::update()
{
	if (active_)
		combat_->execute();
}

void AIComponent::select_attack()
{
	select_attack_->execute();
}

void AIComponent::activate()
{
	active_ = true;
}

void AIComponent::deactivate()
{
	active_ = false;
}
