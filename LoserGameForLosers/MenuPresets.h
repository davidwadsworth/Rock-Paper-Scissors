#pragma once
#include "NavigationPreset.h"

namespace MenuPresets
{
	class CreateMenuOptions : public NavigationPreset
	{
		Entity * screen_;
		Manager * manager_;
	public:
		CreateMenuOptions(Entity * screen);
		void init() override;
	};
}
