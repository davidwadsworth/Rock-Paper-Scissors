#pragma once
#include "Script.h"
#include "ECS.h"
#include "CombatPresets.h"

/**
 * @author David Wadsworth
 *
 * Unique navigation patterns set by game states
*/

namespace CombatScripts
{
	class SinglePlayer : public CircularScript
	{
	public:
		SinglePlayer(Entity * player_1, Entity * player_2, Entity * background)
		{
			add_preset(new CombatPresets::ResetCombat(player_1, player_2, background));
			add_preset(new CombatPresets::SinglePlayerSelectAttack(player_1, player_2));
			add_preset(new CombatPresets::SinglePlayerCombat(player_1, player_2));
			add_preset(new CombatPresets::RoundEnding(player_1, player_2));
		}
	};

	class MultiPlayer : public CircularScript
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
