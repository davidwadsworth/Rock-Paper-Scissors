#pragma once
#include "ECS.h"
#include "AICommand.h"
/**
 * @author David Wadsworth
 *
 * creates controller for the AI
*/
class AIComponent : public Component
{
	int difficulty_;
	AICommand * select_attack_, * combat_;
	bool active_;
public:
	explicit AIComponent(int difficulty);
	void init() override;
	void update() override;
	void select_attack();
	void activate();
	void deactivate();
};
