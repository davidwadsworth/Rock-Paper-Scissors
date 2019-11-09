#include "stdafx.h"

Asset::Asset(Manager * manager)
	: manager_(manager), asset_(nullptr)
{}

Entity * Asset::create_asset()
{
	asset_ = &manager_->add_entity();
	return asset_;
}
