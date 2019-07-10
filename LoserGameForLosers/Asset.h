#pragma once
#include "ECS.h"

class Asset
{
	Manager * manager_;
	Entity* asset_;
public:
	Asset(Manager * manager);
	virtual ~Asset() = default;
	Entity* create_asset();
	Entity* get_asset() const { return asset_; }
	virtual void destroy() = 0;
};