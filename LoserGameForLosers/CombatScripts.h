#pragma once
#include "Script.h"
#include "ECS.h"
#include "CombatPresets.h"

namespace CombatScripts
{
	class SinglePlayer : public Script
	{
	public:
		SinglePlayer(Entity * player_1, Entity * player_2, Entity * background, const int difficulty)
		{
			add_preset(new CombatPresets::ResetCombat(player_1, player_2, background));
			add_preset(new CombatPresets::SinglePlayerSelectAttack(player_1, player_2, difficulty));
			add_preset(new CombatPresets::SinglePlayerCombat(player_1, player_2, difficulty));
			add_preset(new CombatPresets::RoundEnding(player_1, player_2));
		}
	};

	class MultiPlayer : public Script
	{
	public:
		MultiPlayer(Entity * player_1, Entity * player_2, Entity * background)
		{
			add_preset(new CombatPresets::ResetCombat(player_1, player_2, background));
			add_preset(new CombatPresets::MultiPlayerSelectAttack(player_1, player_2));
			add_preset(new CombatPresets::MultiPlayerCombat(player_1, player_2));
			add_preset(new CombatPresets::RoundEnding(player_1, player_2));
		}
	};

	class Debug : public Path
	{
	public:
		Debug() = default;
	};
}
