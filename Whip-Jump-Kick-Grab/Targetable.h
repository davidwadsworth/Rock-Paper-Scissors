#pragma once
#include "ECS.h"

/**
 * @author David Wadsworth
 * 
 * makes commands able to target something other than the entity they are created with
 */

class Targetable
{
public:
	virtual ~Targetable() = default;
	virtual void change_target(Entity * target) = 0;
};
