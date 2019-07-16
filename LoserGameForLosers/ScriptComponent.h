#pragma once
#include "ECS.h"
#include "Pathway.h"
/**
 * @author David Wadsworth
 *
 * Player scripts to load in attacks
*/
class ScriptComponent : public Component
{
	Path * attack_path_;
public:
	ScriptComponent()
		: attack_path_(nullptr)
	{}

	~ScriptComponent() = default;

	void init() override;
	void update() override;

	void empty_add(PathTrunk * action) const;
	void clear_add(PathTrunk * action) const;
	void add(PathTrunk * action) const;
	bool is_empty();
	void clear() const;
};