#pragma once
#include "ECS.h"
#include "Pathway.h"

class ScriptComponent : public Component
{
	Path * attack_path_;
public:
	ScriptComponent() = default;
	~ScriptComponent() = default;

	void init() override;
	void update() override;

	void empty_add(PathTrunk * action) const;
	void clear_add(PathTrunk * action) const;
	void add(PathTrunk * action) const;
	void clear() const;
};