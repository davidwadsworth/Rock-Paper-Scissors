#include "stdafx.h"
#include "ScriptComponent.h"

void ScriptComponent::init()
{
	attack_path_ = new Path();
}

void ScriptComponent::update()
{
	attack_path_->navigate_path();
}

void ScriptComponent::empty_add(PathTrunk * action) const
{
	if (attack_path_->is_empty())
		attack_path_->add(action);
}

void ScriptComponent::clear_add(PathTrunk * action) const
{
	attack_path_->clear();
	attack_path_->add(action);
}

void ScriptComponent::add(PathTrunk * action) const
{
	attack_path_->add(action);
}
