#include "stdafx.h"
#include "CombatInputCommands.h"
#include "CombatPresets.h"
#include "AttackPresets.h"

void CombatCommands::ScriptPush::idle(Entity * entity)
{
	was_pressed_ = true;
}

void CombatCommands::ScriptPush::execute(Entity * entity)
{
	if (was_pressed_)
	{
		auto& players = GameState::get_manager()->get_group(Game::group_players);
		Entity * victim = nullptr;

		for (auto p : players)
			if (p != entity)
				victim = p;


		auto push_preset = AttackPresets::PushPreset(victim, entity);
		push_preset.init();

		entity->get_component<ScriptComponent>().empty_add(push_preset.get_trunk());
		was_pressed_ = false;
	}
}

void CombatCommands::ScriptKick::idle(Entity * entity)
{
	was_pressed_ = true;
}

void CombatCommands::ScriptKick::execute(Entity * entity)
{
	if (was_pressed_)
	{
		auto& players = GameState::get_manager()->get_group(Game::group_players);
		Entity * victim = nullptr;

		for (auto p : players)
			if (p != entity)
				victim = p;

		auto kick_preset = AttackPresets::KickPreset(victim, entity);
		kick_preset.init();

		entity->get_component<ScriptComponent>().empty_add(kick_preset.get_trunk());
		was_pressed_ = false;
	}
}

void CombatCommands::ScriptBlock::idle(Entity * entity)
{
	if (!was_pressed_)
	{
		block_->close();
	}

	was_pressed_ = true;
}

void CombatCommands::ScriptBlock::execute(Entity * entity)
{
	if (was_pressed_)
	{
		if (!block_)
			block_ = new Navigation::BlockAndCrawl(entity, 0.5);
		
		if (entity->get_component<ScriptComponent>().is_empty())
		{
			block_->init();
			was_pressed_ = false;
		}
	}
}

void CombatCommands::EndCombat::idle(Entity * entity)
{
	if (was_pressed_)
	{
		auto& players = GameState::get_manager()->get_group(Game::group_players);
		auto& backgrounds = GameState::get_manager()->get_group(Game::group_background);
		auto round_ending = CombatPresets::RoundEnding(players[0], players[1]);
		auto reset_match = CombatPresets::ResetCombat(players[0], players[1], backgrounds[0]);
		auto enable_controller = CombatPresets::EnableMovement(players[0], players[1]);

		round_ending.init();
		reset_match.init();
		enable_controller.init();

		round_ending.get_trunk()->add(reset_match.get_trunk());
		reset_match.get_trunk()->add(enable_controller.get_trunk());
		GameState::get_path()->add(round_ending.get_trunk());
		was_pressed_ = false;
	}
}

void CombatCommands::EndCombat::execute(Entity * entity)
{
	was_pressed_ = true;
}

void CombatCommands::SelectAttack::idle(Entity* entity)
{
	if (was_pressed_)
	{
		auto& players = GameState::get_manager()->get_group(Game::group_players);
		auto select_attack = CombatPresets::MultiPlayerSelectAttack(players[0], players[1]);
		select_attack.init();

		GameState::get_path()->add(select_attack.get_trunk());
		was_pressed_ = false;
	}
}

void CombatCommands::SelectAttack::execute(Entity* entity)
{
	was_pressed_ = true;
}


