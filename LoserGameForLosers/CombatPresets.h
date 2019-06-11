#pragma once
#include "NavigationPreset.h"
#include "ECS.h"
#include "GameState.h"

namespace CombatPresets
{
	class ResetCombat : public NavigationPreset
	{
		Entity *player_1_, *player_2_, *background_;
		GameState * state_;
		int round_count_;
	public:
		ResetCombat(Entity * player_1, Entity * player_2, Entity * background)
			: player_1_(player_1), player_2_(player_2), background_(background), state_(player_1->state), round_count_(0)
		{}
		void init() override;
	};

	class SinglePlayerSelectAttack : public NavigationPreset
	{
		Entity * player_1_{},* player_2_{};
		GameState * state_{};
		int difficulty_;
	public:
		SinglePlayerSelectAttack(Entity *player_1, Entity * player_2, int difficulty)
			: player_1_(player_1), player_2_(player_2), state_(player_1->state), difficulty_(difficulty)
		{}
		void init() override;
	};

	class MultiPlayerSelectAttack : public NavigationPreset
	{
		Entity * player_1_, *player_2_;
		GameState * state_;
	public:
		MultiPlayerSelectAttack(Entity * player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2), state_(player_1->state)
		{}

		void init() override;
	};

	class SinglePlayerCombat : public NavigationPreset
	{
		Entity *player_1_, *player_2_;
		GameState * state_{};
		int difficulty_;
	public:
		SinglePlayerCombat(Entity *player_1, Entity * player_2, const int difficulty)
			: player_1_(player_1), player_2_(player_2), state_(player_1->state), difficulty_(difficulty)
		{}

		void init() override;
	};

	class MultiPlayerCombat : public NavigationPreset
	{
		Entity * player_1_, *player_2_;
		GameState * state_;
	public:
		MultiPlayerCombat(Entity * player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2), state_(player_1->state)
		{}

		void init() override;
	};

	class RoundEnding : public NavigationPreset
	{
		Entity * player_1_, *player_2_;
		GameState * state_;
	public:
		RoundEnding(Entity * player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2), state_(player_1->state)
		{}

		void init() override;
	};
}
