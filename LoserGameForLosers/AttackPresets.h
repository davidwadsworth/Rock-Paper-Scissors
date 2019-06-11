#pragma once
#include "NavigationPreset.h"
#include "CommonNavigation.h"

namespace AttackPresets
{
	class PlayerSlideBack : public NavigationPreset
	{
		Entity * victim_, *attacker_;
	public:
		explicit PlayerSlideBack(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

		void init() override;
	};

	class KickHitStun : public NavigationPreset
	{
		Entity * victim_, *attacker_;
	public:
		explicit KickHitStun(Entity * victim, Entity * attacker)
			: victim_(victim), attacker_(attacker)
		{}

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

