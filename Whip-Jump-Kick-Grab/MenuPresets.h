#pragma once
#include "NavigationPreset.h"
/**
 * @author David Wadsworth
 *
 * compilations of menu phases
*/
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
