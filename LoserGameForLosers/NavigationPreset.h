#pragma once
#include "Pathway.h"


class NavigationPreset
{
	PathTrunk * trunk_ = nullptr;
public:
	virtual ~NavigationPreset() = default;
	NavigationPreset() = default;

	void set_trunk(PathTrunk * trunk) { trunk_ = trunk; }
	virtual PathTrunk* get_trunk() { return trunk_; }

	virtual void init() = 0;

	virtual void close()
	{
		if (trunk_)
			trunk_->remove();
		trunk_ = nullptr;
	}
};