#pragma once
#include "NavigationPreset.h"
#include "CombatNavigation.h"

namespace AttackPresets
{
	class PlayerSlideBack : public NavigationPreset
	{
		Entity * victim_, *attacker_;
		int damage_;
	public:
		PlayerSlideBack(Entity * victim, Entity * attacker);
		void init() override;
	};

	class KickHitStun : public NavigationPreset
	{
		Entity * victim_, *attacker_;
		int damage_;
	public:
		KickHitStun(Entity * victim, Entity * attacker);

		void blocked();
		void init() override;
	};

	class BlockPreset : public NavigationPreset
	{
		Entity * blocker_;
	public:
		explicit BlockPreset(Entity * blocker)
			: blocker_(blocker)
		{}

		void init() override;
	};

	class KickPreset : public NavigationPreset
	{
		Entity * victim_, *attacker_;
	public:
		explicit KickPreset(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

		void init() override;
	};

	class PushPreset : public NavigationPreset
	{
		Entity * victim_, * attacker_;
	public:
		explicit PushPreset(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

		void init() override;
	};

}

