#include "stdafx.h"
#include "CombatInputCommands.h"
#include "CombatPresets.h"
#include "AttackPresets.h"

void CombatCommands::ScriptPush::idle(Entity * entity)
{
	if (was_pressed_)
	{
		auto& players = entity->manager.get_group(Game::group_players);
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

void CombatCommands::ScriptPush::execute(Entity * entity)
{
	was_pressed_ = true;
}

void CombatCommands::ScriptKick::idle(Entity * entity)
{
	if (was_pressed_)
	{
		auto& players = entity->manager.get_group(Game::group_players);
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

void CombatCommands::ScriptKick::execute(Entity * entity)
{
	was_pressed_ = true;
}

void CombatCommands::ScriptBlock::idle(Entity * entity)
{
	if (was_pressed_)
	{
		auto block_preset = AttackPresets::BlockPreset(entity);
		block_preset.init();

		entity->get_component<ScriptComponent>().empty_add(block_preset.get_trunk());
		was_pressed_ = false;
	}
}

void CombatCommands::ScriptBlock::execute(Entity * entity)
{
	was_pressed_ = true;
}

void CombatCommands::EndCombat::idle(Entity * entity)
{
	if (was_pressed_)
	{
		auto& players = entity->manager.get_group(Game::group_players);
		auto& backgrounds = entity->manager.get_group(Game::group_background);
		auto round_ending = CombatPresets::RoundEnding(players[0], players[1]);
		auto reset_match = CombatPresets::ResetCombat(players[0], players[1], backgrounds[0]);
		auto enable_controller = CombatPresets::EnableMovement(players[0], players[1]);

		round_ending.init();
		reset_match.init();
		enable_controller.init();

		round_ending.get_trunk()->add(reset_match.get_trunk());
		reset_match.get_trunk()->add(enable_controller.get_trunk());
		entity->state->path->add(round_ending.get_trunk());
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
		auto& players = entity->manager.get_group(Game::group_players);
		auto select_attack = CombatPresets::MultiPlayerSelectAttack(players[0], players[1]);
		select_attack.init();

		entity->state->path->add(select_attack.get_trunk());
		was_pressed_ = false;
	}
}

void CombatCommands::SelectAttack::execute(Entity* entity)
{
	was_pressed_ = true;
}


