#include "stdafx.h"
#include "AIComponent.h"
#include "AICommands.h"

AIComponent::AIComponent(const int difficulty)
	: difficulty_(difficulty)
{}

void AIComponent::init()
{
	switch (difficulty_)
	{
	case 1:
		select_attack_ = new AICommands::RandomSelectAttack(entity);
		combat_ = new AICommands::RandRangeCombat(entity, GameState::get_manager()->get_group(Game::group_players)[0], 50, 5, 5);
		break;
	case 2:
		select_attack_ = new AICommands::RandomSelectAttack(entity);
		combat_ = new AICommands::RandRangeCombat(entity, GameState::get_manager()->get_group(Game::group_players)[0], 20, 100, 80);
	case 3:
		select_attack_ = new AICommands::SelectWinner(entity, GameState::get_manager()->get_group(Game::group_players)[0]);
		combat_ = new AICommands::RandRangeCombat(entity, GameState::get_manager()->get_group(Game::group_players)[0], 0, 1000, 500);
	default: ;
	}
}

void AIComponent::update()
{
	if (active_)
	{
		combat_->execute();
	}
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
