#pragma once
#include "NavigationPreset.h"
#include "ECS.h"

namespace CombatPresets
{
	class ResetCombat : public NavigationPreset
	{
		Entity *player_1_, *player_2_, *background_;
		int round_count_;
		Manager * manager_;
	public:
		ResetCombat(Entity * player_1, Entity * player_2, Entity * background)
			: player_1_(player_1), player_2_(player_2), background_(background), round_count_(0)
		{
			manager_ = GameState::get_manager();
		}
		void init() override;
	};

	class SinglePlayerSelectAttack : public NavigationPreset
	{
		Entity * player_1_{},* player_2_{};
		int difficulty_;
		Manager * manager_;
	public:
		SinglePlayerSelectAttack(Entity *player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2)
		{
			manager_ = GameState::get_manager();
		}
		void init() override;
	};

	class MultiPlayerSelectAttack : public NavigationPreset
	{
		Entity * player_1_, *player_2_;
		Manager * manager_;
	public:
		MultiPlayerSelectAttack(Entity * player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2)
		{
			manager_ = GameState::get_manager();
		}

		void init() override;
	};

	class SinglePlayerCombat : public NavigationPreset
	{
		Entity *player_1_, *player_2_;
		int difficulty_;
		Manager * manager_;
	public:
		SinglePlayerCombat(Entity *player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2)
		{
			manager_ = GameState::get_manager();
		}

		void init() override;
	};

	class MultiPlayerCombat : public NavigationPreset
	{
		Entity * player_1_, *player_2_;
		Manager * manager_;
	public:
		MultiPlayerCombat(Entity * player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2)
		{
			manager_ = GameState::get_manager();
		}

		void init() override;
	};

	class RoundEnding : public NavigationPreset
	{
		Entity * player_1_, *player_2_;
		Manager * manager_;
	public:
		RoundEnding(Entity * player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2)
		{
			manager_ = GameState::get_manager();
		}

		void init() override;
	};

	class MatchEnding : public NavigationPreset
	{
		int player_;
		Manager * manager_;
	public:
		MatchEnding(int player)
			: player_(player)
		{
			manager_ = GameState::get_manager();
		}
		void init() override;
	};

	class EnableMovement : public NavigationPreset
	{
		Entity * player_1_, *player_2_;
	public:
		EnableMovement(Entity * player_1, Entity * player_2)
			: player_1_(player_1), player_2_(player_2)
		{}

		void init() override;

	};
}
