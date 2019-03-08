#pragma once
#include "ECS.h"

class Targetable
{
public:
	virtual void change_target(Entity * target) = 0;
};
