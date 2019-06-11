#pragma once
#include "ECS.h"

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void execute(Entity * entity){}
};

