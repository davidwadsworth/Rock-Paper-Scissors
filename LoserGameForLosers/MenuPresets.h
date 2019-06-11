#pragma once
#include "NavigationPreset.h"
#include "GameState.h"

namespace MenuPresets
{
	class CreateMenuOptions : public NavigationPreset
	{
		GameState * state_;
	public:
		CreateMenuOptions(GameState * state)
			: state_(state)
		{}

		void init() override;
	};
}
